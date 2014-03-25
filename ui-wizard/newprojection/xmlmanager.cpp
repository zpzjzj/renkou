#include "xmlmanager.hpp"
#include "datatreewidget.h"
#include "datatreewidgetitem.h"
#include <QWidget>
#include <QMessageBox>

XMLManager::XMLManager(DataTreeWidget *widget, QString &filetype)
    :treeWidget(widget), filetype(filetype)
{

}

bool XMLManager::read(QIODevice *device){
    QString errString;
    int errLine;
    int errColumn;

    if (!domDocument.setContent(device, true, &errString, &errLine, &errColumn)){
         QMessageBox::information(treeWidget->window(), QObject::tr("DOM XMLManager"),
                                 QObject::tr("Parse error at line%1, column %2:\n%3")
                                 .arg(errLine)
                                 .arg(errColumn)
                                 .arg(errString));
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != filetype){
        QMessageBox::information(treeWidget->window(), QObject::tr("DOM XMLManager"),
                                 QObject::tr("The file is not a %s file").arg(filetype));
        return false;
    }

    //disconnect update

    QDomElement child = root.firstChildElement("group");
    while (!child.isNull()){
        parseTitleElement(child);
        child = child.nextSiblingElement("group");
    }

    // connect();
    return true;
}

void XMLManager::parseTitleElement(const QDomElement &element, DataTreeWidgetItem *parentItem){
    DataTreeWidgetItem *item = createChildItem(element, parentItem);

    QString title = element.firstChildElement("title").text();
//    if (title.isEmpty()){
//        title = QObject::tr("");
//    }
    item->setText(title);

    bool exclusive = (element.attribute("exclusive")=="1");
    item->setExclusive(exclusive);

    QDomElement child = element.firstChildElement();
    while (!child.isNull()){
        if (child.tagName() == "value"){
            DataTreeWidgetItem *childItem = createChildItem(child, item);

            QString title = child.firstChildElement("value").text();

            childItem->setText(title);

        }
    }
}

DataTreeWidgetItem *XMLManager::createChildItem(const QDomElement &element, DataTreeWidgetItem *parentItem){
    DataTreeWidgetItem *item;
    if (parentItem != nullptr){
        item = new DataTreeWidgetItem(parentItem);
    }
    else {
        item = new DataTreeWidgetItem(treeWidget);
    }
    return item;
}


