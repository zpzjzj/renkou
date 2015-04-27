#ifndef PARAUTIL_H
#define PARAUTIL_H

#include "Para.hpp"

namespace util {
    bool isSelected(scheme::Para::SelectedType type);
    bool isSelected(const scheme::Para& para);
    bool isMultiSelected(const scheme::Para& para);
    bool isLeaf(const scheme::Para& para);
    scheme::Para::ParaSet::const_iterator getSelected(const scheme::Para& para);
    /**
     * @brief expand, combinate para's orParas with andParas
     * @param para
     * @return combinations of paras
     */
    std::vector<scheme::Para::ParaSet> expand(const scheme::Para& para);
}

#endif // PARAUTIL_H
