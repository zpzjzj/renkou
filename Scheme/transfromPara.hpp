#ifndef TRANSFROMPARA_HPP
#define TRANSFROMPARA_HPP

# include "Para.hpp"
# include "SchemeParameter.hpp"
# include "AbstractScheme.hpp"
# include <list>
# include <memory>

namespace scheme{
    /**
     * @brief map the paraSet to SchemeParamter (actually the default parameter)
     * @param paraSet
     * @return the pointer to default parameter
     */
    extern std::vector<std::shared_ptr<AbstractScheme> > map(const Para::ParaSet& paraSet);
}
#endif // TRANSFROMPARA_HPP
