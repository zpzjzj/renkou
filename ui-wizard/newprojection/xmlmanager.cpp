#include "xmlmanager.hpp"
#include "datatreewidget.h"
#include "datatreewidgetitem.h"
#include <QWidget>



XMLManager::XMLManager(DataTreeWidget* widget,
                       QString& filetype)
    : treeWidget(widget),
      filetype(filetype)
{

}

bool XMLManager::read(QIODevice *device){
    xml.setDevice(device);

    if (xml.readNextStartElement()) {
        if (xml.name().compare(*filetype, Qt::CaseInsensitive) == 0){
            readXML();
        }
        else {
            xml.raiseError(QObject::tr("The file is not match."));
        }
    }

    return !xml.error();
}

void XMLManager::readXML(){
    Q_ASSERT(xml.isStartElement()
             && xml.name().compare(*filetype, Qt::CaseInsensitive) == 0);

    while (xml.readNextStartElement()){
        if (xml.name() == "extension"){
            extension = new QString(xml.readElementText());
        }
        else if (xml.name() == "dataitems"){
            readTitle(nullptr);
        }
        else {
            xml.skipCurrentElement();
        }
    }
}

void XMLManager::readTitle(DataTreeWidgetItem *item){

    DataTreeWidgetItem *title = createChildItem(item);

}

void XMLManager::readExtension(){
    Q_ASSERT(xml.isStartElement() && xml.name() == "extension")
}
DataTreeWidgetItem *XMLManager::createChildItem(DataTreeWidgetItem *item)
{
    DataTreeWidgetItem *childItem;
    if (item != nullptr){
        childItem = new DataTreeWidgetItem(item);
    }
    else {
        childItem = new DataTreeWidgetItem(treeWidget);
    }
    childItem->setText(xml.name().toString());
    return childItem;
}

QString& title::getSubtitleAt(int index)const{
    return subtitles->at(index);
}

int XMLManager::size() const{
    return titleList->size();
}
