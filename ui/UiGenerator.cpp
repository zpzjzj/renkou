#include "UiGenerator.hpp"
#include <QCheckBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <numeric>

UiGenerator::UiGenerator(PanelPtr panel, ParasManager* ptr) :
    mPanel(panel), mParasManager(ptr){
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

    QGroupBox* createCheckBoxGroup(const scheme::Para& para) {
        auto groupBoxPtr = new QGroupBox();
        QVBoxLayout *vbox = new QVBoxLayout();
        for(const auto& paraPtr : para.getOrParas()) {
            vbox->addWidget(new QCheckBox(paraPtr->getName()));
        }
        groupBoxPtr->setLayout(vbox);
        return groupBoxPtr;
    }
}

void UiGenerator::generateUi() {
    auto paraListWidgetPtr = mPanel->getParaListWidget();
    auto stackedViewPtr = mPanel->getStackedWidget();

    for(const auto& paraPtr : mParasManager->getParaSet()) {
        const auto& para = *paraPtr;
        if(isCheckBoxGroup(para)) {
            stackedViewPtr->addWidget(createCheckBoxGroup(para));
            paraListWidgetPtr->addItem(para.getName());
        }
    }
}
