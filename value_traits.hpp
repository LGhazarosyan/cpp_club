//
// Created by Lusine Ghazarosyan on 24.04.21.
//

#ifndef LGHAZAROSYAN_VALUE_TRAITS_HPP
#define LGHAZAROSYAN_VALUE_TRAITS_HPP

#include <type_traits>

namespace lghazarosyan{

    template<typename T, typename U>
    struct is_same{
        static constexpr bool value = false;
    };

    template <typename T>
    struct is_same<T,T>{
        static constexpr bool value = true;
    };

    template<typename T, typename U>
    constexpr bool is_same_v = is_same<T,U>::value;

    struct true_type{
        static constexpr bool value = true;
    };

    struct false_type{
        static constexpr bool value = false;
    };

    namespace details{

        template <typename T>
        false_type is_base_helper(void * );

        template<typename T>
        true_type is_base_helper(T *);
    }
    template<typename Base, typename Derived>
    struct is_base_of{
        static constexpr bool value = decltype(details::is_base_helper<std::decay_t<Base>>(std::declval<std::decay_t<Derived>*>()))::value;
    };

    template<typename Base, typename Derived>
    constexpr bool is_base_of_v = is_base_of<Base,Derived>::value;

    namespace details{
    template <bool , class T, class ...Ts>
    struct check_is_same_as_pack{
        constexpr static bool value = lghazarosyan::is_same_v<std::decay_t<T>, typename std::decay<Ts...>::type>;
    };

    template <class T, class ...Ts>
    struct check_is_same_as_pack<false , T, Ts...>:lghazarosyan::false_type{};
    }

    template<class T, class...Ts>
    struct is_same_as_pack{
        constexpr static bool value = details::check_is_same_as_pack<sizeof...(Ts) == 1, T, Ts...>::value;
    };
};

#endif //LGHAZAROSYAN_VALUE_TRAITS_HPP
