#ifndef UIGENERATOR_HPP
#define UIGENERATOR_HPP
#include "ParasManager.hpp"
#include "SelDispCombo.hpp"
#include <memory>
#include <QButtonGroup>
#include <QGroupBox>
#include <QMultiMap>

class UiGenerator : public QObject
{
    Q_OBJECT
public:
    typedef std::unique_ptr<ParasManager> ParasManagerPtr;
    typedef std::shared_ptr<SelDispCombo> PanelPtr;
    UiGenerator(PanelPtr panel, ParasManager* ptr);
    void generateUi();
private:
    typedef QMultiMap<const scheme::Para*, QButtonGroup*> ButtonGroupMap;
private slots:
    void changeIcon(const scheme::Para* changedPara);
    void changeParasExclusive(const scheme::Para* multiPara);
private:
    QGroupBox* createCheckBoxGroup(const scheme::Para &para, const scheme::Para *rootParaPtr, QWidget* parent);
private:
    PanelPtr mPanel;
    ParasManagerPtr mParasManager;
    ButtonGroupMap mButtonGroupMap;
};

#endif // UIGENERATOR_HPP
