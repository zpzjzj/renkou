#include "objectlistmanager.h"

ObjectListManager::ObjectListManager()
{
    objects.clear();

    QString str = " quanguo";
    DemoObject obj(1900, str);
    objects.append(obj);
}

QList<DemoObject> ObjectListManager::getObjects()const{
    return objects;
}

const DemoObject& ObjectListManager::at(int index){
    if (index < objects.count() && index >=0){
        return objects.at(index);
    }
}

void ObjectListManager::addObject(DemoObject &obj){
    objects.append(obj);
}

int ObjectListManager::objectCount() const{
    return objects.count();
}

ObjectListManager *ObjectListManager::m_Instantce = nullptr;
