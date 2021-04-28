
#ifndef LGHAZAROSYAN_MAKE_ITERATOR_FROM_POINTER_HPP
#define LGHAZAROSYAN_MAKE_ITERATOR_FROM_POINTER_HPP
#include <iostream>
namespace lghazarosyan {
    //wrapping mechanism is used only for T*,(T is not const)
    template<class T>
    class wrap_pointer_to_const_iterator<const T*>;

    template<class T>
    class wrap_pointer_to_const_iterator<T*> {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::contiguous_iterator_tag;
        using pointer = const T*;
        using reference = const T&;
        using iterator_concept = std::contiguous_iterator_tag;

    public:
        wrap_pointer_to_const_iterator() = default;
        wrap_pointer_to_const_iterator(const wrap_pointer_to_const_iterator &) = default;

        wrap_pointer_to_const_iterator(wrap_pointer_to_const_iterator &&) = default;

        wrap_pointer_to_const_iterator &operator=(const wrap_pointer_to_const_iterator &) = default;

        wrap_pointer_to_const_iterator &operator=(wrap_pointer_to_const_iterator &&) = default;

        ~wrap_pointer_to_const_iterator() = default;
        reference operator*() const;

        pointer operator->() const;

        wrap_pointer_to_const_iterator &operator++();

        wrap_pointer_to_const_iterator operator++(int);

        wrap_pointer_to_const_iterator &operator--();

        wrap_pointer_to_const_iterator operator--(int);

        wrap_pointer_to_const_iterator &operator+=(difference_type);

        wrap_pointer_to_const_iterator operator+(difference_type) const;

        wrap_pointer_to_const_iterator &operator-=(difference_type);

        wrap_pointer_to_const_iterator operator-(difference_type) const;

        wrap_pointer_to_const_iterator operator[](difference_type) const;

        bool operator==(const wrap_pointer_to_const_iterator &) const;

    protected:
        pointer _ptr = nullptr;

        explicit wrap_pointer_to_const_iterator(pointer);

        template<typename t,std::size_t N>
        friend class ::lghazarosyan::array;

    };

    template<class T>
    class wrap_pointer_to_iterator;

    template<class T>
    class wrap_pointer_to_iterator<const T*>;

    template<class T>
    class wrap_pointer_to_iterator<T*> : public wrap_pointer_to_const_iterator<T*> {

    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::contiguous_iterator_tag;
        using pointer = T*;
        using reference = T&;
        using iterator_concept = std::contiguous_iterator_tag;
    public:
        reference operator*() const;

        pointer operator->() const;

        wrap_pointer_to_iterator &operator++();

        wrap_pointer_to_iterator operator++(int);

        wrap_pointer_to_iterator &operator--();

        wrap_pointer_to_iterator operator--(int);

        wrap_pointer_to_iterator operator[](difference_type) const;

        wrap_pointer_to_iterator &operator+=(difference_type);

        wrap_pointer_to_iterator operator+(difference_type) const;

        wrap_pointer_to_iterator &operator-=(difference_type);

        wrap_pointer_to_iterator operator-(difference_type) const;

    private:
        wrap_pointer_to_iterator(const wrap_pointer_to_const_iterator<T*> &);

        explicit wrap_pointer_to_iterator(pointer);

        template<typename t,std::size_t N>
        friend class ::lghazarosyan::array;
    };


    template<typename T>
    typename wrap_pointer_to_iterator<T*>::reference wrap_pointer_to_iterator<T*>::operator*() const {
        return const_cast<reference>(*wrap_pointer_to_const_iterator<T*>::_ptr);
    }

