#include "../Scheme/schememetadata.h"
#include "../Scheme/jsonUtil.hpp"
#include "IndicatorSel.hpp"
#include "ui_IndicatorSel.h"
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QTreeView>
#include <QMessageBox>

IndicatorSel::IndicatorSel(ParasManager* parasManagerPtr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorSel)
{
    ui->setupUi(this);
    auto coordDispBtn = ui->buttonBox->addButton(tr("坐标式显示"), QDialogButtonBox::ActionRole);
    auto mapDispBtn = ui->buttonBox->addButton(tr("地图式显示"), QDialogButtonBox::ActionRole);
    mSchemeListManagerPtr = new SchemeListManager(parasManagerPtr, ui->listWidget, parent);
    createTreeView();
    QObject::connect(coordDispBtn, SIGNAL(clicked()), this, SLOT(coordDisplay()));
    QObject::connect(mapDispBtn, SIGNAL(clicked()), this, SLOT(mapDisplay()));
}

IndicatorSel::~IndicatorSel()
{
    delete ui;
}

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
    QStandardItem* getItem(QStandardItem* siblingItem, int col) {
        auto parent = siblingItem->parent();
        return parent->child(siblingItem->row(), col);
    }

    using Category = schememetadata::Category;
    Category getCategory(const QString& str) {
        //!< map of str in indicator file and Category
        const static QMap<QString, Category> map = {
            std::make_pair(QObject::tr("人口概要"), Category::RenKouGaiYao),
            std::make_pair(QObject::tr("夫妇子女"), Category::FuFuZiNv),
            std::make_pair(QObject::tr("政策生育"), Category::ZhengCeShengYu),
            std::make_pair(QObject::tr("生育孩次"), Category::ShengYuHaiCi),
            std::make_pair(QObject::tr("分龄非农"), Category::FenLingFeiNong),
            std::make_pair(QObject::tr("分龄农业"), Category::FenLingNongYe),
            std::make_pair(QObject::tr("分龄合计"), Category::FenLingHeJi),
            std::make_pair(QObject::tr("分龄特扶"), Category::FenLingTeFu),
            std::make_pair(QObject::tr("分龄奖扶"), Category::FenLingJiangFu)
        };
        return map.value(str);
    }

}

void IndicatorSel::createTreeView() {
    QJsonDocument doc = jsonUtil::readFile(":/display/config/indicator.json");
    for(auto jsonValRef : doc.array()) {
        auto category = jsonValRef.toObject();
        mModels.push_back(std::make_unique<QStandardItemModel>());
        QStandardItemModel* model = mModels.back().get();
        buildModel(model->invisibleRootItem(), category["groups"].toArray());
        QString name = getName(category);
        model->setHorizontalHeaderLabels({name});
        QTreeView *treeView = new QTreeView();
        treeView->setModel(model);
        ui->tabWidget->addTab(treeView, name);
    }
}

void IndicatorSel::coordDisplay() {
    auto item = getSelection();
    if(item == nullptr)
        return;
    auto schemes = getSchemes(getCategory(getItem(item, item->column() + 1)->text()));
    //TODO
}

void IndicatorSel::mapDisplay() {
    const static QString AREA_STR = "diqu";
    auto item = getSelection();
    if(item == nullptr)
        return;
    if(mAbstractSchemes.front()->value(AREA_STR) == mAbstractSchemes.back()->value(AREA_STR)) {
        QMessageBox::warning(this, tr("指标选择"), tr("当前方案在同一地区，不能地图显示"));
        return;
    }
    auto schemes = getSchemes(getCategory(getItem(item, item->column() + 1)->text()));
    //TODO
}

IndicatorSel::SchemeList IndicatorSel::getSchemes(schememetadata::Category category) const {
    SchemeList res;
    schememetadataPtr meta = std::make_shared<schememetadata>(category);
    res.reserve(mAbstractSchemes.size());
    for(auto abstractSchemePtr : mAbstractSchemes) {
        auto scheme = abstractSchemePtr->generate(meta);
        if(scheme != nullptr) {
            qDebug() << "scheme: " << scheme->getName()
                     << "in IndicatorSel::getSchemes(schememetadata::Category category)";
            res.push_back(scheme);
        }
    }
    return res;
}

QStandardItem* IndicatorSel::getSelection() {
    auto treeView = dynamic_cast<QTreeView*>(ui->tabWidget->currentWidget());
    auto indexs = treeView->selectionModel()->selectedIndexes();
    if(indexs.empty()) {
        QMessageBox::warning(this, tr("指标选择"), tr("当前您没有选择任何指标!"), QMessageBox::Ok);
        return nullptr;
    } else {
        auto model = dynamic_cast<QStandardItemModel*>(treeView->model());
        return model->itemFromIndex(indexs.first());
    }
}
