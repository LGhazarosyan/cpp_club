//
// Created by Lusine Ghazarosyan on 24.04.21.
//

#ifndef LGHAZAROSYAN_TYPE_TRAITS_HPP
#define LGHAZAROSYAN_TYPE_TRAITS_HPP

#include "value_traits.hpp"

namespace lghazarosyan {

//
// ---- enable_if ----
//

template<bool condition ,typename  Type = void>
struct enable_if {
};

template<class Type>
struct enable_if<true,Type> {
    using type = Type;
};

template<bool condition,typename Type = void>
using enable_if_t = typename enable_if<condition,Type>::type;

//
// ---- first_type_of_pack ----
//

namespace details {

template< class, class T, class ...Ts>
struct first_type_of_pack_helper{
    using type = T;
};

} // namespace details

template<class ...Ts>
struct first_type_of_pack: public details::first_type_of_pack_helper<lghazarosyan::enable_if_t<sizeof...(Ts) != 0>, Ts...>{};

//
// ---- remove_reference ----
//

template<class T>
struct remove_reference {
    using type = T;
};

template<class T>
struct remove_reference< T&> {
    using type = T;
};

template<class T>
struct remove_reference< T&&> {
    using type = T;
};

template<class T>
using remove_reference_t = typename remove_reference<T>::type;

//
// ---- is_callable ----
//

namespace details {

template <class T, class U>
struct pair_helper {
	using type1 = T;
	using type2 = U;
};

template <class Callable, typename... Ts>
auto is_callable_func(int) -> pair_helper<true_type, decltype((*declval<Callable*>())(declval<Ts>()...))>;

template<class Callable, typename... Ts>
auto is_callable_func(long) -> pair_helper<false_type, void>;

template<class ReturnType, class Callable, typename... Ts>
struct is_callable_helper {
	using type = decltype(is_callable_func<Callable, Ts...>(0));
	static constexpr bool value = is_same_v<typename type::type1, true_type> && is_same_v<typename type::type2, ReturnType>;
};

}; // namespace details

template<class ReturnType, class Callable, typename... Ts>
struct is_callable: details::is_callable_helper<ReturnType, Callable, Ts...>{};

template<class ReturnType, class Callable, typename...Ts>
bool constexpr is_callable_v = is_callable<ReturnType, Callable, Ts...>::value;

//
// ---- return_type ----
//

template<class Callable, typename... Ts>
struct return_type {
	using inner_type = decltype(details::is_callable_func<Callable, Ts...>(0));
	using type = typename inner_type::type2;
	static_assert(is_same_v<typename inner_type::type1, true_type>, "Callable object is not callable with given arguments");
};

template<class Callable, typename... Ts>
using return_type_t = typename return_type<Callable, Ts...>::type;


//
// ---- is_convertible ----
//
 
namespace details {

template <class Type1, class Type2>
auto is_convertible_helper(int) -> pair_helper<true_type, decltype(static_cast<Type1>(declval<Type2>()))>;

template <class Type1, class Type2>
auto is_convertible_helper(long) -> pair_helper<false_type, false_type>;

} // namespace lghazarosyan 

template <class Type1, class Type2>
struct is_convertible: decltype(details::is_convertible_helper<Type1, Type2>(0))::type1{};

template <class Type1, class Type2>
constexpr bool is_convertible_v = is_convertible<Type1, Type2>::value;

// 
// ---- is_constructible ----
//
//

namespace details {

template <class Type, class ...Ts>
auto is_constructible_helper(int) -> pair_helper<true_type, decltype(Type(declval<Ts>()...))>;

template <class Type, class ...Ts>
auto is_constructible_helper(long) -> pair_helper<false_type, false_type>;
} // namespace details

template<class ...Ts>
struct is_constructible;

// This works as if the relationship is checked in a context not related to Type. So no matter where called,
// protected and private things are not taken into account 
template<class Type, class ...Ts>
struct is_constructible<Type, Ts...>: decltype(details::is_constructible_helper<Type,Ts...>(0))::type1{};

// This is done for class pointers and references. As C style cast can break all inheritance rules, this is needed
// for private/protected inheritance to be taken into account
template<class Type1, class Type2>
struct is_constructible<Type1*, Type2*>: is_convertible<Type1*, Type2*>{};

template<class Type1, class Type2>
struct is_constructible<Type1&, Type2&>: is_constructible<Type1*, Type2*>{};

template<class Type>
struct is_constructible<Type*, Type*>: is_convertible<Type*, Type*>{};

template<class Type>
struct is_constructible<Type&, Type&>: is_convertible<Type&, Type&>{};

template <class T, class ...Ts>
constexpr bool is_constructible_v = is_constructible<T, Ts...> :: value;

//Something wrong with decltype, when E has private move and copy ctor, still the main implementation gives true
//TODO: find out why
template <class Type>
struct is_constructible<Type, Type>: bool_constant<is_constructible_v<Type, const Type&> || is_constructible_v<Type, Type&&>> {}; 

} // namespace lghazarosyan

#endif //LGHAZAROSYAN_TYPE_TRAITS_HPP 
