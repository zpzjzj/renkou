#include "../Scheme/stlUtil.hpp"
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
     * @return checkbox's name + option's name
     */
    QString toString_checkBoxWithCombo(const scheme::Para& para) {
        auto &orParas = para.getOrParas();
        auto iter = std::find_if(orParas.begin(), orParas.end(),
                                 [](scheme::Para::ParaPtr ptr){
                return util::isSelected(*ptr);});
        return para.getName() + " " + (*iter)->getName();
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
    auto key = paraPtr;
    while(!mParaStrsMap.contains(key) && key != nullptr) {
        key = mParasManager->getParent(key);
    }
    if(key != nullptr) {
        qDebug() << key->getName();
        mParaStrsMap[key] = toStrings(*key);
    }
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
        return {toString_checkBoxWithCombo(para)};
    }

    std::vector<QString> res;
    for(auto& paraSet : util::expand(para)) {
        util::append(res, toStrings(paraSet));
    }
    return res;
}

/**
 * @brief SchemeListManager::toStrings
 *          each para call toStrings(para)
 *          then combine all results
 * @param paraSet (considered as list of andParas)
 * @return combination result of paraSet
 */
std::vector<QString> SchemeListManager::toStrings(scheme::Para::ParaSet paraSet) {
    std::vector<std::vector<QString> > strs(paraSet.size());
    std::transform(paraSet.begin(), paraSet.end(), strs.begin(),
                   [](const scheme::Para::ParaPtr& paraPtr){
        return toStrings(*paraPtr);
    });
    //combine strings
    return combine(strs);
}
