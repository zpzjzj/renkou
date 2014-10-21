#ifndef TRANSFROMPARA_HPP
#define TRANSFROMPARA_HPP

# include "Para.hpp"
# include "SchemeParameter.hpp"
# include <list>
# include <memory>

namespace scheme{
    /**
     * @brief expand
     * @param paraSet para that have 0 or 1 orPara elem (single selection)
     * @param variable para that can have more than one orParas (multiple selection)
     * @return a list of comparing ParaSet
     */
    extern std::list<Para::ParaSet> expand(const Para::ParaSet& paraSet, const Para& variable);

    /**
     * @brief map the paraSet to SchemeParamter (actually the default parameter)
     * @param paraSet
     * @return the pointer to default parameter
     */
    extern std::shared_ptr<SchemeParameter> map(const Para::ParaSet& paraSet);
}
#endif // TRANSFROMPARA_HPP
