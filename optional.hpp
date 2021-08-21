#include<iostream>
#include <type_traits>
#include <optional>

#include "type_traits.hpp"
#include "value_traits.hpp"


//provides weak exception safity

namespace lghazarosyan{
    struct nullopt_t{
        explicit constexpr nullopt_t(int) {}
    };

    inline constexpr nullopt_t nullopt(0);

    template<class T>
    class optional{
    public:
        using value_type = T;

    private:
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using rvalue_reference = T&&;
        using const_rvalue_reference = const T&&;
    public:
        optional() = default;

        //this trick is for not calling this templated function indtead of move or copy constructors
        template <class ...Ts, class = lghazarosyan::enable_if_t<std::is_constructible_v<value_type,Ts...> &&  !is_same_as_pack<optional<T>, Ts...>::value>,  class =  lghazarosyan::enable_if_t<!lghazarosyan::is_same_v<std::decay_t<optional<T>>, nullopt_t>>>
        optional(Ts&& ...args)noexcept(std::is_nothrow_constructible_v<value_type,Ts...>);

        optional(const optional&)noexcept(std::is_nothrow_copy_constructible_v<value_type>);
        optional(optional&&)noexcept(std::is_nothrow_move_constructible_v<value_type>);
        optional(const nullopt_t&)noexcept;

        optional& operator =(optional) noexcept(std::is_nothrow_swappable_v<value_type>);
        optional& operator = (const nullopt_t& )noexcept(std::is_nothrow_destructible_v<value_type>);

        //this trick is for not calling this templated function indtead of move or copy assignment operator
        template<class U, class = lghazarosyan::enable_if_t<std::is_assignable_v<T, U> && !lghazarosyan::is_same_v<std::decay_t<optional<T>>,std::decay_t<U>>>, class =  lghazarosyan::enable_if_t<!lghazarosyan::is_same_v<std::decay_t<optional<T>>, nullopt_t>>>
        optional& operator = (U&&) noexcept(std::is_nothrow_assignable_v<T, U>);

        ~optional();

    public:
        bool has_value()const noexcept;
        operator bool()const noexcept;

        reference operator *() noexcept;
        const_reference operator *()const noexcept;
        pointer operator ->() noexcept;
        const_pointer operator ->()const noexcept;

        reference value()&;
        const_reference value()const&;
        rvalue_reference value()&&;
        const_rvalue_reference value()const&&;

        template <class U, class = lghazarosyan::enable_if_t<std::is_constructible_v<value_type, U>>>
        value_type value_or(U&&)const & noexcept(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_assignable_v<value_type, U>);

        template <class U, class = lghazarosyan::enable_if_t<std::is_constructible_v<value_type, U>>>
        value_type value_or(U&& value)&& noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_assignable_v<value_type, U>);

        void reset()noexcept(std::is_nothrow_destructible_v<value_type>);
        template <class ...Ts, class = lghazarosyan::enable_if_t<std::is_constructible_v<value_type,Ts...>>>
        void emplace(Ts&&...args)noexcept(std::is_nothrow_constructible_v<value_type, Ts...> && std::is_nothrow_destructible_v<value_type>);

        void swap(optional&)noexcept(std::is_nothrow_move_constructible_v<value_type> && std::is_nothrow_destructible_v<value_type> && std::is_nothrow_swappable_v<value_type>);

        bool operator == (const optional& other)const noexcept;
        bool operator != (const optional& other)const noexcept;
        bool operator == (const nullopt_t& opt)const noexcept;
        bool operator != (const nullopt_t& opt)const noexcept;


    private:
        const_pointer ptr()const noexcept;
        pointer ptr() noexcept;

