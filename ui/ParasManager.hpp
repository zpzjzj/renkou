#ifndef PARASMANAGER_HPP
#define PARASMANAGER_HPP
#include "../Scheme/Para.hpp"
#include "../Scheme/AbstractScheme.hpp"
#include "../Scheme/Singleton.hpp"
#include <QApplication>
#include <QDir>
#include <QMap>
#include <QObject>
#include <QStringListModel>

class ParasManager : public QObject
{
    Q_OBJECT
public:
    using AbstractSchemeList = std::vector<std::shared_ptr<AbstractScheme> >;
    using ParaRepre = std::pair<QString, QString>;//<!(outer representation, inner representation)
    using ParaValueMap = QMap<ParaRepre, ParaRepre>;
    using ParaPair = std::pair<ParaRepre, ParaRepre>;
public:
    ParasManager();
    void read(QString filename = PARA_PATH());
    const scheme::Para::ParaSet& getParaSet() const {return mParaSet;}
    const scheme::Para* getMultiSelPara() const {return mMultiSelPara;}
    void setVal(bool val, scheme::Para* dest);
    scheme::Para* addOrPara(scheme::Para* para, const scheme::Para& orPara);
    const scheme::Para* getParent(const scheme::Para* child) const {
        return mParentMap.value(const_cast<scheme::Para*>(child), nullptr);
    }
    const AbstractSchemeList& update();
    const AbstractSchemeList& getAbstractSchemeList() const {
        return mAbstractSchemeList;
    }
    QStringListModel* getModel() {return &mListModel;}
signals:
    void paraStateChanged(const scheme::Para*);
    void multiParaChanged(const scheme::Para*);
    void paraChanged(const scheme::Para*);
public slots:
    bool saveToFile(QString fname = PARA_PATH());
    void updateParasList(const scheme::Para *changed);
private:
    typedef QMap<scheme::Para*, scheme::Para*> ParaMap;
private:
    void buildMap(scheme::Para& para);//<!build mParentMap
    void updateSchemeList();
    static const QString& PARA_PATH();
private:
    scheme::Para::ParaSet mParaSet;
    ParaMap mParentMap;//!<(child, parent) map, for parent lookup
    scheme::Para* mMultiSelPara;
    //!<pointed at multiple selected para, when null means none

    ParaValueMap mResMap;//!<key - value map
    std::vector<std::vector<ParaPair>> mResList;//!<list<scheme>, scheme consists of list of pair
    QStringListModel mListModel;//!<model for display compairing schemes
    //shall not change until update() called
    AbstractSchemeList mAbstractSchemeList;

    static const QString PARA_ORI_PATH;
};

#endif // PARASMANAGER_HPP
