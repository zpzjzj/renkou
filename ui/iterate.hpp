#ifndef ITERATE_HPP
#define ITERATE_HPP
#include <algorithm>
namespace util {
namespace detail {
    template <class F, class IterFirst, class ... Iter>
    void do_iter(IterFirst end, F f, IterFirst iterFirst, Iter... t) {
      while(iterFirst != end) {
        f(*(iterFirst++), *(t++)...);
      }
    }
}
    template <class F, class CF, class ... C>
    void iterate(F f, CF&& first, C&& ... c) {
      detail::do_iter(end(first), f, begin(first), begin(c)...);
    }
}

#endif // ITERATE_HPP
