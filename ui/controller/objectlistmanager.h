#ifndef OBJECTLISTMANAGER_H
#define OBJECTLISTMANAGER_H

#include <QList>
#include "demoobject.h"

class ObjectListManager
{
public:
//    ObjectListManager();
    static ObjectListManager*getInstance(){
        if (!m_Instantce){
            m_Instantce = new ObjectListManager();
        }
        return m_Instantce;
    }

    QList<DemoObject> getObjects() const;
    const DemoObject& at(int index);
    void addObject(DemoObject &obj);

    int objectCount() const;
private:
    ObjectListManager();
    static ObjectListManager *m_Instantce;

    QList<DemoObject> objects;
};


#endif // OBJECTLISTMANAGER_H
