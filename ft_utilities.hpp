#ifndef FT_UTILITIES_HPP
#define FT_UTILITIES_HPP

namespace ft {
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator value_type() { return v; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename> struct is_integral_base: ft::false_type {};
	template<> struct is_integral_base<bool>: ft::true_type {};
	template<> struct is_integral_base<char>: ft::true_type {};
	template<> struct is_integral_base<char16_t>: ft::true_type {};
	template<> struct is_integral_base<char32_t>: ft::true_type {};
	template<> struct is_integral_base<wchar_t>: ft::true_type {};
	template<> struct is_integral_base<signed char>: ft::true_type {};
	template<> struct is_integral_base<short int>: ft::true_type {};
	template<> struct is_integral_base<int>: ft::true_type {};
	template<> struct is_integral_base<long int>: ft::true_type {};
	template<> struct is_integral_base<long long int>: ft::true_type {};
	template<> struct is_integral_base<unsigned char>: ft::true_type {};
	template<> struct is_integral_base<unsigned short int>: ft::true_type {};
	template<> struct is_integral_base<unsigned int>: ft::true_type {};
	template<> struct is_integral_base<unsigned long int>: ft::true_type {};
	template<> struct is_integral_base<unsigned long long int>: ft::true_type {};

	template <class T>
	struct is_integral : is_integral_base<T> {};

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <class Iterator>
	struct iterator_traits {
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef	typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef	typename Iterator::reference reference;
		typedef	typename Iterator::iterator_category iterator_category;
	};
	template <class T>
	class iterator_traits<T*> {
	public:
		typedef ptrdiff_t difference_type;
		typedef	T value_type;
		typedef T* pointer;
		typedef	T& reference;
		typedef	std::random_access_iterator_tag iterator_category;
	};
	template <class T>
	class iterator_traits<const T*> {
	public:
		typedef ptrdiff_t difference_type;
		typedef	T value_type;
		typedef const T* pointer;
		typedef	const T& reference;
		typedef	std::random_access_iterator_tag iterator_category;
	};

	template<class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) return false;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!pred(*first1, *first2)) return false;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (first2 == last2 or *first2 < *first1) return false;
			else if (*first1 < *first2) return true;
		}
		return first2 != last2;
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		for (; first1 != last1; ++first1, ++first2) {
			if (first2 == last2 or comp(*first2, *first1)) return false;
			else if (comp(*first1, *first2)) return true;
		}
		return first2 != last2;
	}
}

#endif
