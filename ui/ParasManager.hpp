#ifndef PARASMANAGER_HPP
#define PARASMANAGER_HPP
#include "../Scheme/Para.hpp"
#include "../Scheme/AbstractScheme.hpp"
#include "../Scheme/Singleton.hpp"
#include <QApplication>
#include <QDir>
#include <QMap>
#include <QObject>

class ParasManager : public QObject
{
    Q_OBJECT
public:
    using AbstractSchemeList = std::vector<std::shared_ptr<AbstractScheme> >;

public:
    ParasManager();
    void read(QString filename = PARA_PATH());
    const scheme::Para::ParaSet& getParaSet() const {return mParaSet;}
    const scheme::Para* getMultiSelPara() const {return mMultiSelPara;}
    void setVal(bool val, scheme::Para* dest);
    scheme::Para* addOrPara(scheme::Para* para, const scheme::Para& orPara);
    const scheme::Para* getParent(const scheme::Para* child) const {
        auto iter = mParentMap.find(const_cast<scheme::Para*>(child));
        return iter == mParentMap.end() ? nullptr : iter.value();
    }
    const AbstractSchemeList& update();
    const AbstractSchemeList& getAbstractSchemeList() const {
        return mAbstractSchemeList;
    }
signals:
    void paraStateChanged(const scheme::Para*);
    void multiParaChanged(const scheme::Para*);
    void paraChanged(const scheme::Para*);
public slots:
    bool saveToFile(QString fname = PARA_PATH());
private:
    typedef QMap<scheme::Para*, scheme::Para*> ParaMap;
private:
    void buildMap(scheme::Para& para);//<!build mParentMap
private:
    scheme::Para::ParaSet mParaSet;
    ParaMap mParentMap;//<!(child, parent) map, for parent lookup
    scheme::Para* mMultiSelPara;
    //<!pointed at multiple selected para, when null means none

    //shall not change until update() called
    AbstractSchemeList mAbstractSchemeList;
    static const QString PARA_ORI_PATH;
private:
    static const QString& PARA_PATH();
};

#endif // PARASMANAGER_HPP
