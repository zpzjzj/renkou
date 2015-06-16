#include "paraUtil.hpp"
#include "Select.hpp"
#include <numeric>

namespace util{
    void selectPara(scheme::Para* dest, scheme::Para* selected, bool isMultiSelect) {
        using SelectedType = scheme::Para::SelectedType;
        scheme::Para::ParaSet& set = dest->getOrParas();
        int selCnt = 0;
        for(scheme::Para::ParaPtr& option : set) {
            if(option.get() == selected) {
                option->setSelectedType(SelectedType::SINGLE);
                ++selCnt;
            } else {
                if(option->getSelectedType() != SelectedType::INCOMPLETE) {
                    if(isMultiSelect)
                        ++selCnt;
                    else
                        option->setSelectedType(SelectedType::INCOMPLETE);
                }
            }
        }
        dest->setSelectedType(selCnt > 1 ? SelectedType::MULTIPLE : SelectedType::SINGLE);
    }

    void buildComboBox(QComboBox *&comboBox, scheme::Para& para) {
        for(auto paraPtr : para.getOrParas()) {
            comboBox->addItem(paraPtr->getName());
        }
        auto func = [&para](int index) {
            selectPara(&para, (para.getOrParas())[index].get());
        };
        QObject::connect(comboBox, Select<int>::overload_of(&QComboBox::currentIndexChanged), func);
        para.getOrParas()[comboBox->currentIndex()]->setSelectedType(scheme::Para::SelectedType::SINGLE);
    }

    /**
     * @brief isCheckBoxGroup
     *          check if para's children are all leaves;
     *          and has no andParas
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

    bool hasComboBox(const scheme::Para& para) {
        return para.getTags().contains(scheme::Para::Tag::SINGLE_SELECT);
    }
}
