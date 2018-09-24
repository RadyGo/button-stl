#pragma once

#include <new>            // placement new
#include <type_traits>
#include <iterator>

template <typename Iterator>
inline typename std::iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
	return static_cast<typename std::iterator_traits<Iterator>::value_type*>(0);
}

template<typename T1, typename T2>
inline void construct(T1* p, const T2& value) {
	new (p) T1(value);
}

template<typename T>
inline void destroy(T* pointer) {
	pointer->~T();
}

template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, std::false_type) {
	for (; first < last; ++first)
		destroy(&*first);
}

template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, std::true_type) {}

template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
	typedef typename std::is_trivially_destructible<T>::type trivial_destructor;
	__destroy_aux(first, last, trivial_destructor());
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
	__destroy(first, last, value_type(first));
}

inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}
