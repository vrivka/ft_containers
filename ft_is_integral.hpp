#ifndef FT_IS_INTEGRAL_HPP
#define FT_IS_INTEGRAL_HPP

namespace ft {
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename> struct is_integral_base: ft::false_type {};
	template<> struct is_integral_base<bool>: ft::true_type {};
	template<> struct is_integral_base<char>: ft::true_type {};
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
}

#endif
