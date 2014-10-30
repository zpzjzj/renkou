#include "UiGenerator.hpp"
#include <QButtonGroup>
#include <QCheckBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <map>
#include <numeric>
#include <utility>

UiGenerator::UiGenerator(PanelPtr panel, ParasManager* ptr) :
    mPanel(panel), mParasManager(ptr){
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
     * @return
     */
    bool isCheckBoxGroup(const scheme::Para& para) {
        const auto &orParas = para.getOrParas();
        return std::accumulate(orParas.begin(), orParas.end(), para.getAndParas().empty(), [](bool x, const scheme::Para::ParaPtr y){
            return x && isLeaf(*y);
        });
    }
}

QGroupBox* UiGenerator::createCheckBoxGroup(const scheme::Para& para, const scheme::Para* rootParaPtr, QWidget* parent) {
    QVBoxLayout* vbox = new QVBoxLayout(parent);
    auto buttonGroupPtr = new QButtonGroup(parent);
    buttonGroupPtr->setExclusive(false);
    mButtonGroupMap.insert(rootParaPtr, buttonGroupPtr);
    for(auto paraPtr : para.getOrParas()) {
        auto button = new QCheckBox(paraPtr->getName(), parent);
        auto ptr = paraPtr.get();
        QObject::connect(button, &QCheckBox::stateChanged, [this, ptr](bool val){
            this->mParasManager->setVal(val, ptr);
        });
        buttonGroupPtr->addButton(button);
        vbox->addWidget(button);
    }
    vbox->addStretch();
    auto groupBoxPtr = new QGroupBox(para.getName(), parent);
    groupBoxPtr->setLayout(vbox);
    return groupBoxPtr;
}

void UiGenerator::generateUi() {
    auto paraListWidgetPtr = mPanel->getParaListWidget();
    auto stackedViewPtr = mPanel->getStackedWidget();

    for(const auto& paraPtr : mParasManager->getParaSet()) {
        const auto& para = *paraPtr;
        if(isCheckBoxGroup(para)) {
            stackedViewPtr->addWidget(createCheckBoxGroup(para, paraPtr.get(), mPanel.get()));
            paraListWidgetPtr->addItem(para.getName());
        }
    }
}

//TODO
void UiGenerator::changeIcon(const scheme::Para* changedPara) {
    qDebug() << "para changed:" << changedPara->getKey();
    qDebug() << "now state:" << changedPara->getSelectedType();
}
void UiGenerator::changeParasExclusive(const scheme::Para* multiPara) {
    qDebug() << "changeParasExclusive() slot" << "multipara" << multiPara;
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
