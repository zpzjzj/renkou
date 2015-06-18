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
    static constexpr bool test(rm_ref_t<typename U::TNAME>*) {
        return true;
    }

    static constexpr bool value = test<T>(nullptr);
    using type = ::bool_<value>;
};
#undef TNAME
#endif
