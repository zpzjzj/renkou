#include "paraUtil.hpp"
#include "SchemeSel.hpp"
#include "Select.hpp"
#include "UiGenerator.hpp"
#include <QButtonGroup>
#include <QCheckBox>
#include <QFile>
#include <QIcon>
#include <QToolBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <map>
#include <numeric>
#include <utility>

const QString ICON_PATH = ":/image/";
const QString ICOMPLETE_ICON_NAME = "lampGrey.gif";
const QString COMPLETE_ICON_NAME = "lampYellow.gif";
const QString MULTIPLE_SELECTED_ICON_NAME = "lampMulti.gif";

UiGenerator::UiGenerator(PanelPtr panel, ParasManager* ptr) :
    mPanel(panel), mParasManager(ptr), mIconMapOwner([](){
        return SelectedTypeIconMap{
            std::make_pair(scheme::Para::SelectedType::INCOMPLETE, new QIcon(ICON_PATH + ICOMPLETE_ICON_NAME)),
            std::make_pair(scheme::Para::SelectedType::SINGLE, new QIcon(ICON_PATH + COMPLETE_ICON_NAME)),
            std::make_pair(scheme::Para::SelectedType::MULTIPLE, new QIcon(ICON_PATH + MULTIPLE_SELECTED_ICON_NAME))
        };
    }){
    QObject::connect(mParasManager.get(), SIGNAL(paraStateChanged(const scheme::Para*)),
                     this, SLOT(changeIcon(const scheme::Para*)));
    QObject::connect(mParasManager.get(), SIGNAL(multiParaChanged(const scheme::Para*)),
                     this, SLOT(changeParasExclusive(const scheme::Para*)));
}

namespace{

    bool isLeaf(const scheme::Para& para) {
        return para.getAndParas().empty() && para.getOrParas().empty();
    }

    /**
     * @brief isCheckBoxGroup
     *          check if para's children are all leaves;
     *
     * @param paraPtr
     * @return isCheckBoxGroup
     */
    bool isCheckBoxGroup(const scheme::Para& para) {
        const auto &orParas = para.getOrParas();
        return std::accumulate(orParas.begin(), orParas.end(),
                               para.getAndParas().empty(), [](bool x, const scheme::Para::ParaPtr y){
            return x && isLeaf(*y);
        });
    }
}

QGroupBox* UiGenerator::createCheckBoxGroup(scheme::Para &para, QWidget* parent) {
    QGridLayout* gridLayout = new QGridLayout(parent);
    auto buttonGroupPtr = new QButtonGroup(parent);
    buttonGroupPtr->setExclusive(false);
    mButtonGroupMap.insert(&para, buttonGroupPtr);
    for(auto paraPtr : para.getOrParas()) {
        auto button = new QCheckBox(paraPtr->getName(), parent);
        auto ptr = paraPtr.get();
        QObject::connect(button, &QCheckBox::stateChanged, [this, ptr](bool val){
            mParasManager->setVal(val, ptr);
        });
        buttonGroupPtr->addButton(button);
        int row = gridLayout->rowCount();
        int col = 0;
        gridLayout->addWidget(button, row, col++);
        if(!paraPtr->getOrParas().empty()) {
            auto comboBox = createComboBox(*paraPtr, parent);
            QObject::connect(button, &QCheckBox::toggled, comboBox, &QComboBox::setEnabled);
            gridLayout->addWidget(comboBox, row, col);
        }
    }
    auto groupBoxPtr = new QGroupBox(parent);
    groupBoxPtr->setLayout(gridLayout);
    return groupBoxPtr;
}

QComboBox* UiGenerator::createComboBox(scheme::Para &para, QWidget* parent) {
    auto comboBox = new QComboBox(parent);
    util::buildComboBox(comboBox, para);
    return comboBox;
}

QListWidgetItem* UiGenerator::createListWidgetItem(scheme::Para &para, QListWidget* parent) {
    auto icon = mIconMapOwner.getInstance()[para.getSelectedType()];
    auto res = new QListWidgetItem(*icon, para.getName(), parent);
    mListWidgetItemMap.insert(&para, res);
    return res;
}

