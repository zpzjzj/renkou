#ifdef TNAME
#include <type_traits>
#include <boost/preprocessor/cat.hpp>

//has_TNAME : is has typename as TNAME
template <class T>
struct BOOST_PP_CAT(has_, TNAME) {
    template <class>
    static constexpr bool test(...) {
        return false;
    }

    template <class U>
    static constexpr bool test(std::remove_reference_t<typename U::TNAME>*) {
        return true;
    }

    static constexpr bool value = test<T>(nullptr);
    using type = ::bool_<value>;
};

template <class T>
constexpr bool BOOST_PP_CAT(BOOST_PP_CAT(has_, TNAME), _v)
    = BOOST_PP_CAT(has_, TNAME)<T>::value;

#undef TNAME
#endif
