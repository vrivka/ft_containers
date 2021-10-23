#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>

namespace ft{
	template <class Iterator>
	class iterator_traits {
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef	typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef	typename Iterator::reference reference;
		typedef	typename Iterator::iterator_category iterator_category;
		iterator_traits() {};
		iterator_traits(const iterator_traits<Iterator> &) {};
		~iterator_traits() {};
		iterator_traits<Iterator> &operator=(const iterator_traits<Iterator> &) { return *this; };
	};
	template <class T>
	class iterator_traits<T*> {
	public:
		typedef ptrdiff_t difference_type;
		typedef	T value_type;
		typedef T* pointer;
		typedef	T& reference;
		typedef	std::random_access_iterator_tag iterator_category;
		iterator_traits() {};
		iterator_traits(const iterator_traits<T*> &) {};
		~iterator_traits() {};
		iterator_traits<T*> &operator=(const iterator_traits<T*> &) { return *this; };
	};
	template <class T>
	class iterator_traits<const T*> {
	public:
		typedef ptrdiff_t difference_type;
		typedef	T value_type;
		typedef const T* pointer;
		typedef	const T& reference;
		typedef	std::random_access_iterator_tag iterator_category;
		iterator_traits() {};
		iterator_traits(const iterator_traits<const T*> &) {};
		~iterator_traits() {};
		iterator_traits<const T*> &operator=(const iterator_traits<const T*> &) { return *this; };
	};
}


#endif
