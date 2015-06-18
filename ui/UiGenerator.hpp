#ifndef UIGENERATOR_HPP
#define UIGENERATOR_HPP
#include "ParasManager.hpp"
#include "SchemeListManager.hpp"
#include "SchemeSel.hpp"
#include "SelDispCombo.hpp"
#include "Singleton.hpp"
#include <functional>
#include <memory>
#include <QButtonGroup>
#include <QComboBox>
#include <QGroupBox>
#include <QListWidgetItem>
#include <QMap>
#include <QMultiMap>
#include <QTabWidget>
#include <QToolBox>

class UiGenerator : public QObject
{
    Q_OBJECT
public:
    typedef std::shared_ptr<SchemeListManager> SchemeListManagerPtr;
    typedef std::unique_ptr<ParasManager> ParasManagerPtr;
    typedef std::shared_ptr<SelDispCombo> PanelPtr;
    typedef std::function<QWidget* (scheme::Para& para, QWidget* parent)> GenerateFunc;
public:
    UiGenerator(PanelPtr panel, ParasManager* ptr);
    void generateUi();
private:
    typedef QMap<const scheme::Para*, QListWidgetItem*> ListWidgetItemMap;
    typedef QMap<scheme::Para::SelectedType, const QIcon*> SelectedTypeIconMap;
    typedef QMap<const scheme::Para*, QButtonGroup*> ButtonGroupMap;
private slots:
    void changeIcon(const scheme::Para* changedPara);
    void changeParasExclusive(const scheme::Para* multiPara);
private:
    QWidget* generateUi(scheme::Para &para, QWidget* parent, QButtonGroup *btnGroupPtr = nullptr);//<!dispatcher
    QComboBox* createComboBox(scheme::Para &para, QWidget* parent);
    QGroupBox* createCheckBoxGroup(scheme::Para &para, QWidget* parent, QButtonGroup *buttonGroupPtr = nullptr);
    QListWidgetItem* createListWidgetItem(scheme::Para &para, QListWidget *parent);
    QToolBox* createToolBox(scheme::Para& para, QWidget* parent);
    QTabWidget* createTabWidget(scheme::Para& para, QWidget* parent, GenerateFunc func);
    QTabWidget* createTabWidget(scheme::Para &para, QWidget *parent);
    QWidget* createSpecialParaWidget(scheme::Para &para, QWidget* parent);//<!generate special para's UI
    SchemeSel* createSchemeSelWidget(scheme::Para &para, QWidget* parent);
    QButtonGroup* createButtonGroup(scheme::Para &para, QWidget* parent, bool isExclusive = false);
private:
    PanelPtr mPanel;
    ParasManagerPtr mParasManager;
//    SchemeListManagerPtr mSchemeListManager;
    ButtonGroupMap mButtonGroupMap;
    ListWidgetItemMap mListWidgetItemMap;
    Singleton<SelectedTypeIconMap> mIconMapOwner;
    Singleton<QIcon> mInitIcon;
};

#endif // UIGENERATOR_HPP
