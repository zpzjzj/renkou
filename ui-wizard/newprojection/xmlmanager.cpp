#include "xmlmanager.hpp"
#include <QWidget>

QString& title::getSubtitleAt(int index)const{
    return subtitles->at(index);
}

XMLManager::XMLManager(QWidget *widget)
{

}

int XMLManager::size() const{
    return titleList->size();
}

bool XMLManager::read(QIODevice *device){

}
