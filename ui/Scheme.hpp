#ifndef SCHEME_HPP
#define SCHEME_HPP

#include "../Scheme/Para.hpp"
#include <QComboBox>
#include <QObject>
#include <QRadioButton>
#include <QSpinBox>

namespace display {
typedef scheme::Para* ParaPtr;
struct Policy : public QObject{
public:
    typedef QComboBox* PolicyWidget;
    typedef QSpinBox* TimeWidget;
    enum {MAX_YEAR = 3000};
public:
    Policy(PolicyWidget policyWidgetPtr, TimeWidget timeWidgetPtr);
    Policy(const Policy& policy);
    void bind(ParaPtr paraPtr);
public:
    PolicyWidget mPolicy;
    TimeWidget mTime;
    ParaPtr mParaPtr;
private:
    ParaPtr mPolicyParaPtr;
    ParaPtr mTimeParaPtr;
};

struct SchemeOption {
public:
    typedef QRadioButton* OptionWidget;
    typedef std::vector<Policy> PolicySet;
public:
    SchemeOption(OptionWidget optionWidgetPtr);
    void bind(ParaPtr paraPtr);
public:
    OptionWidget mOption;
    PolicySet mPolicies;
    ParaPtr mParaPtr;
};

struct Scheme {
public:
    typedef std::vector<SchemeOption> OptionSet;
    void bind(ParaPtr paraPtr, QWidget* parent);
public:
    OptionSet mOptions;
    ParaPtr mParaPtr;
};

}

#endif // SCHEME_HPP
