#include "Scheme.hpp"
#include "Select.hpp"
#include <algorithm>
#include <QButtonGroup>
#include <QDate>
#include <QObject>
#include <string>

namespace {
    void selectPara(scheme::Para::Para* dest, scheme::Para* selected, bool isMultiSelect = false) {
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
}

display::Policy::Policy(PolicyWidget policyWidgetPtr, TimeWidget timeWidgetPtr)
    : mPolicy(policyWidgetPtr), mTime(timeWidgetPtr){}

display::Policy::Policy(const Policy& policy)
    : mPolicy(policy.mPolicy), mTime(policy.mTime), mParaPtr(policy.mParaPtr),
        mPolicyParaPtr(policy.mPolicyParaPtr), mTimeParaPtr(policy.mTimeParaPtr){}

void display::Policy::bind(ParaPtr paraPtr) {
    qDebug() << "display::Policy::bind()" << "name" << paraPtr->getName();
    mParaPtr = paraPtr;
    scheme::Para::ParaSet set = mParaPtr->getAndParas();
    // match para
    for(auto paraPtr : set) {
        if(paraPtr->getName() == "unsigned")
            mTimeParaPtr = paraPtr.get();
        else
            mPolicyParaPtr = paraPtr.get();
    }

    // add to comboBox list
    for(auto paraPtr : mPolicyParaPtr->getOrParas()) {
        mPolicy->addItem(paraPtr->getName());
    }

    auto func = [this](int index) {
        selectPara(mPolicyParaPtr, (mPolicyParaPtr->getOrParas())[index].get());
    };

    QObject::connect(mPolicy, Select<int>::overload_of(&QComboBox::currentIndexChanged), func);
    func(mPolicy->currentIndex());

    QObject::connect(mTime, Select<int>::overload_of(&QSpinBox::valueChanged), [this](int val) {
        mTimeParaPtr->setVal(std::to_string(val).c_str());
    });
    mTime->setMaximum(MAX_YEAR);
    mTime->setValue(QDate::currentDate().year());
}

display::SchemeOption::SchemeOption(OptionWidget optionWidgetPtr)
    : mOption(optionWidgetPtr){}

void display::SchemeOption::bind(ParaPtr paraPtr) {
    qDebug() << "display::SchemeOption::bind()" << "para name" << paraPtr->getName();
    mParaPtr = paraPtr;
    qDebug() << "policy num" << mParaPtr->getAndParas().size() << "==" << mPolicies.size();
    int index = 0;
    for(auto paraPtr : mParaPtr->getAndParas()) {
        qDebug() << "index in SchemeOption::bind" << index;
        mPolicies.at(index).bind(paraPtr.get());
        ++index;
    }
}

void display::Scheme::bind(ParaPtr paraPtr, QWidget* parent) {
    qDebug() << "display::Scheme::bind()" << "para name" << paraPtr->getName();
    mParaPtr = paraPtr;
    auto btnGroupPtr = new QButtonGroup(parent);
    int index = 0;
    for(auto paraPtr : mParaPtr->getOrParas()) {
        qDebug() << "index in Scheme::bind()" << index;
        auto &schemeOption = mOptions.at(index);
        schemeOption.bind(paraPtr.get());
        auto optionWidget = schemeOption.mOption;
        btnGroupPtr->addButton(optionWidget);
        QObject::connect(optionWidget, &QRadioButton::clicked, [this, paraPtr](int val) {
            if(val)
                selectPara(mParaPtr, paraPtr.get());
        });
        ++index;
    }
}
