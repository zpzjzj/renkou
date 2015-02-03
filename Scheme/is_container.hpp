#include <boost/preprocessor/cat.hpp>
#include <type_traits>
#include <boost/mpl/bool.hpp>

template<bool T>
using bool_ = boost::mpl::bool_<T>;

namespace detail {
// a preprocess iteration will be better. I an not able to and not interested in making this done
#define TNAME value_type // value type
#include "has_xxx.hpp"
#define TNAME reference // reference
#include "has_xxx.hpp"
#define TNAME const_reference // const_reference
#include "has_xxx.hpp"
#define TNAME iterator // iterator
#include "has_xxx.hpp"
#define TNAME const_iterator // const_iterator
#include "has_xxx.hpp"
#define TNAME difference_type // difference_type
#include "has_xxx.hpp"
#define TNAME size_type // size_type
#include "has_xxx.hpp"
#define TNAME begin // begin
#include "has_mem.hpp"
#define TNAME cbegin // cbegin
#include "has_mem.hpp"
#define TNAME end // end
#include "has_mem.hpp"
#define TNAME cend // cend
#include "has_mem.hpp"
#define TNAME size // size
#include "has_mem.hpp"
#define TNAME max_size // max_size
#include "has_mem.hpp"
#define TNAME empty // empty
#include "has_mem.hpp"
}
#include "and.hpp"
//template <bool, class>
//struct is_container_impl {
//        static constexpr int value = false; // not a class
//};

//template <class T>
//struct is_container_impl<true, T> {
//    static constexpr int value =
//        detail::has_value_type<T>::value
//        && detail::has_reference<T>::value
//        && detail::has_const_reference<T>::value
//        && detail::has_const_iterator<T>::value
//        && detail::has_difference_type<T>::value
//        && detail::has_size_type<T>::value
//        && detail::has_mem_begin<T>::value
//        && detail::has_mem_cbegin<T>::value
//        && detail::has_mem_end<T>::value
//        && detail::has_mem_cend<T>::value
//        && detail::has_mem_size<T>::value
//        && detail::has_mem_max_size<T>::value
//        && detail::has_mem_empty<T>::value;
//    using type = boost::mpl::bool_<value>;
//};

//template <class T>
//struct is_container
//    :is_container_impl<std::is_class<T>::value, T> {};

template <typename T>
struct is_container 
    : and_<
        std::is_class<T>,
        detail::has_value_type<T>,
        detail::has_reference<T>,
        detail::has_const_reference<T>,
        detail::has_const_iterator<T>,
        detail::has_difference_type<T>,
        detail::has_size_type<T>,
        detail::has_mem_begin<T>,
        detail::has_mem_cbegin<T>,
        detail::has_mem_end<T>,
        detail::has_mem_cend<T>,
        detail::has_mem_size<T>,
        detail::has_mem_max_size<T>,
        detail::has_mem_empty<T> >{};

template <class T>
constexpr bool is_container_v = is_container<T>::value;