    template<typename T>
    typename wrap_pointer_to_iterator<T*>::pointer wrap_pointer_to_iterator<T*>::operator->() const {
        return const_cast<pointer>(std::addressof(operator*()));
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> &wrap_pointer_to_iterator<T*>::operator++() {
        return (*this) = wrap_pointer_to_const_iterator<T*>::operator++();
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> wrap_pointer_to_iterator<T*>::operator++(int) {
        return wrap_pointer_to_const_iterator<T*>::operator++(0);
    }

    template<typename T>
        wrap_pointer_to_iterator<T*> &wrap_pointer_to_iterator<T*>::operator--() {
        return (*this) = wrap_pointer_to_const_iterator<T*>::operator--();
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> wrap_pointer_to_iterator<T*>::operator--(int) {
        return wrap_pointer_to_const_iterator<T*>::operator--(0);
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> wrap_pointer_to_iterator<T*>::operator[](difference_type index) const {
        return wrap_pointer_to_const_iterator<T*>::operator[](index);
    }

    template<typename T>
    wrap_pointer_to_iterator<T*>::wrap_pointer_to_iterator(const wrap_pointer_to_const_iterator<T*> &cit):wrap_pointer_to_const_iterator<T*>(cit) {
    }

    template<typename T>
    wrap_pointer_to_iterator<T*>::wrap_pointer_to_iterator(pointer ptr):wrap_pointer_to_const_iterator<T*>(ptr) {
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> &wrap_pointer_to_iterator<T*>::operator+=(difference_type index) {
        return *this = wrap_pointer_to_const_iterator<T*>::operator+=(index);
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> wrap_pointer_to_iterator<T*>::operator+(difference_type index) const {
        return wrap_pointer_to_const_iterator<T*>::operator+(index);
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> &wrap_pointer_to_iterator<T*>::operator-=(difference_type index) {
        return *this = wrap_pointer_to_const_iterator<T*>::operator-=(index);
    }

    template<typename T>
    wrap_pointer_to_iterator<T*> wrap_pointer_to_iterator<T*>::operator-(difference_type index) const {
        return wrap_pointer_to_const_iterator<T*>::operator-(0);
    }


    template<typename T>
    typename wrap_pointer_to_const_iterator<T*>::reference wrap_pointer_to_const_iterator<T*>::operator*() const {
        return *_ptr;
    }

    template<typename T>
    typename wrap_pointer_to_const_iterator<T*>::pointer wrap_pointer_to_const_iterator<T*>::operator->() const {
        return addressof(operator*());
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> &wrap_pointer_to_const_iterator<T*>::operator++() {
        ++_ptr;
        return *this;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> wrap_pointer_to_const_iterator<T*>::operator++(int) {
        wrap_pointer_to_const_iterator<T*> copy = *this;
        ++(*this);
        return copy;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> &wrap_pointer_to_const_iterator<T*>::operator--() {
        --_ptr;
        return *this;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> wrap_pointer_to_const_iterator<T*>::operator--(int) {
        wrap_pointer_to_const_iterator<T*> copy = *this;
        --(*this);
        return copy;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> &wrap_pointer_to_const_iterator<T*>::operator+=(difference_type index) {
        _ptr += index;
        return *this;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> &wrap_pointer_to_const_iterator<T*>::operator-=(difference_type index) {
        _ptr -= index;
        return *this;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> wrap_pointer_to_const_iterator<T*>::operator+(difference_type index) const {
        wrap_pointer_to_const_iterator copy = *this;
        ++(*this);
        return copy;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> wrap_pointer_to_const_iterator<T*>::operator-(difference_type index) const {
        wrap_pointer_to_const_iterator copy = *this;
        --(*this);
        return copy;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*> wrap_pointer_to_const_iterator<T*>::operator[](difference_type index) const {
        return *this + index;
    }

    template<typename T>
    wrap_pointer_to_const_iterator<T*>::wrap_pointer_to_const_iterator(pointer ptr) {
        _ptr = ptr;
    }

    template<typename T>
    bool wrap_pointer_to_const_iterator<T*>::operator==(const wrap_pointer_to_const_iterator &other) const {
        return _ptr == other._ptr;
    }
}

#endif //LGHAZAROSYAN_MAKE_ITERATOR_FROM_POINTER_HPP
