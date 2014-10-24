#ifndef UIGENERATOR_HPP
#define UIGENERATOR_HPP
#include "ParasManager.hpp"
#include "SelDispCombo.hpp"
#include <memory>

class UiGenerator
{
public:
    typedef std::unique_ptr<ParasManager> ParasManagerPtr;
    typedef std::shared_ptr<SelDispCombo> PanelPtr;
    UiGenerator(PanelPtr panel, ParasManager* ptr);
    void generateUi();
private:
    PanelPtr mPanel;
    ParasManagerPtr mParasManager;
    std::vector<std::shared_ptr<QWidget>> mWidgets;
};

#endif // UIGENERATOR_HPP
