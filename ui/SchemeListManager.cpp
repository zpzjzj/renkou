#include "paraUtil.hpp"
#include "SchemeSel.hpp"
#include "SchemeListManager.hpp"
#include <algorithm>
#include <numeric>

namespace {
    bool isCheckBoxWithComboBox(const scheme::Para& para) {
        return !para.getName().isEmpty()
                && util::hasComboBox(para);
    }

    /**
     * @brief toString
     * @param checkBoxWithComboBoxPara
     *          satisfy condition in isCheckBoxWithComboBox(para)
     *          and is single selected
     * @return
     */
    QString toString(const scheme::Para& checkBoxWithComboBoxPara) {
        auto &orParas = checkBoxWithComboBoxPara.getOrParas();
        auto iter = std::find_if(orParas.begin(), orParas.end(),
                                 [](scheme::Para::ParaPtr ptr){
                return util::isSelected(*ptr);});
        return checkBoxWithComboBoxPara.getName() + " " + (*iter)->getName();
    }

    template<typename C>
    std::vector<QString> combine(C strs) {
        return std::accumulate(strs.begin(), strs.end(), std::vector<QString>{QString()},
                               [](std::vector<QString> x, std::vector<QString> y){
            std::vector<QString> res;
            for(auto x_str : x) {
                for(auto y_str : y) {
                    res.push_back(x_str.isEmpty() ? y_str : x_str + "/" + y_str);
                }
            }
            return res;
        });
    }
}

SchemeListManager::SchemeListManager(ParasManager *parasManager, QListWidget *listWidget, QObject *parent) :
    QObject(parent), mParasManager(parasManager), mListWidget(listWidget) {
    for(auto paraPtr : mParasManager->getParaSet()) {
        auto strs = toStrings(*paraPtr);
        qDebug() << paraPtr->getName();
        for(auto str : strs) {
            qDebug() << str;
        }
        mParaStrsMap.insert(paraPtr.get(), strs);
    }
    updateList();
    QObject::connect(mParasManager, SIGNAL(paraChanged(const scheme::Para*)), this, SLOT(updateSchemes(const scheme::Para*)));
}

void SchemeListManager::updateSchemes(const scheme::Para* paraPtr) {
    mParaStrsMap[paraPtr] = toStrings(*paraPtr);
    updateList();
}

void SchemeListManager::updateList() {
    mListWidget->clear();
    for(auto str : combine(mParaStrsMap.values())) {
        mListWidget->addItem(str);
    }
}

/**
 * @brief SchemeListManager::toStrings
 * @param para
 * @return string representation of para
 */
std::vector<QString> SchemeListManager::toStrings(const scheme::Para& para) {
    if(para.getName() == QObject::tr("方案选择")) {
        std::vector<QString> res;
        for(auto paraPtr : para.getOrParas()) {
            if(util::isSelected(*paraPtr)) {
                res.push_back(SchemeSel::toString(*paraPtr));
            }
        }
        return res;
    } else if(util::isLeaf(para)) {
        return {para.getName()};
    } else if(isCheckBoxWithComboBox(para)) {
        qDebug() << "isCheckBoxWithComboBox(para)" << para.getName();
        return {toString(para)};
    }

    std::vector<scheme::Para::ParaSet> paraSets;//combination of para
    auto& andParas = para.getAndParas();
    if(!para.getOrParas().empty()) {//combine orPara with andParas
        for(auto& paraPtr : para.getOrParas()) {
            if(util::isSelected(*paraPtr)) {
                auto paras(andParas);
                paras.push_back(paraPtr);
                paraSets.push_back(paras);
            }
        }
    } else {
        paraSets.push_back(andParas);
    }

    std::vector<QString> res;
    for(auto& paraSet : paraSets) {
        auto strs = toStrings(paraSet);
        res.insert(res.end(), strs.begin(), strs.end());
    }
    return res;
}

/**
 * @brief SchemeListManager::toStrings
 * @param paraSet (considered as list of andParas)
 * @return
 */
std::vector<QString> SchemeListManager::toStrings(scheme::Para::ParaSet paraSet) {
    QList<std::vector<QString> > strs;
    for(auto paraPtr : paraSet) {
        strs.push_back(toStrings(*paraPtr));
    }
    //combine strings
    return combine(strs);
}
