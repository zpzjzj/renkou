#include "transfromPara.hpp"
#include "paraUtil.hpp"
#include "stlUtil.hpp"
#include "Select.hpp"
#include <numeric>
#include <vector>
#include <utility>

/**
 * @author zhaoping
 */

namespace{
    using namespace scheme;
    using Pair = std::pair<QString, QString>;//key - value
    using PairSet = std::vector<Pair>;//corresponding to a scheme
    using PairSets = std::vector<PairSet>;//combinations of scheme

    /**
     * @brief getValue get the string representation of value for a para
     *          eg. 地区: 上海
     * @param para
     * @return para's val
     */
    PairSets getPairs(const Para& para, const QString& key){
        qDebug() << "getPairs called";
        PairSets res;
        for(auto &paraPtr : para.getOrParas()) {
            if(util::isSelected(*paraPtr)) {
                qDebug() << "found selected";
                if(!paraPtr->getVal().isEmpty()) {
                    qDebug() << "getPairs" << key << paraPtr->getVal();
                    res.push_back(PairSet{std::make_pair(key, paraPtr->getVal())});
                } else if(!paraPtr->getOrParas().empty()) {
                    util::append(res, getPairs(*paraPtr, key));
                }
            }
        }
        return res;
    }

    /**
     * @brief getValue for scheme
     *          eg. 方案选择: 农d11p15_非d11p15
     * @param para
     * @return str representation for scheme
     */
    QString getValue_scheme(const Para& para) {
        QStringList strList;
        for(const auto& scheme : para.getAndParas()) {
            QString str = scheme->getVal();
            auto& option = *(util::getSelected(*scheme));
            if(option->getAndParas().empty())
                str += option->getVal();
            else {
                for(auto &step : option->getAndParas()) {
                    for(auto &part : step->getAndParas()) {
                        if(part->getOrParas().empty()) {//year number
                            str += part->getVal().right(2);
                        }
                        else {
                            str += (*util::getSelected(*part))->getVal();
                        }
                    }
                }
            }
            strList.append(str);
        }
        return strList.join('_');
    }

    PairSets getPairs_scheme(const Para& para, const QString& key) {
        PairSets res;
        for(auto &paraPtr : para.getOrParas()) {
            if(util::isSelected(*paraPtr)) {
                res.push_back(PairSet{std::make_pair(key, getValue_scheme(*paraPtr))});
            }
        }
        return res;
    }

    /**
     * @brief getPair
     * @param para with key
     * @return pairs of orPara value
     */
    PairSets getPairs(const Para& para) {
        auto &key = para.getKey();
        if(key == "koujinplusshiji") {
            return getPairs_scheme(para, key);
        } else {
            return getPairs(para, key);
        }
    }

    /**
     * @brief isToExpand
     * @param para
     * @return is suitable to expand
     */
    bool isToExpand(const Para& para) {
        return para.getKey().isEmpty();
    }

    PairSets expand(const Para::ParaSet& paraSet);
    /**
     * @brief expand one para into a set of subparas
     * @param para
     * @return combinations of paras (andPara, orPara)
     */
    PairSets expand(const Para::ParaPtr& paraPtr) {
        if(!isToExpand(*paraPtr)) {
            return getPairs(*paraPtr);
        } else {
            PairSets res;
            for(auto &set : util::expand(*paraPtr)) {
                util::append(res, expand(set));
            }
            return res;
        }
    }

    void printSets(const PairSets& sets) {
        for(auto& pairSet : sets) {
            for(auto &pair : pairSet) {
                qDebug() << pair.first << pair.second;
            }
            qDebug() << "~~~pairSet~~~~";
        }
    }
    /**
     * @brief expand
     *          each call expand, then form a vector of paraSet
     *          then combine all of them into one
     * @param paraSet
     * @return
     */
    PairSets expand(const Para::ParaSet& paraSet) {
        qDebug() << "PairSets expand(const Para::ParaSet& paraSet)";
        std::vector<PairSets> pairs(paraSet.size());
        std::transform(paraSet.begin(), paraSet.end(), pairs.begin(),
                       util::Select<const Para::ParaPtr&>::overload_of(&expand));
        for(auto &sets : pairs) {
            printSets(sets);
            qDebug() << "=====pairSets=====";
        }

        //do combine
        auto res = std::accumulate(pairs.begin(), pairs.end(),
                               PairSets{PairSet{}},
                               [](PairSets& x, PairSets& y){
            PairSets res;
            for(auto &set_x : x) {
                for(auto &set_y : y) {
                    res.push_back(util::add(set_x, set_y));
                }
            }
            return res;
        });
        return res;
    }
}

namespace scheme {

/**
 * @brief map paras in paraSet to SchemeParamter
 * @param paraSet
 * @return a SchemeParameter
 */
std::vector<std::shared_ptr<AbstractScheme> > map(const Para::ParaSet& paraSet) {
    auto buffer = std::make_shared<SchemeBuffer>();
    PairSets pairSets = expand(paraSet);
    qDebug() << "res in std::shared_ptr<SchemeParameter> map(const Para::ParaSet& paraSet)";
    printSets(pairSets);
    std::vector<std::shared_ptr<AbstractScheme> > abstractSchemes;
    abstractSchemes.reserve(pairSets.size());
    for(PairSet& pairSet : pairSets) {
        std::shared_ptr<SchemeParameter> paraPtr = std::make_shared<SchemeParameterDefault>();
        for(Pair& pair : pairSet) {
            paraPtr->set(pair.first, pair.second);
        }
        abstractSchemes.push_back(std::make_shared<AbstractScheme>(paraPtr, buffer));
    }

    return abstractSchemes;
}

}
