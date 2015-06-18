#ifdef TNAME
#include <boost/preprocessor/cat.hpp>
/**
 * copy from wikibook
 **/
template <class T>
struct BOOST_PP_CAT(has_mem_, TNAME) {
    struct Fallback {int TNAME;};
    struct D : T, Fallback {};
    template <typename U, U> struct check;

    template <class>
    static constexpr bool test(...) {
        return true;
    }

    template <class U>
    static constexpr bool test(check<int Fallback::*, &U::TNAME>*) {
        return false;
    }

    static constexpr bool value = test<D>(nullptr);
    using type = ::bool_<value>;
};
#undef TNAME
#endif
