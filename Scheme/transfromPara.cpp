#include "transfromPara.hpp"
#include "SchemeParameter.hpp"

/**
 * @author zhaoping
 */

namespace{
    using namespace scheme;
    /**
     * @brief expand one para into a set of paras
     * @param para
     * @return a forest of para tree with single orPara
     */
    Para::ParaSet expand(const Para& para) {
        Para::ParaSet res;
        for(const Para::ParaPtr& orPara : para.getOrParas()) {
            //split all combinations of paras into a set
            for(const Para::ParaPtr& singlePara : expand(*orPara)) {
                res.push_back(
                    std::make_shared<Para>(
                        Para(para.getName(), para.getKey(), para.getVal(),
                             para.getAndParas(), Para::ParaSet({singlePara}))));
            }
        }
        return res;
    }
}

///**
// * @brief scheme::expand
// * @param paraSet
// *          paras with single choice
// * @param variable
// *          para with multiple choice
// * @return combination of all posibilities
// */
//std::list<Para::ParaSet> scheme::expand(const Para::ParaSet& paraSet, const Para& variable) {
//    std::list<Para::ParaSet> res;
//    for(auto& para: ::expand(variable)){
//        Para::ParaSet set(paraSet);
//        set.push_back(para);
//        res.push_back(set);
//    }
//    return res;
//}

namespace{
    /**
     * @brief getValue get the string representation of value for a para
     *          eg. 方案选择: 农d11p15_非d11p15_z
     *              地区: 上海
     * @param para
     * @return
     */
    QString getValue(const Para& para){
        QString res = "";
        for(const auto& paraPtr: para.getAndParas()){
            //concatenate all the aspects
            if(paraPtr->getVal() != ""){
                if(res != "")
                    res += "_"; //spliter
                res += paraPtr->getVal() + getValue(*paraPtr);
            }
        }

        auto& orParas = para.getOrParas();
        if(orParas.size() == 1){ //single choice
            res += getValue(*orParas[0]);
        }else if(orParas.size() == 0){
            //TODO
        }else{
            //error
        }

        return res;
    }

    /**
     * @brief map the para into a key - value format
     * @param para
     * @return
     */
    std::pair<QString, QString> map(const Para& para){
        if(para.getKey() != ""){
            return std::pair<QString, QString>(para.getKey(), para.getVal());
        }//TODO
    }
}

/**
 * @brief map paras in paraSet to SchemeParamter
 * @param paraSet
 * @return a SchemeParameter
 */
std::shared_ptr<SchemeParameter> map(const Para::ParaSet& paraSet){
    std::shared_ptr<SchemeParameterDefault> parameter = std::make_shared<SchemeParameterDefault>();
    //TODO
    return parameter;
}
