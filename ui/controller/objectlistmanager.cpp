#include "objectlistmanager.h"

ObjectListManager::ObjectListManager()
{
    objects.clear();
}

QList<DemoObject> ObjectListManager::getObjects()const{
    return objects;
}

const DemoObject& ObjectListManager::back() {
    return objects.back();
}
const DemoObject& ObjectListManager::at(int index){
    if (index < objects.count() && index >=0){
        return objects.at(index);
    }
    return DemoObject();
}

void ObjectListManager::addObject(DemoObject &obj){
    objects.append(obj);
}

void ObjectListManager::deleteObjectAt(int index) {
    objects.removeAt(index);
}

int ObjectListManager::objectCount() const{
    return objects.count();
}

ObjectListManager *ObjectListManager::m_Instantce = nullptr;
