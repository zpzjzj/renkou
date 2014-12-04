#include "SchemeSel.hpp"
#include "ui_SchemeSel.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QObject>
#include <QRadioButton>

const QString SCHEME_PATH = ":/display/config/scheme.json";

namespace {
    const scheme::Para* getSelected(const scheme::Para& para) {
        using SelectedType = scheme::Para::SelectedType;
        const auto& set = para.getOrParas();
        const auto iter = std::find_if_not(set.begin(), set.end(), [](const scheme::Para::ParaPtr& ptr){
            return ptr->getSelectedType() == SelectedType::INCOMPLETE;
        });
        return iter == set.end() ? nullptr : iter->get();
    }

    QString toString_policy(const scheme::Para& policyPara) {
        QStringList strList;
        for(const auto &ptr : policyPara.getAndParas()) {
            if(!ptr->getOrParas().empty()) {
                strList << getSelected(*ptr)->getName();
            } else
                strList << ptr->getVal();
        }
        return strList.join(' ');
    }

    QString toString_schemeOption(const scheme::Para& schemeOption) {
        QStringList strList;
        for(const auto &ptr : schemeOption.getAndParas()) {
            strList << toString_policy(*ptr);
        }
        if(strList.isEmpty())
            strList << schemeOption.getName();
        return strList.join(',');
    }
    /**
     * @brief toString_partScheme
     * @param partScheme, para of agri / nonAgri
     * @return string representation of this scheme
     */
    QString toString_partScheme(const scheme::Para& partScheme) {
        return partScheme.getName() + ":" + toString_schemeOption(*getSelected(partScheme));
    }

    /**
     * @brief toString
     * @param scheme
     * @return string representation
     */
    QString toString(const scheme::Para &scheme) {
        QStringList strList;
        for(auto &ptr : scheme.getAndParas())
            strList << toString_partScheme(*ptr);
        return strList.join(';');
    }
}

SchemeSel::SchemeSel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchemeSel)
{
    ui->setupUi(this);
}

void SchemeSel::build() {
    read();
    buildScheme();
    bind();
    QObject::connect(ui->mAddSchemeButton, SIGNAL(clicked()), this, SLOT(addScheme()));
    QObject::connect(ui->mSyncButton, SIGNAL(clicked()), this, SLOT(synchronizeScheme()));
}

void SchemeSel::addScheme() {
    QString val = toString(mCurrScheme);
    if(std::none_of(mSchemeList.begin(), mSchemeList.end(),
                   [val](QCheckBox* ptr){
                        return ptr->text() == val;})) {
        auto checkBoxPtr = new QCheckBox(val, this);
        mSchemeList.append(checkBoxPtr);
        ui->mSchemeSetLayout->addWidget(checkBoxPtr);
        emit addScheme(mCurrScheme, checkBoxPtr);
    }
}

void SchemeSel::read() {
    QFile file(SCHEME_PATH);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open para file");
        return;
    }
    QString val = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(val.toUtf8()));
    mCurrScheme.read(doc.object());
}

SchemeSel::~SchemeSel()
{
    delete ui;
}

void SchemeSel::buildScheme() {
    display::Scheme& agriScheme = mAgriScheme;
    display::Scheme& nonAgriScheme = mNonAgriScheme;
    agriScheme.mOptions.push_back(display::SchemeOption(ui->mCurrButton));
    nonAgriScheme.mOptions.push_back(display::SchemeOption(ui->mCurrButton_2));

    display::SchemeOption agriOneStepOption(ui->mOneStepButton);
    display::SchemeOption nonAgriOneStepOption(ui->mOneStepButton_2);
    agriOneStepOption.mPolicies.push_back(display::Policy(ui->mOneStepComboBox, ui->mOneStepSpinBox));
    nonAgriOneStepOption.mPolicies.push_back(display::Policy(ui->mOneStepComboBox_2, ui->mOneStepSpinBox_2));
    agriScheme.mOptions.push_back(agriOneStepOption);
    nonAgriScheme.mOptions.push_back(nonAgriOneStepOption);

    display::SchemeOption agriTwoStepOption(ui->mTwoStepButton);
    display::SchemeOption nonAgriTwoStepOption(ui->mTwoStepButton_2);
    agriTwoStepOption.mPolicies.push_back(display::Policy(ui->mTwoStep_1_ComboBox, ui->mTwoStep_1_SpinBox));
    agriTwoStepOption.mPolicies.push_back(display::Policy(ui->mTwoStep_2_ComboBox, ui->mTwoStep_2_SpinBox));
    nonAgriTwoStepOption.mPolicies.push_back(display::Policy(ui->mTwoStep_1_ComboBox_2, ui->mTwoStep_1_SpinBox_2));
    nonAgriTwoStepOption.mPolicies.push_back(display::Policy(ui->mTwoStep_2_ComboBox_2, ui->mTwoStep_2_SpinBox_2));
    agriScheme.mOptions.push_back(agriTwoStepOption);
    nonAgriScheme.mOptions.push_back(nonAgriTwoStepOption);
}

void SchemeSel::bind() {
    for(auto& paraPtr : mCurrScheme.getAndParas()) {
        if(paraPtr->getName() == QObject::tr("农业")) {
            mAgriScheme.bind(paraPtr.get(), this);
        } else {
            mNonAgriScheme.bind(paraPtr.get(), this);
        }
    }
}

void SchemeSel::synchronizeScheme() {
    qDebug() << "SchemeSel::synchronizeScheme()";
    mNonAgriScheme.setVal(mAgriScheme);
}
