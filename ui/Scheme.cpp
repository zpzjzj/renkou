#include "iterate.hpp"
#include "paraUtil.hpp"
#include "Scheme.hpp"
#include "Select.hpp"
#include <algorithm>
#include <QButtonGroup>
#include <QDate>
#include <QObject>
#include <string>

display::Policy::Policy(PolicyWidget policyWidgetPtr, TimeWidget timeWidgetPtr)
    : mPolicy(policyWidgetPtr), mTime(timeWidgetPtr){}

display::Policy::Policy(const Policy& policy)
    : QObject(), mPolicy(policy.mPolicy), mTime(policy.mTime), mParaPtr(policy.mParaPtr),
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

    util::buildComboBox(mPolicy, *mPolicyParaPtr);

    QObject::connect(mTime, util::Select<int>::overload_of(&QSpinBox::valueChanged), [this](int val) {
        mTimeParaPtr->setVal(std::to_string(val).c_str());
    });
    mTime->setMaximum(MAX_YEAR);
    mTime->setValue(QDate::currentDate().year());
    mPolicy->setEnabled(false);
    mTime->setEnabled(false);
}

void display::Policy::setVal(const Policy &other) {
    mPolicy->setCurrentIndex(other.mPolicy->currentIndex());
    mTime->setValue(other.mTime->value());
}

display::SchemeOption::SchemeOption(OptionWidget optionWidgetPtr)
    : mOption(optionWidgetPtr){}

void display::SchemeOption::bind(ParaPtr paraPtr) {
    mParaPtr = paraPtr;
    util::iterate([this](scheme::Para::ParaPtr& paraPtr, display::Policy& policy){
        policy.bind(paraPtr.get());
        QObject::connect(mOption, &QRadioButton::toggled, policy.mPolicy, &QComboBox::setEnabled);
        QObject::connect(mOption, &QRadioButton::toggled, policy.mTime, &QSpinBox::setEnabled);
    }, mParaPtr->getAndParas(), mPolicies);
}

void display::SchemeOption::setVal(const SchemeOption &other) {
    if(other.mOption->isChecked())
        mOption->click();
    util::iterate([](display::Policy& policy, const display::Policy& other) {
        policy.setVal(other);
    }, mPolicies, other.mPolicies);
}

void display::Scheme::setVal(const Scheme &other) {
    util::iterate([](display::SchemeOption& option, const display::SchemeOption& other) {
        option.setVal(other);
    }, mOptions, other.mOptions);
}

void display::Scheme::bind(ParaPtr paraPtr, QWidget* parent) {
    mParaPtr = paraPtr;
    auto btnGroupPtr = new QButtonGroup(parent);
    util::iterate([&btnGroupPtr, this](scheme::Para::ParaPtr& paraPtr, display::SchemeOption&schemeOption){
        schemeOption.bind(paraPtr.get());
        auto optionWidget = schemeOption.mOption;
        btnGroupPtr->addButton(optionWidget);
        QObject::connect(optionWidget, &QRadioButton::clicked, [this, paraPtr](int val) {
            if(val)
                util::selectPara(mParaPtr, paraPtr.get());
        });
    }, mParaPtr->getOrParas(), mOptions);
}
