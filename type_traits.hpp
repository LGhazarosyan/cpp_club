//
// Created by Lusine Ghazarosyan on 24.04.21.
//

#ifndef LGHAZAROSYAN_TYPE_TRAITS_HPP
#define LGHAZAROSYAN_TYPE_TRAITS_HPP

#include "value_traits.hpp"

namespace lghazarosyan {

template<bool condition ,typename  Type = void>
struct enable_if{
};

template<class Type>
struct enable_if<true,Type>{
    using type = Type;
};

template<bool condition,typename Type = void>
using enable_if_t = typename enable_if<condition,Type>::type;

namespace details{
template< class, class T, class ...Ts>
struct first_type_of_pack_helper{
    using type = T;
};
}

template<class ...Ts>
struct first_type_of_pack: public details::first_type_of_pack_helper<lghazarosyan::enable_if_t<sizeof...(Ts) != 0>, Ts...>{};

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

template<class Callable, typename... Ts>
struct return_type {
	using inner_type = decltype(details::is_callable_func<Callable, Ts...>(0));
	using type = typename inner_type::type2;
	static_assert(is_same_v<typename inner_type::type1, true_type>, "Callable object is not callable with given arguments");
};

template<class Callable, typename... Ts>
using return_type_t = typename return_type<Callable, Ts...>::type;
	
} // namespace lghazarosyan

#endif //LGHAZAROSYAN_TYPE_TRAITS_HPP 