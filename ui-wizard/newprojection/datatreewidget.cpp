#include <QtWidgets>
#include "datatreewidget.h"
#include "studyobject.h"
#include "EnumClass.h"
DataTreeWidget::DataTreeWidget(QWidget *parent)
    :QTreeWidget(parent), MAX_LEVEL(5)
{
    for (int i=1; i<=MAX_LEVEL; i++){
        headLabels << tr("h%1").arg(i);
    }
    QStringList labels;
    labels << tr("导入项目") << tr("路径") << tr("操作");

    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    setHeaderLabels(labels);

    toImportIcon.addPixmap(QPixmap(":/res/icon/Checkbox empty 16x16.png"));
    ImportedIcon.addPixmap(QPixmap(":/res/icon/Checkbox 16x16.png"));

    //resizeColumnToContents(2);

    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(const QString&)),
            this, SLOT(importBtnClicked(const QString&)));
}

bool DataTreeWidget::read(QIODevice *device, QString &type, StudyObject *obejct){
    QString errorStr;
    int errorLine;
    int errorColumn;

    this->object = obejct;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine, &errorColumn)){
        QMessageBox::information(window(), tr("请检查xml文件"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }

    QDomElement root = domDocument.documentElement();
//    qDebug()<<root.tagName() << type;
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

    int level = 0;
    child = child.nextSiblingElement("items")
            .firstChildElement(headLabels.at(level));

    while (!child.isNull()){
        parseHeaderElement(child);
        child = child.nextSiblingElement(headLabels.at(level));
    }

    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this, SLOT(updateDomElement(QTreeWidgetItem*,int)));
    return true;
}

bool DataTreeWidget::write(QIODevice *device){
    const int IndentSize = 4;

    QTextStream out(device);
    domDocument.save(out, IndentSize);
    return true;
}

void DataTreeWidget::updateDomElement(QTreeWidgetItem *item, int column){
    QDomElement element = domElementForItem.value(item);
    if (!element.isNull()) {
        if (column == 1) {
            if (element.tagName() == "leaf"){

                element.setAttribute("href", item->text(1));
                qDebug()<<element.attribute("href");
            }
        }
    }
    //update tmp file
    writeTmpFile();
}
bool DataTreeWidget::writeTmpFile(){
    QString fileName = EnumClass::PREFIX+object->getTmpXmlFilename();
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Xml File"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    return write(&file);
}
void DataTreeWidget::importBtnClicked(const QString &string){
    QTreeWidgetItem *item = valueForItem.value(string);
    ///TODO
    ///
    QString caption = tr("Open %1 Files").arg(extensionType);
    QString dir = EnumClass::PREFIX;
    QString filter = 0;
    QString path = QFileDialog::getOpenFileName(this, caption, dir,filter);
    if (! path.isEmpty()){
        item->setText(1, path);
        item->setIcon(0, ImportedIcon);
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

            QString value = child.text();
            if (value.isEmpty()) {
                value = headLabels.at(level);
            }

            //childItem->setFlags(item->flags() | Qt::ItemIsEditable);
            childItem->setIcon(0, toImportIcon);
            childItem->setText(0, value);
            childItem->setText(1, child.attribute("href"));

            QPushButton* pbt = new QPushButton("导入");
            pbt->setMaximumWidth(40);


            signalMapper->setMapping(pbt, value);
            connect(pbt, SIGNAL(clicked()), signalMapper, SLOT(map()));
            valueForItem.insert(value, childItem);
            setItemWidget(childItem, 2, pbt);
        }
        child = child.nextSiblingElement();
    }
}

QTreeWidgetItem *DataTreeWidget::createItem(const QDomElement &element,
                                            QTreeWidgetItem *parentItem,
                                            int level){
    qDebug()<<tr("DataTreeWidget::createItem(QDomeElement %1, QTreeWidgetItem %2, %3")
              .arg(element.text())
              .arg(parentItem->text(0))
               .arg(level);
    QTreeWidgetItem *item;
    if (parentItem){
        item = new QTreeWidgetItem(parentItem);
    } else {
        item = new QTreeWidgetItem(this);
    }
    domElementForItem.insert(item, element);
    return item;
}

