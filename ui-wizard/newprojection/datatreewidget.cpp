#include <QtWidgets>
#include "datatreewidget.h"

DataTreeWidget::DataTreeWidget(QWidget *parent)
    :QTreeWidget(parent), MAX_LEVEL(5)
{
    for (int i=1; i<=MAX_LEVEL; i++){
        headLabels << tr("h%1").arg(i);
    }
    QStringList labels;
    labels << tr("导入项目") << tr("路径") << tr("操作");

    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    setHeaderLabels(labels);

    toImportIcon.addPixmap(QPixmap(":/res/icon/Checkbox empty 16x16.png"));
    ImportedIcon.addPixmap(QPixmap(":/res/icon/Checkbox 16x16.png"));

    resizeColumnToContents(2);
}

bool DataTreeWidget::read(QIODevice *device, QString &type){
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine, &errorColumn)){
        QMessageBox::information(window(), tr("请检查xml文件"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }

    QDomElement root = domDocument.documentElement();
    qDebug()<<root.tagName() << type;
    if (root.tagName().compare(type) != 0){
        QMessageBox::information(window(), tr("文件内容不匹配"),
                                 tr("Please check if the type is match.\n"));
        return false;
    }
    clear();
    disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this, SLOT(updateDomElement(QTreeWidgetItem*,int)));


    QDomElement child = root.firstChildElement("extension");
    extensionType = child.text();
    qDebug()<<child.tagName();

    int level = 0;
    child = child.nextSiblingElement("items")
            .firstChildElement(headLabels.at(level));
    qDebug()<<child.tagName() << endl;

    QDomElement head;
    while (!child.isNull()){
        parseHeaderElement(child);
        child = child.nextSiblingElement(headLabels.at(level));
    }

    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this, SLOT(updateDomElement(QTreeWidgetItem*,int)));
    return true;
}

bool DataTreeWidget::write(QIODevice *device){

}

void DataTreeWidget::updateDomElement(QTreeWidgetItem *item, int column){
    QDomElement element = domElementForItem.value(item);
    if (!element.isNull()) {
//        if (column == 0) {
//            QDomElement oldTitleElement = element.firstChildElement("title");
//            QDomElement newTitleElement = domDocument.createElement("title");

//            QDomText newTitleText = domDocument.createTextNode(item->text(0));
//            newTitleElement.appendChild(newTitleText);

//            element.replaceChild(newTitleElement, oldTitleElement);
//        } else {
//            if (element.tagName() == "bookmark")
//                element.setAttribute("href", item->text(1));
//        }
    }
}

void DataTreeWidget::parseHeaderElement(const QDomElement &element,
                                        QTreeWidgetItem *parentItem,
                                        int level){
    QTreeWidgetItem *item = createItem(element, parentItem);

    QString value = element.firstChildElement("value").text();
    if (value.isEmpty()) {
        value = headLabels.at(level);
    }

    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setIcon(0, toImportIcon);
    item->setText(0, value);

    bool exclusive = (element.attribute("exclusive") == "1");

    QDomElement child = element.firstChildElement();
    while (!child.isNull()){
        if (child.tagName().at(0) == 'h'){
            //head x
            parseHeaderElement(child, item, level+1);
        }
        else if (child.tagName() == "leaf") {
            QTreeWidgetItem *childItem = createItem(child, item);

            QString value = element.firstChildElement("value").text();
            if (value.isEmpty()) {
                value = headLabels.at(level);
            }

            childItem->setFlags(item->flags() | Qt::ItemIsEditable);
            childItem->setIcon(0, toImportIcon);
            childItem->setText(0, value);
            childItem->setText(1, child.attribute("href"));

            QPushButton* pbt = new QPushButton("导入");
            pbt->setMaximumWidth(40);
            pbtnForItem.insert(pbt, childItem);
            setItemWidget(childItem, 2, pbt);
        }
        child = child.nextSiblingElement();
    }
}

QTreeWidgetItem *DataTreeWidget::createItem(const QDomElement &element,
                                            QTreeWidgetItem *parentItem,
                                            int level){
    QTreeWidgetItem *item;
    if (parentItem){
        item = new QTreeWidgetItem(parentItem);
    } else {
        item = new QTreeWidgetItem(this);
    }
    domElementForItem.insert(item, element);
    return item;
}

