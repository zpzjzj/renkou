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

}
#endif // STLUTIL_HPP
