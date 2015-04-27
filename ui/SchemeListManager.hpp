#ifndef SCHEMELISTMANAGER_HPP
#define SCHEMELISTMANAGER_HPP

#include "ParasManager.hpp"
#include "../Scheme/Para.hpp"
#include <QObject>
#include <QListWidget>
#include <QMap>
#include <vector>

class SchemeListManager : public QObject
{
    Q_OBJECT
public:
    typedef ParasManager* ParasManagerPtr;
public:
    SchemeListManager(ParasManagerPtr parasManager, QListWidget* listWidget, QObject *parent = 0);
public slots:
    void updateSchemes(const scheme::Para* paraPtr);
private:
    static std::vector<QString> toStrings(scheme::Para::ParaSet paraSet);
    static std::vector<QString> toStrings(const scheme::Para& para);
    void updateList();
private:
    ParasManagerPtr mParasManager;
    QListWidget* mListWidget;
    QMap<const scheme::Para*, std::vector<QString> > mParaStrsMap;
};

#endif // SCHEMELISTMANAGER_HPP