SchemeSel* UiGenerator::createSchemeSelWidget(scheme::Para& para, QWidget* parent) {
    auto schemeSel = new SchemeSel(parent);
    schemeSel->build();
    auto buttonGroupPtr = new QButtonGroup(parent);
    buttonGroupPtr->setExclusive(false);
    mButtonGroupMap.insert(&para, buttonGroupPtr);

    QObject::connect(schemeSel, util::Select<const scheme::Para&,
                     SchemeSel::SchemeWidgetPtr>::overload_of(&SchemeSel::addScheme),
                     [this, &para, buttonGroupPtr](const scheme::Para& scheme, SchemeSel::SchemeWidgetPtr btnPtr){
                        auto ptr = mParasManager->addOrPara(&para, scheme);
                        buttonGroupPtr->addButton(btnPtr);
                        QObject::connect(btnPtr, &QCheckBox::stateChanged, [this, ptr](bool val){
                            mParasManager->setVal(val, ptr);
                        });
    });
    return schemeSel;
}

QWidget* UiGenerator::createSpecialParaWidget(scheme::Para& para, QWidget* parent) {
    QWidget* res = nullptr;
    const auto& name = para.getName();
    if(name == QObject::tr("方案选择")) {
        res = createSchemeSelWidget(para, parent);
    } else if(name == QObject::tr("基本参数选择")) {
        res = createTabWidget(para, parent, [this](scheme::Para &para, QWidget *parent){
            return createCheckBoxGroup(para, parent);
        });
    }
    return res;
}

QToolBox* UiGenerator::createToolBox(
        scheme::Para& para,
        QWidget* parent) {
    QToolBox* res = new QToolBox();
    auto buttonGroupPtr = new QButtonGroup(parent);
    buttonGroupPtr->setExclusive(false);
    mButtonGroupMap.insert(&para, buttonGroupPtr);
    for(const auto& paraPtr : para.getOrParas()) {
        QWidget* page = generateUi(*paraPtr, parent);
        res->addItem(page, paraPtr->getName());
        // add child buttons to button group
        for(auto &btn : mButtonGroupMap[paraPtr.get()]->buttons()) {
            buttonGroupPtr->addButton(btn);
        }
    }
    return res;
}

QTabWidget* UiGenerator::createTabWidget(
        scheme::Para& para,
        QWidget* parent,
        GenerateFunc func) {
    QTabWidget* res = new QTabWidget(parent);
    for(const auto& paraPtr : para.getAndParas()) {
        QWidget* page = func(*paraPtr, parent);
        res->addTab(page, paraPtr->getName());
    }
    return res;
}

QTabWidget* UiGenerator::createTabWidget(scheme::Para &para, QWidget *parent) {
    return createTabWidget(para, parent, [this](scheme::Para &para, QWidget *parent){
        return generateUi(para, parent);
    });
}

QWidget* UiGenerator::generateUi(scheme::Para& para, QWidget* parent) {
    QWidget* res = nullptr;
    if(isCheckBoxGroup(para)) {
        res = createCheckBoxGroup(para, parent);
    } else if(!para.getOrParas().empty()) {
        res = createToolBox(para, parent);
    } else if(!para.getAndParas().empty()) {
        res = createTabWidget(para, parent);
    }
    return res;
}

void UiGenerator::generateUi() {
    auto paraListWidgetPtr = mPanel->getParaListWidget();
    auto stackedViewPtr = mPanel->getStackedWidget();
    auto parent = mPanel.get();

    for(auto& paraPtr : mParasManager->getParaSet()) {
        auto& para = *paraPtr;
        QWidget* specialWidget = createSpecialParaWidget(para, parent);
        if(specialWidget != nullptr) {
            stackedViewPtr->addWidget(specialWidget);
        } else {
            stackedViewPtr->addWidget(generateUi(para, parent));
        }
        paraListWidgetPtr->addItem(createListWidgetItem(para, paraListWidgetPtr));
    }
}

void UiGenerator::changeIcon(const scheme::Para* changedPara) {
    QListWidgetItem* item = mListWidgetItemMap[changedPara];
    item->setIcon(*mIconMapOwner.getInstance()[changedPara->getSelectedType()]);
}
void UiGenerator::changeParasExclusive(const scheme::Para* multiPara) {
    static const scheme::Para* lastMultiPara = nullptr;
    for(const auto& paraPtr : mParasManager->getParaSet()) {
        if(paraPtr.get() != multiPara) {
            for(auto groupBox : mButtonGroupMap.values(paraPtr.get())) {
                /**
                  * when multiPara is nullptr, means multi is some -> null
                  *     then all paras exclusive = false
                  * when multiPara is not null, means null -> some
                  *     then all other paras exclusive = true
                  */
                groupBox->setExclusive(multiPara != nullptr);
            }
        }
    }
    changeIcon(lastMultiPara != nullptr ? lastMultiPara : multiPara);
    lastMultiPara = multiPara;
}
