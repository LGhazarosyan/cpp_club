#ifndef LGHAZAROSYAN_UNIQUE_PTR
#define LGHAZAROSYAN_UNIQUE_PTR

#include <utility>
#include "type_traits.hpp"

namespace lghazarosyan {

template <class T>
struct default_deleter {
	void operator()(const T* ptr)const {
		delete ptr;
	}
};

template <class T, class Deleter = default_deleter<T>>
class unique_ptr {
public:
	explicit unique_ptr(T* ptr = nullptr, Deleter deleter=Deleter());

	template <class U, class E>
	unique_ptr(const unique_ptr<U, E>& other) = delete;

	template <class U, class E>
	unique_ptr(unique_ptr<U, E>&& other);

	template <class U, class E>
	unique_ptr& operator=(const unique_ptr<U,E>& other) = delete;

	template <class U, class E>
	unique_ptr& operator=(unique_ptr<U, E>&& other);

	~unique_ptr();

	void reset();
	T* release();
	void swap(unique_ptr&);
	
	T * get();
	const T * get() const;

	Deleter& get_deleter();
	const Deleter& get_deleter() const;

	operator bool() const;

	T& operator *();
	const T& operator *()const;

	T* operator ->();
	const T* operator ->()const;



	template <class Type, class ...Ts>
	friend unique_ptr make_unique(Ts&&... args);

private:
	T* _ptr = nullptr;
	Deleter _deleter;

};

template <class T, class Deleter>
unique_ptr<T, Deleter>:: unique_ptr(T * ptr, Deleter deleter): _ptr(ptr)
														  ,_deleter(deleter){}
template <class T, class Deleter>
template <class U, class E>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr<U, E>&& other): _ptr(other.release())
							    ,_deleter(std::move(other._deleter)) {
	static_assert(is_convertible_v<T*, U*> && is_constructible_v<Deleter, E>, "Cannot construct unique ptr object");

}

template <class T, class Deleter>
template <class U, class E>
unique_ptr<T, Deleter>&  unique_ptr<T, Deleter>::operator=(unique_ptr<U, E>&& other) {
	static_assert(is_convertible_v<T*, U*> && is_constructible_v<Deleter, E>, "Cannot assign to unique ptr object");
	reset();
	_ptr=other.release();
	_deleter=std::move(other._deleter);
	return *this;
}

template <class T, class Deleter>
T* unique_ptr<T, Deleter>::release() {
	T* ptr = _ptr;
	_ptr = nullptr;
	return ptr;
}

template <class T, class Deleter>
void unique_ptr<T, Deleter>::reset() {
	_deleter(_ptr);
	_ptr = nullptr;
}

template <class T, class Deleter>
void unique_ptr<T, Deleter>::swap(unique_ptr& other) {
	using namespace std;
	swap(other._ptr, _ptr);
	swap(other._deleter, _deleter);
}

template <class T, class Deleter>
unique_ptr<T, Deleter>::~unique_ptr() {
	_deleter(_ptr);
}

template <class T, class Deleter>
T* unique_ptr<T, Deleter>::get() {
	return _ptr;
}

template <class T, class Deleter>
const T* unique_ptr<T, Deleter>::get() const {
	return _ptr;
}

template <class T, class Deleter>
Deleter& unique_ptr<T, Deleter>::get_deleter() {
	return _deleter;
}

template<class T, class Deleter>
const Deleter& unique_ptr<T, Deleter>::get_deleter() const {
	return _deleter;
}

template<class T, class Deleter>
unique_ptr<T, Deleter>::operator bool() const {
	return _ptr != nullptr;
}

template<class T, class Deleter>
T& unique_ptr<T, Deleter>::operator *() {
	return *_ptr;
}

template<class T, class Deleter>
const T& unique_ptr<T, Deleter>::operator *() const {
	return *_ptr;
}

template<class T, class Deleter>
T*  unique_ptr<T, Deleter>::operator ->() {
	return _ptr;
}

template<class T, class Deleter>
const T*  unique_ptr<T, Deleter>::operator ->() const {
	return _ptr;
}

template <class Type, class ...Ts>
unique_ptr<Type, default_deleter<Type>> make_unique(Ts&&... args) {
	static_assert(lghazarosyan::is_constructible_v<Type, Ts...>, "Cannot construct unique pointer");
	Type* ptr = new Type(std::forward<Ts>(args)...);
	return unique_ptr<Type, default_deleter<Type>>(ptr);
}

} // namespace lghazarosyan

#endif // LGHAZAROSYAN_UNIQUE_PTRhttps://www.youtube.com/E
