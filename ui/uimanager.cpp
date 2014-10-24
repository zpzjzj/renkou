#include <algorithm>
#include <memory>
#include <QApplication>
#include "display.h"
#include "entercalculate.h"
#include "evaluate.h"
#include "importbasicdata.h"
#include "importbasicpara.h"
#include "newproject.h"
#include "newprojectionwizard.hpp"
#include "openproject.h"
#include "ParasManager.hpp"
#include "searchobject.h"
#include "SelDispCombo.hpp"
#include "uimanager.h"
#include "UiGenerator.hpp"

UiManager::UiManager()
{
    ptrCollection.fill(nullptr);
}

namespace {
    QDialog* createSelDispCombo(UiManager* uiManager) {
        auto derived_ptr = new SelDispCombo();
        derived_ptr->setUiManager(uiManager);
        auto parasManagerPtr = new ParasManager();
        parasManagerPtr->read();
        auto uiGenerator = new UiGenerator(UiGenerator::PanelPtr(derived_ptr), parasManagerPtr);
        uiGenerator->generateUi();
        return derived_ptr;
    }
}

/** suppose the uiPage not existed before
  */
UiManager::uiPtr UiManager::create_ui(page uiPage){
    using namespace std;
    uiPtr ptr = nullptr;

    //create the ui object according to page value
    //TODO: the ctors of all ui need refining
    switch (uiPage) {
    case display :{
        auto derived_ptr = new Display();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case selDispCombo:
        ptr = uiPtr(createSelDispCombo(this));
        break;
    case enterCalculate:{
        auto derived_ptr = new EnterCalculate();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case evaluate:{
        auto derived_ptr = new Evaluate();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case importBasicData:{
        auto derived_ptr = new ImportBasicData();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case importBasicPara:{
        auto derived_ptr = new ImportBasicPara();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case newProject:{
        auto derived_ptr = new NewProject();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case openProject:{
        auto derived_ptr = new OpenProject();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case searchObject:{
        auto derived_ptr = new SearchObject();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);}
        break;
    case newprojectionwizard:{
        auto derived_ptr = new NewProjectionWizard();
        derived_ptr->setUiManager(this);
        ptr = uiPtr(derived_ptr);
    }
        break;

    default:
        break;
}//end of switch
ptrCollection[uiPage] = ptr;

return ptr;
}

UiManager::~UiManager()
{
}

void UiManager::active(UiManager::page uiPage)
{
    get_ui(uiPage)->show();
}

void UiManager::disactive(UiManager::page uiPage)
{
    get_ui(uiPage)->hide();
}

void UiManager::makeFront(UiManager::page uiPage)
{
    get_ui(uiPage)->exec();
}