    private:
        unsigned char _ptr[sizeof(value_type)];
        bool _has_value = false;
    };

    template <class T>
    template <class ...Ts, class, class >
    optional<T>:: optional(Ts&&... args)noexcept(std::is_nothrow_constructible_v<value_type,Ts...>):_has_value(true){
        new(_ptr)value_type(std::forward<Ts>(args)...);
    }

    template<class T>
    optional<T>:: optional(const optional&other)noexcept(std::is_nothrow_copy_constructible_v<value_type>):_has_value(other._has_value){
        if(has_value()){
            new(_ptr)T(*other);
        }
    }

    template<class T>
    optional<T>::optional(optional&& other)noexcept(std::is_nothrow_move_constructible_v<value_type>):_has_value(other._has_value){
        if(has_value()){
            new(_ptr)T(std::move(*other));
        }
    }

    template<class T>
    optional<T>::optional(const nullopt_t&)noexcept:_has_value(false){}

    template<class T>
    optional<T>& optional<T>::operator =(optional other)noexcept(std::is_nothrow_swappable_v<value_type>){
        swap(other);
        return *this;
    }

    template<class T>
    optional<T>& optional<T>::operator =(const nullopt_t&)noexcept(std::is_nothrow_destructible_v<value_type>){
        if(has_value()){
            ptr()->~T();
        }
        _has_value = false;
        return *this;
    }

    template<class T>
    template<class U, class, class>
    optional<T>& optional<T>::operator = (U&& value) noexcept(std::is_nothrow_assignable_v<value_type, U>){
        if(has_value()){
            ptr()->~T();
        }
        new(_ptr)T(std::forward<T>(value));
        _has_value = true;
        return *this;
    }

    template<class T>
    optional<T>::~optional(){
        if(_has_value){
           ptr()->~T();
        }
    }

    template<class T>
    bool optional<T>::has_value()const noexcept{
        return _has_value;
    }

    template<class T>
    optional<T>::operator bool()const noexcept{
        return has_value();
    }

    template<class T>
    typename optional<T>::reference optional<T>::operator *() noexcept{
        return *ptr();
    }

    template<class T>
    typename optional<T>::const_reference optional<T>::operator *()const noexcept{
        return *ptr();
    }

    template<class  T>
    typename optional<T>::pointer optional<T>::operator ->()noexcept{
        return &(*ptr());
    }

    template<class T>
    typename optional<T>::const_pointer optional<T>::operator ->()const noexcept{
        return &(*ptr());
    }

    template<class T>
    typename optional<T>::reference optional<T>::value()&{
        if(!has_value()){
            throw std::bad_optional_access();
        }
        return *ptr();
    }

    template<class T>
    typename optional<T>::const_reference optional<T>::value()const&{
        if(!has_value()){
            throw std::bad_optional_access();
        }
        return *ptr();
    }

    template<class T>
    typename optional<T>::rvalue_reference optional<T>::value()&&{
        if(!has_value()){
            throw std::bad_optional_access();
        }
        _has_value = false;
        return std::move(*ptr());
    }

    template<class T>
    typename optional<T>::const_rvalue_reference optional<T>::value()const&& {
        if(!_has_value){
            throw std::bad_optional_access();
        }
        return *ptr();
    }

    template<class T>
    template<class U, class>
    typename optional<T>::value_type optional<T>::value_or(U&& value)const &noexcept(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_assignable_v<value_type, U>){
        if(_has_value){
            return *ptr();
        }
        return std::forward<U>(value);
    }

    template<class T>
    template<class U, class>
    typename optional<T>::value_type optional<T>::value_or(U&& value)&&noexcept(std::is_nothrow_move_constructible_v<T>&&std::is_nothrow_assignable_v<value_type, U>){
        if(_has_value){
            _has_value = false;
            return std::move(*ptr());
        }
        return std::forward<U>(value);
    }

    template<class T>
    void optional<T>::reset()noexcept(std::is_nothrow_destructible_v<value_type>){
        if(_has_value){
            ptr()->~T();
            _has_value = false;
        }
    }

    template<class T>
    template<class ...Ts, class >
    void optional<T>::emplace(Ts&&...args)noexcept(std::is_nothrow_constructible_v<value_type, Ts...> && std::is_nothrow_destructible_v<value_type>){
        if(_has_value){
            ptr()->~T();
        }
        new (_ptr)T(args...);
        _has_value = true;
    }

    template<class T>
    void optional<T>::swap(optional&other)noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_destructible_v<T> && std::is_nothrow_swappable_v<T>){
        using std::swap;
        swap(_has_value, other._has_value);
        if(!has_value() && !other.has_value()){
            return;
        }
        if(has_value() && other.has_value()){
            swap(*ptr(),*other.ptr());
            return;
        }
        if(!has_value()){
            new(other._ptr)T(std::move(*ptr()));
            ptr()->~T();
            return;
        }
        new(_ptr)T(std::move(*other.ptr()));
        other.ptr()->~T();
    }

    template <class T>
    typename optional<T>::const_pointer optional<T>::ptr()const noexcept{
        return reinterpret_cast<const T*>(_ptr);
    }

    template <class T>
    typename optional<T>::pointer optional<T>::ptr()noexcept{
        return reinterpret_cast<T*>(_ptr);
    }

    template <class T>
    bool optional<T>::operator == (const optional& other)const noexcept{
        if(_has_value != other._has_value){
            return false;
        }
        return !has_value() || **this == *other;
    }

    template <class T>
    bool optional<T>::operator != (const optional& other)const noexcept{
        return !(*this == other);
    }

    template <class T>
    bool optional<T>::operator == (const nullopt_t& opt)const noexcept{
        return !has_value();
    }

    template <class T>
    bool optional<T>::operator != (const nullopt_t& opt)const noexcept{
        return !(*this == opt);
    }


template<class T>
class optional<T[]>;

template<class T, class ...Ts, class = lghazarosyan::enable_if_t<std::is_constructible_v<T,Ts...>>>
optional<T> make_optional(Ts...args){
    return optional<T>(args...);
}
};
