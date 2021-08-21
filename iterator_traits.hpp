namespace lghazarosyan{
    template <class T>
    struct iterator_traits{
        using iterator_category = typename T::iterator_category;
        using difference_type = typename T::difference_type;
        using pointer = typename T::pointer;
        using reference = typename T::refernce;
        using value_type = typename T::value_type;
    };
    template<typename T>
    struct iterator_traits<T *>{
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;
        using value_type = T;
    };
}
