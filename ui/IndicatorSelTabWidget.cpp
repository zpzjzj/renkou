#include "IndicatorSelTabWidget.hpp"
#include "../Scheme/jsonUtil.hpp"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTreeView>
#include <tuple>
#include <memory>

namespace {
    const QString INDICATOR_STR = "indicator";
    const QString INDICATORS_STR = "indicators";
    const QString CLASS_STR = "class";

    inline QString read_if_exist(QJsonObject& json, QString key) {
        auto iter = json.find(key);
        return iter == json.end() ? "" : (*iter).toString();
    }

    QString getName(QJsonObject &json) {
        return json["name"].toString();
    }

    void buildModel(QStandardItem* parentItem, QJsonArray array) {
        for(auto jsonValRef : array) {
            auto groupObj = jsonValRef.toObject();
            QStandardItem *item = new QStandardItem(getName(groupObj));
            item->setEditable(false);
            parentItem->appendRow(item);
            if(groupObj.find(INDICATORS_STR) != groupObj.end()) {//is group
                buildModel(item, groupObj[INDICATORS_STR].toArray());
                item->setSelectable(false);
            } else {
                if(parentItem->columnCount() == 1) {
                    parentItem->setColumnCount(3);
                }//expand col if not avail

                int row = item->row();
                int col = item->column();
                parentItem->setChild(row, ++col, new QStandardItem(groupObj[CLASS_STR].toString()));
                parentItem->setChild(row, ++col, new QStandardItem(read_if_exist(groupObj, INDICATOR_STR)));
            }
        }
    }

    /**
     * @brief getItem
     * @return sibling of item
     */
    QStandardItem* getItem(const QStandardItem* siblingItem, int col) {
        qDebug() << "siblingItem" << siblingItem->text();
        qDebug() << "col" << col;
        auto parent = siblingItem->parent();
        qDebug() << "parent col count" << parent->columnCount();
        return parent->child(siblingItem->row(), col);
    }

    /**
     * @brief getIndicator
     * @param item that is not null
     * @return original indicator name & category
     */
    std::tuple<QString, QString> getIndicatorInfo(const QStandardItem* item) {
        QString category = getItem(item, item->column() + 1)->text();
        QString indicator = getItem(item, item->column() + 2)->text();
        return std::make_tuple(category, indicator);
    }
}

IndicatorSelTabWidget::IndicatorSelTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    QJsonDocument doc = jsonUtil::readFile(":/display/config/indicator.json");
    for(auto jsonValRef : doc.array()) {
        auto category = jsonValRef.toObject();
        mModels.emplace_back(std::move(new QStandardItemModel()));
        QStandardItemModel* model = mModels.back().get();
        buildModel(model->invisibleRootItem(), category["groups"].toArray());
        QString name = getName(category);
        model->setHorizontalHeaderLabels({name});
        QTreeView *treeView = new QTreeView(this);
        treeView->setModel(model);
        treeView->setSelectionMode(QAbstractItemView::SingleSelection);
        QObject::connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            [this, treeView](const QItemSelection& selected){
            const QStandardItemModel* model = dynamic_cast<const QStandardItemModel*>(treeView->model());
            selectionChanged(model, selected.indexes());
        });
        addTab(treeView, name);
    }
    QObject::connect(this, &QTabWidget::currentChanged, [this](int index) {
        auto treeView = dynamic_cast<QTreeView*>(widget(index));
        auto model = dynamic_cast<QStandardItemModel*>(treeView->model());
        auto indexs = treeView->selectionModel()->selectedIndexes();
        selectionChanged(model, indexs);
    });
}

void IndicatorSelTabWidget::selectionChanged(const QStandardItemModel* model, const QModelIndexList indexes) {
    QString indicator;
    QString category;
    if(!indexes.empty()) {
        QStandardItem* selected = model->itemFromIndex(indexes.front());
        std::tie(category, indicator) = getIndicatorInfo(selected);
    }

    qDebug() << "selectionChanged()" << indicator << category;
    if(mIndicator != indicator) {
        mIndicator = indicator;
        emit indicatorChanged(indicator);
        qDebug() << "indicatorChanged" << indicator;
    }

    if(mCategory != category) {
        mCategory = category;
        emit categoryChanged(category);
        qDebug() << "categoryChanged" << category;
    }
}
