#include <boost/mpl/and.hpp>

template <typename T, typename ...Args>
struct and_ : boost::mpl::and_<T, and_<Args...> >{};

template <typename T>
struct and_<T> : T {};
