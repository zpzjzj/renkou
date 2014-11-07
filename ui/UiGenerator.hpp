#ifndef UIGENERATOR_HPP
#define UIGENERATOR_HPP
#include "ParasManager.hpp"
#include "SelDispCombo.hpp"
#include "Singleton.hpp"
#include <memory>
#include <QButtonGroup>
#include <QGroupBox>
#include <QListWidgetItem>
#include <QMap>
#include <QMultiMap>
#include <QToolBox>

class UiGenerator : public QObject
{
    Q_OBJECT
public:
    typedef std::unique_ptr<ParasManager> ParasManagerPtr;
    typedef std::shared_ptr<SelDispCombo> PanelPtr;
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
    QWidget* generateUi(const scheme::Para& para, QWidget* parent);//<!dispatcher
    QGroupBox* createCheckBoxGroup(const scheme::Para &para, QWidget* parent);
    QListWidgetItem* createListWidgetItem(const scheme::Para &para, QListWidget *parent);
    QToolBox* createToolBox(const scheme::Para& para, QWidget* parent);
    QWidget* createSpecialParaWidget(const scheme::Para& para, QWidget* parent);//<!generate special para's UI
private:
    PanelPtr mPanel;
    ParasManagerPtr mParasManager;
    ButtonGroupMap mButtonGroupMap;
    ListWidgetItemMap mListWidgetItemMap;
    Singleton<SelectedTypeIconMap> mIconMapOwner;
};

#endif // UIGENERATOR_HPP
