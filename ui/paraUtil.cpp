#include "paraUtil.hpp"
#include "Select.hpp"

namespace util{
    void selectPara(scheme::Para::Para* dest, scheme::Para* selected, bool isMultiSelect) {
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

    bool isSelected(scheme::Para::SelectedType type) {
        return type != scheme::Para::SelectedType::INCOMPLETE;
    }

    bool isSelected(const scheme::Para& para) {
        return isSelected(para.getSelectedType());
    }

    bool isMultiSelected(const scheme::Para& para) {
        return para.getSelectedType() == scheme::Para::SelectedType::MULTIPLE;
    }
}
