#ifndef PARASMANAGER_HPP
#define PARASMANAGER_HPP
#include "../Scheme/Para.hpp"
#include <QMap>
#include <QObject>

class ParasManager : public QObject
{
    Q_OBJECT
public:
    ParasManager();
    void read();
    const scheme::Para::ParaSet& getParaSet() const {return mParaSet;}
    const scheme::Para* getMultiSelPara() const {return mMultiSelPara;}
    void setVal(bool val, scheme::Para* dest);
    scheme::Para* addOrPara(scheme::Para* para, const scheme::Para& orPara);
signals:
    void paraStateChanged(const scheme::Para*);
    void multiParaChanged(const scheme::Para*);
private:
    typedef QMap<scheme::Para*, scheme::Para*> ParaMap;
private:
    void buildMap(scheme::Para& para);//<!build mParentMap
private:
    scheme::Para::ParaSet mParaSet;
    ParaMap mParentMap;//<!(child, parent) map, for parent lookup
    scheme::Para* mMultiSelPara;
    //<!pointed at multiple selected para, when null means none
    static const QString PARA_PATH;
};

#endif // PARASMANAGER_HPP
