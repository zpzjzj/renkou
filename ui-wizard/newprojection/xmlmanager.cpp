#include "xmlmanager.hpp"
#include "datatreewidget.h"
#include "datatreewidgetitem.h"
#include <QWidget>

XMLManager::XMLManager(DataTreeWidget *widget, QString &filetype)
    :treeWidget(widget),filetype(filetype)
{

}

bool XMLManager::read(QIODevice *device){
    QString errString;
    int errLine;
    int errColumn;

    if (!domDocument.setContent(device, true, &errString, &errLine, &errColumn)){
         QMessageBox::information(window(), tr("DOM XMLManager"),
                                 tr("Parse error at line%1, column %2:\n%3")
                                 .arg(errLine)
                                 .arg(errColumn)
                                 .arg(errString));
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != *filetype){
        QMessageBox::information(window(), tr("DOM XMLManager"),
                                 tr("The file is not an \"importdata\" or \"importparam\" file"));
        return false;
    }


}
