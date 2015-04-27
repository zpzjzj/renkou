#include "paraUtil.hpp"
#include "stlUtil.hpp"

namespace util {
bool isSelected(scheme::Para::SelectedType type) {
    return type != scheme::Para::SelectedType::INCOMPLETE;
}

bool isSelected(const scheme::Para& para) {
    return isSelected(para.getSelectedType());
}

bool isMultiSelected(const scheme::Para& para) {
    return para.getSelectedType() == scheme::Para::SelectedType::MULTIPLE;
}

bool isLeaf(const scheme::Para& para) {
    return para.getAndParas().empty() && para.getOrParas().empty();
}


scheme::Para::ParaSet::const_iterator getSelected(const scheme::Para& para) {
    auto &orParas = para.getOrParas();
    auto res = std::find_if(orParas.begin(), orParas.end(),
                 [](const scheme::Para::ParaPtr& ptr){
        return isSelected(*ptr);
    });
    return res;
}

using ParaSets = std::vector<scheme::Para::ParaSet>;
ParaSets expand(const scheme::Para& para) {
    const auto& andParas = para.getAndParas();
    if(!para.getOrParas().empty()) {
        ParaSets res;
        for(auto& orPara : para.getOrParas()) {
            if(util::isSelected(*orPara)) {
                res.push_back(util::add(andParas, orPara));
            }
        }
        return res;
    } else {
        return {andParas};
    }
}

}
