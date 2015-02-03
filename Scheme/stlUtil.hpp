#ifndef STLUTIL_HPP
#define STLUTIL_HPP

#include <iterator>
#include <utility>
#include "add.hpp"

namespace util {

template <template<typename...> class C1, template<typename...> class C2, typename T>
void append(C1<T>& c1, const C2<T>& c2) {
    c1.insert(std::end(c1), std::begin(c2), std::end(c2));
}


//template <template<typename...> class C1, template<typename...> class C2, typename T>
//decltype(auto) add(C1<T>& c1, const C2<T>& c2) {
//    auto res(c1);
//    append(res, c2);
//    return res;
//}

//template <template<typename...> class C, typename Param>
//decltype(auto) add(C<Param> res, const Param& arg) {
//    res.push_back(arg);
//    return res;
//}

//template <template<typename...> class C, typename Param, typename... Params>
//decltype(auto) add(C<Param>& c, const Param& arg, const Params&... args) {
//    return add(add(c, arg), args...);
//}

//template <template<typename...> class C, typename Param, typename... Params>
//decltype(auto) add(C<Param>&& c, const Param& arg, const Params&... args) {
//    return add(add(std::move(c), arg), args...);
//}

}
#endif // STLUTIL_HPP
