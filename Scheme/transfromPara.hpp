#ifndef TRANSFROMPARA_HPP
#define TRANSFROMPARA_HPP

# include "Para.hpp"
# include "SchemeParameter.hpp"
# include <list>
# include <memory>

namespace scheme{
    /**
     * @brief map the paraSet to SchemeParamter (actually the default parameter)
     * @param paraSet
     * @return the pointer to default parameter
     */
    extern std::shared_ptr<SchemeParameter> map(const Para::ParaSet& paraSet);
}
#endif // TRANSFROMPARA_HPP
