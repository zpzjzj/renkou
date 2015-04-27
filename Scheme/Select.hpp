#ifndef SELECT_HPP
#define SELECT_HPP
namespace util {
template<typename... Args> struct Select {
    /**
     *  arg of overload_of is the Args vertion overload function ptr
     *  this make the compiler decide which overload function to use
     */
    template<typename C, typename R>
    static constexpr auto overload_of(R (C::*pmf)(Args...)) -> decltype(pmf) {
        return pmf;
    }

    template<typename R>
    static constexpr auto overload_of(R (*pmf)(Args...)) -> decltype(pmf) {
        return pmf;
    }
};
}
#endif // SELECT_HPP
