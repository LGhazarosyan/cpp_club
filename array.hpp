//
// Created by Lusine Ghazarosyan on 21.04.21.
//

#ifndef LGHAZAROSYAN_ARRAY_HPP
#define LGHAZAROSYAN_ARRAY_HPP
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"

//TODO: add not default constructible value_type support
namespace lghazarosyan{
    template<typename T, std::size_t N>
    class array{

    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = lghazarosyan::reverse_iterator<iterator>;
        using const_reverse_iterator = lghazarosyan::reverse_iterator<const_iterator>;

    public:
        constexpr array() = default;
        constexpr array(const array&);
        constexpr array(array&&);

        constexpr array(const std::initializer_list<T>& lst );
        constexpr array(std::initializer_list<T>&& lst );

        constexpr array& operator = (const array&);
        constexpr array& operator = (array &&);
        ~array() = default;

    public:
        constexpr const_reference operator [] (difference_type)const noexcept;
        constexpr reference operator [] (difference_type) noexcept;

        constexpr reference at(difference_type);
        constexpr const_reference at(difference_type)const ;

        constexpr pointer data() noexcept;
        constexpr const_pointer data()const noexcept;

        constexpr void fill(const value_type &);

        constexpr reference back()noexcept;
        constexpr const_reference back()const noexcept;

        constexpr reference  front() noexcept;
        constexpr const_reference front()const noexcept;

        [[nodiscard]] constexpr bool empty()const noexcept;
        constexpr size_type size()const noexcept;
        constexpr size_type max_size()const noexcept;


    public:
        iterator begin() noexcept;
        const_iterator begin()const noexcept;
        iterator end() noexcept;
        const_iterator end()const noexcept;
        const_iterator cbegin()const noexcept ;
        const_iterator cend()const noexcept;
        reverse_iterator rbegin()noexcept;
        const_reverse_iterator rbegin()const noexcept;
        reverse_iterator rend()noexcept;
        const_reverse_iterator rend()const noexcept;
        const_reverse_iterator crbegin()const noexcept;
        const_reverse_iterator crend()const noexcept;


    private:
        T _arr[N];
    };

    template<typename T, std::size_t N>
    constexpr  typename array<T,N>::const_reference array<T, N>::operator[](typename array::difference_type index) const noexcept {
        return _arr[index];
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::reference array<T, N>::operator[](typename array::difference_type index) noexcept {
        return _arr[index];
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::reference array<T, N>::at(array::difference_type index) {
        if(index>=N){
            throw std::out_of_range("Index of array's element must be less then it's size");
        }
        return _arr[index];
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::const_reference array<T, N>::at(array::difference_type index)const {
        if(index>=N){
            throw std::out_of_range("Index of array's element must be less then it's size");
        }
        return _arr[index];
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::pointer array<T, N>::data() noexcept {
        return _arr;
    }
    template<typename T, std::size_t N>
    constexpr typename array<T,N>::const_pointer array<T, N>::data()const noexcept {
        return _arr;
    }

    template<typename T, std::size_t N>
    constexpr void array<T, N>::fill(const value_type & value) {
        for (size_type i=0;i<N;++i){
            _arr[i] = value;
        }
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::reference array<T, N>::back()noexcept {
        return _arr[N-1];
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::const_reference array<T, N>::back() const noexcept{
        return _arr[N-1];
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::reference array<T, N>::front() noexcept{
        return _arr[0];
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::const_reference array<T, N>::front() const noexcept{
        return _arr[0];
    }

    template<typename T, std::size_t N>
    constexpr bool array<T, N>::empty() const noexcept {
        return N == 0;
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::size_type array<T, N>::size() const noexcept{
        return N;
    }

    template<typename T, std::size_t N>
    constexpr typename array<T,N>::size_type array<T, N>::max_size() const noexcept{
        return N;
    }

    template<typename T, std::size_t N>
    typename array<T,N>::iterator array<T, N>::begin() noexcept{
        return array::iterator(_arr);
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_iterator array<T, N>::begin()const noexcept{
        return cbegin();
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_iterator array<T, N>::cbegin()const noexcept{
        return array::const_iterator(_arr);
    }
    template<typename T, std::size_t N>
    typename array<T,N>::iterator array<T, N>::end() noexcept{
        return array::iterator(_arr+N);
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_iterator array<T, N>::end()const noexcept {
        return cend();
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_iterator array<T, N>::cend()const noexcept{
        return array::const_iterator(_arr);//as I know , I will never attempt to change it's value , if it is really const
    }

    template<typename T, std::size_t N>
    typename array<T,N>::reverse_iterator array<T, N>::rbegin() noexcept{
        return reverse_iterator(end());
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_reverse_iterator array<T, N>::rbegin()const noexcept{
        return crbegin();
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_reverse_iterator array<T, N>::crbegin()const noexcept{
        return const_reverse_iterator(cend());
    }

    template<typename T, std::size_t N>
    typename array<T,N>::reverse_iterator array<T, N>::rend() noexcept{
        return reverse_iterator(begin());
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_reverse_iterator array<T, N>::rend()const noexcept{
        return crend();
    }

    template<typename T, std::size_t N>
    typename array<T,N>::const_reverse_iterator array<T, N>::crend()const noexcept{
        return const_reverse_iterator(cbegin());
    }

    template<typename T, std::size_t N>
    constexpr array<T, N>::array(const array &other) {
        for(size_type i = 0; i < N; ++i){
            _arr[i] = other[i];
        }
    }

    template<typename T, std::size_t N>
    constexpr array<T, N>::array(array &&other) {
        for(size_type i = 0; i < N; ++i){
            _arr[i] = std::move(other[i]);
        }
    }

    template<typename T, std::size_t N>
    constexpr array<T,N>& array<T, N>::operator = (const array & other) {
        if(this != &other) {
            for (size_type i = 0; i < N; ++i) {
                _arr[i] = other[i];
            }
        }
        return *this;
    }

    template<typename T, std::size_t N>
    constexpr array<T,N>& array<T, N>::operator = (array && other) {
        if(this != &other) {
            for (size_type i = 0; i < N; ++i) {
                _arr[i] = std::move(other[i]);
            }
        }
        return *this;
    }

    template<typename T, std::size_t N>
    constexpr array<T, N>::array(const std::initializer_list<T> &lst) {
        if(lst.size() < N){
            throw std::domain_error("the size of list can't be smaller than that of array's");
        }
        size_type index = 0;
       for (const auto& i:lst){
           if(index < N){
               _arr[index++] = i;
           }
       }
    }

    template<typename T, std::size_t N>
    constexpr array<T, N>::array(std::initializer_list<T> &&lst) {
        if(lst.size() < N){
            throw std::domain_error("the size of list can't be smaller than that of array's");
        }

        size_type index = 0;
        for (auto& i:lst){
            if(index < N){
                _arr[index++] = std::move(i);
            }
        }
    }
};



#endif //LGHAZAROSYAN_ARRAY_HPP
