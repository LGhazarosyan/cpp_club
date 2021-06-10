//
// Created by Lusine Ghazarosyan on 22.04.21.
//

#ifndef LGHAZAROSYAN_REVERSE_ITERATOR_HPP
#define LGHAZAROSYAN_REVERSE_ITERATOR_HPP
#include <iostream>
#include <iterator>
#include "type_traits.hpp"
#include "value_traits.hpp"

namespace lghazarosyan{
        template<class Iter, class unused = lghazarosyan::enable_if_t<lghazarosyan::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>>>
        class reverse_iterator {
        public:
            using iterator_type = Iter;

            using reference = typename std::iterator_traits<Iter>::reference;

            using pointer = typename std::iterator_traits<Iter>::pointer;

            using iterator_category = typename std::iterator_traits<Iter>::iterator_category;

            using difference_type = typename std::iterator_traits<Iter>::difference_type;

        public:
            reverse_iterator() = delete;

            reverse_iterator(const reverse_iterator &) = default;

            reverse_iterator(reverse_iterator &&) = default;

            reverse_iterator &operator=(const reverse_iterator &) = default;

            reverse_iterator &operator=(reverse_iterator &&) = default;

            ~reverse_iterator() = default;

            reverse_iterator(const Iter &);

            reverse_iterator(Iter &&);

            template<class OtherIter, class = decltype(Iter(std::declval<const OtherIter &>()))>
            reverse_iterator(const reverse_iterator<OtherIter> &);

            template<class OtherIter, class = decltype(std::declval<iterator_type>() = std::declval<const OtherIter &>())>
            reverse_iterator<Iter> operator=(const reverse_iterator<OtherIter> &);

            bool operator==(const reverse_iterator &other);

            bool operator!=(const reverse_iterator &other);

            reference operator*() const;

            pointer operator->() const;

            reverse_iterator<Iter, unused> &operator++();

            reverse_iterator<Iter, unused> operator++(int);

            reverse_iterator<Iter, unused> &operator--();

            reverse_iterator<Iter, unused> operator--(int);
            
            iterator_type base() const;

            reverse_iterator<Iter, unused> operator[](difference_type index);

            reverse_iterator<Iter, unused> &operator+=(difference_type index);

            reverse_iterator<Iter, unused> &operator-=(difference_type index);

            reverse_iterator<Iter, unused> operator+(difference_type index) const;

            reverse_iterator<Iter, unused> operator-(difference_type index) const;

        protected:
            iterator_type _iter;

            template<class OtherIt, class>
            friend
            class reverse_iterator;

        };


        template<class Iter, class unused>
        reverse_iterator<Iter, unused>::reverse_iterator(const Iter &iter):_iter(iter) {
            --_iter;
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused>::reverse_iterator(Iter &&iter): _iter(
                std::move(iter)) {
            --_iter;
        }


        template<class Iter, class unused>
        template<class OtherIter, class>
        reverse_iterator<Iter, unused>::reverse_iterator(
                const reverse_iterator<OtherIter> &other) {
            _iter = other._iter;
        }

        template<class Iter, class unused>
        template<class OtherIter, class>
        reverse_iterator<Iter> reverse_iterator<Iter, unused>::operator=(
                const reverse_iterator<OtherIter> &other) {
            _iter = other._iter;
        }


        template<class Iter, class unused>
        typename reverse_iterator<Iter, unused>::reference
        reverse_iterator<Iter, unused>::operator*() const {
            return *_iter;
        }

        template<class Iter, class unused>
        typename reverse_iterator<Iter, unused>::pointer
        reverse_iterator<Iter, unused>::operator->() const {
            return std::addressof(operator*());
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused> &reverse_iterator<Iter, unused>::operator++() {
            --_iter;
            return *this;
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused> reverse_iterator<Iter, unused>::operator++(int) {
            reverse_iterator copy = *this;
            ++(*this);
            return copy;
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused> &reverse_iterator<Iter, unused>::operator--() {
            ++_iter;
            return *this;
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused> reverse_iterator<Iter, unused>::operator--(int) {
            reverse_iterator copy = *this;
            --(*this);
            return copy;
        }

        template<class Iter, class unused>
        typename reverse_iterator<Iter, unused>::iterator_type
        reverse_iterator<Iter, unused>::base() const {
            iterator_type base = _iter;
            ++base;
            return base;
        }

        template<class Iter, class unused>
        bool reverse_iterator<Iter, unused>::operator==(const reverse_iterator &other) {
            return (_iter == other._iter);
        }

        template<class Iter, class unused>
        bool reverse_iterator<Iter, unused>::operator!=(const reverse_iterator &other) {
            return !(*this == other);
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused>
        reverse_iterator<Iter, unused>::operator[](difference_type index) {
            if constexpr (lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>){
                return *this + index;
            }
            else{
                static_assert(lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>,"Iterator must be random_access for operator []");
            }
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused> &
        reverse_iterator<Iter, unused>::operator-=(difference_type index) {
            if constexpr (lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>){
                reverse_iterator<Iter>::_iter += index;
                return *this;
            }
            else{
                static_assert(lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>,"Iterator must be random_access for operator -=");
            }
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused> &
        reverse_iterator<Iter, unused>::operator+=(difference_type index) {
            if constexpr (lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>){
                reverse_iterator<Iter>::_iter -= index;
                return *this;
            }
            else{
                static_assert(lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>,"Iterator must be random_access for operator +=");
            }
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused>
        reverse_iterator<Iter, unused>::operator-(difference_type index) const {
            if constexpr (lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>){
                reverse_iterator copy = *this;
                return copy -= index;
            }
            else{
                static_assert(lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>,"Iterator must be random_access for operator -");
            }
        }

        template<class Iter, class unused>
        reverse_iterator<Iter, unused>
        reverse_iterator<Iter, unused>::operator+(difference_type index) const {
            if constexpr (lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>){
                reverse_iterator copy = *this;
                return copy += index;
            }
            else{
                static_assert(lghazarosyan::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>,"Iterator must be random_access for operator +");
            }
        }

};
#endif //LGHAZAROSYAN_REVERSE_ITERATOR_HPP