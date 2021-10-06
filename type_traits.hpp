//
// Created by Lusine Ghazarosyan on 24.04.21.
//

#ifndef LGHAZAROSYAN_TYPE_TRAITS_HPP
#define LGHAZAROSYAN_TYPE_TRAITS_HPP
namespace lghazarosyan{

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

}

#endif //LGHAZAROSYAN_TYPE_TRAITS_HPP
