#include "value_traits.hpp"
#include "type_traits.hpp"
#include <__config>
#include <cstddef>

namespace lghazarosyan{

namespace details{
    template <typename, typename, std::size_t>
    struct tuple_element_index_helper;
}

//here sizeof...(Ts) != 0 guaranteed
template<class ...Ts>
class tuple {
private:
    template<class U, class ... UTs>
    struct tuple_from_RestTypes
    {
        using type = tuple<UTs...>;
    };

    using T = typename first_type_of_pack<Ts...>::type;
    using RestTypes = typename tuple_from_RestTypes<Ts...>::type;
public:
    tuple() = default;
    tuple(const tuple&) = default;
    tuple(tuple&&) = default;

    template <class U, class ...UTs, class = lghazarosyan::enable_if_t< sizeof...(Ts) - 1 == sizeof...(UTs) && std::is_constructible_v<T, U>>, class = lghazarosyan::enable_if_t<sizeof...(UTs) != 0 || !lghazarosyan::is_same_v<std::decay_t<U>, std::decay_t<tuple>>>>
    tuple(U&&, UTs&&...);

    tuple& operator =(tuple);
    ~tuple() = default;

    void swap(tuple &);


private:
    T _current;
    RestTypes _rest;

    template<std::size_t, typename ...UTs>
    friend auto get(const tuple<UTs...>&);

    template<typename, class ...UTs>
    friend auto get(const tuple<UTs...>&);

    template<typename ...UTs1, typename ...UTs2>
    friend bool operator ==(const tuple<UTs1...>&, const tuple<UTs2...>&);

    template <std::size_t, typename>
    friend struct tuple_element;

    template <typename, typename, std::size_t>
    friend struct details::tuple_element_index_helper;
};

template<>
class tuple<>{
public:
    void swap(tuple &){}
};

template <class ...Ts>
auto make_tuple(Ts&&... args){
    return tuple<remove_reference_t<Ts>...>(std::forward<Ts>(args)...);
}

template <class ...Ts>
tuple<Ts&...> tie(Ts&... args){
    return tuple<Ts&...>(args...);
}


template<class ...Ts>
template<class U, class...UTs, class, class>
tuple<Ts...>::tuple(U && first, UTs&&... rest):_current(std::forward<U>(first)), _rest(std::forward<UTs>(rest)...){}

template<class ...Ts>
tuple<Ts...>& tuple<Ts...>::operator = (tuple other){
    swap(*this, other);
    return *this;
}

template<class ...Ts>
void tuple<Ts...>::swap(tuple &other){
    using std::swap;
    swap(_current, other._current);
    _rest.swap(other._rest);
}

template<std::size_t Index, class ...Ts>
auto get(const tuple<Ts...>& tup) {
    static_assert(sizeof...(Ts) > 0, "Requested Index goes beyond tuples size");
    if constexpr(Index == 0) {
        return tup._current;
    } else {
        return get<Index - 1>(tup._rest);
    }
}

template<typename T, class ...Ts>
auto get(const tuple<Ts...>& tup) {
    static_assert(sizeof...(Ts) > 0, "Requested type does not exist in tuple");
    if constexpr(is_same_v<typename tuple<Ts...>::T, T> ) {
        return tup._current;
    } else {
        return get<T>(tup._rest);
    }
}

bool operator == (const tuple<>&, const tuple<>&) {
    return true;
}

template<typename ...Ts, typename ...UTs>
bool operator == (const tuple<Ts...>& tup1, const tuple<UTs...>& tup2) {
    if constexpr (sizeof...(Ts) != 0 && sizeof...(UTs) != 0) {
        if constexpr(is_same_v<typename tuple<Ts...>::T, typename tuple<UTs...>::T>) {
            if (tup1._current == tup2._current) {
                return tup1._rest == tup2._rest;
            }
        }
    }
    return false;
}

template<typename ...Ts, typename ...UTs>
bool operator != (const tuple<Ts...>& tup1, const tuple<UTs...>& tup2) {
    return !(tup1 == tup2);
}

template<class >
struct tuple_size;

template <class ...Ts>
struct tuple_size<tuple<Ts...>> {
    constexpr static std::size_t value = sizeof...(Ts);
};

template<class T>
std::size_t tuple_size_v = tuple_size<T>::value;

template <std::size_t, typename>
struct tuple_element;

template<std::size_t Index, typename ...Ts>
struct tuple_element<Index, tuple<Ts...>> {
    using type = typename tuple_element<Index - 1, typename tuple<Ts...>::RestTypes>::type;
};

template<typename ...Ts>
struct tuple_element<0, tuple<Ts...>> {
    using type = typename tuple<Ts...>::T;
};

//If the index is beyond the type will be void
template<std::size_t Index>
struct tuple_element<Index, tuple<>> {
    using type = void;
};

template<>
struct tuple_element<0, tuple<>> {
    using type = void;
};

template<std::size_t Index, typename T>
using tuple_element_t = typename tuple_element<Index, T>::type;

namespace details {

template <typename T, typename ...Ts, std::size_t Index>
struct tuple_element_index_helper<T, tuple<Ts...>, Index> {
    constexpr static std::size_t value = is_same_v<T, typename  tuple<Ts...>::T> ? Index : tuple_element_index_helper<T, typename tuple<Ts...>::RestTypes, Index + 1>::value;
};

template <typename T, std::size_t Index>
struct tuple_element_index_helper<T, tuple<>, Index> {
    constexpr static std::size_t value = static_cast<std::size_t>(-1);
};

}

template<typename T, typename U>
struct tuple_element_index : details::tuple_element_index_helper<T, U, 0> {};

template<typename T, typename U>
constexpr static std::size_t tuple_element_index_v = tuple_element_index<T, U>::value;

}
