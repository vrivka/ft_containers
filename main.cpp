#include <iostream>
#include "ft_vector.hpp"
#include "ft_stack.hpp"
#include "ft_map.hpp"
#include "ft_set.hpp"
#include <iomanip>
#include <vector>
#include <stack>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

#ifndef _NMSPC
#define _NMSPC ft
#endif

template<class T>
void printInfo(const _NMSPC::vector<T> &vec) {
	std::cout << "=======Vector<T>======\n";
	std::cout << "| Is empty?: " << std::boolalpha << vec.empty() << '\n';
	std::cout << "| Size: " << vec.size() << '\n';
	std::cout << "| Capacity: " << vec.capacity() << '\n';
	std::cout << "| Contain:\n";
	typename _NMSPC::vector<T>::const_iterator it = vec.begin();
	typename _NMSPC::vector<T>::const_iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << "| " << *it << '\n';
	std::cout << "======================\n";
}

template<class T1, class T2>
void printInfo(const _NMSPC::vector<_NMSPC::pair<T1, T2> > &vec) {
	std::cout << "=======Vector<pair<T1,T2>>======\n";
	std::cout << "| Is empty?: " << std::boolalpha << vec.empty() << '\n';
	std::cout << "| Size: " << vec.size() << '\n';
	std::cout << "| Capacity: " << vec.capacity() << '\n';
	std::cout << "| Contain:\n";
	typename _NMSPC::vector<_NMSPC::pair<T1, T2> >::const_iterator it = vec.begin();
	typename _NMSPC::vector<_NMSPC::pair<T1, T2> >::const_iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << "| first: " << it->first << " second: " << it->second << '\n';
	std::cout << "=============================\n";
}

template<class T>
void printInfo(const _NMSPC::map<int,int,T> &mp) {
	std::cout << "=======map======\n";
	std::cout << "| Is empty?: " << std::boolalpha << mp.empty() << '\n';
	std::cout << "| Size: " << mp.size() << '\n';
	std::cout << "| Contain:\n";
	typename _NMSPC::map<int,int>::const_iterator it = mp.begin();
	typename _NMSPC::map<int,int>::const_iterator ite = mp.end();
	for (; it != ite; ++it)
		std::cout << "| first: " << it->first << " second: " << it->second << '\n';
	std::cout << "================\n";
}

template<class T>
void vec_coprassion(const _NMSPC::vector<T> &v1, const _NMSPC::vector<T> &v2) {
	std::cout << std::boolalpha << (v1 == v2) << '\t';
	std::cout << std::boolalpha << (v1 != v2) << '\t';
	std::cout << std::boolalpha << (v1 < v2) << '\t';
	std::cout << std::boolalpha << (v1 <= v2) << '\t';
	std::cout << std::boolalpha << (v1 > v2) << '\t';
	std::cout << std::boolalpha << (v1 >= v2) << "\n";
}

void vector_test() {
	int a[6] = {4, 8, 15, 16, 23, 42};
	int b[6] = {42, 23, 16, 15, 8, 4};

	std::cout << "Vector constructors tests\n";
	{
		_NMSPC::vector<int> v1;
		_NMSPC::vector<int> v2(6);
		_NMSPC::vector<int> v3(6, 100);
		_NMSPC::vector<int> v4(a + 0, a + 6);
		_NMSPC::vector<int> v5(v4.begin(), v4.end());
		_NMSPC::map<int, int> m;
		for (int i = 0; i < 6; ++i)
			m.insert(_NMSPC::make_pair(a[i], b[i]));
		_NMSPC::vector<_NMSPC::pair<int, int> > v6(m.begin(), m.end());
		const _NMSPC::vector<int> &v7(v5);
		const _NMSPC::vector<_NMSPC::pair<int, int> > &v8(v6);
		std::cout << "v1\n";
		printInfo(v1);
		std::cout << "v2\n";
		printInfo(v2);
		std::cout << "v3\n";
		printInfo(v3);
		std::cout << "v4\n";
		printInfo(v4);
		std::cout << "v5\n";
		printInfo(v5);
		std::cout << "v6\n";
		printInfo(v6);
		std::cout << "v7\n";
		printInfo(v7);
		std::cout << "v8\n";
		printInfo(v8);
	}
	std::cout << "\nAssign operator tests\n";
	{
		_NMSPC::vector<int> v1(10, 100);
		_NMSPC::vector<int> v2(5, 50);

		std::cout << "v1\n";
		printInfo(v1);

		std::cout << "Before\n";
		std::cout << "v2\n";
		printInfo(v2);
		v2 = v1;
		std::cout << "After\n";
		std::cout << "v2\n";
		printInfo(v2);

		_NMSPC::vector<int> v3(15, 150);
		std::cout << "Before\n";
		std::cout << "v3\n";
		printInfo(v3);
		v3 = v1;
		std::cout << "After\n";
		std::cout << "v3\n";
		printInfo(v3);
	}
	std::cout << "\nIterators tests\n";
	{
		_NMSPC::vector<int> v(a + 0, a + 6);

		_NMSPC::vector<int>::iterator it = v.begin();
		_NMSPC::vector<int>::iterator ite = v.end();
		_NMSPC::vector<int>::const_iterator cit = it;
		_NMSPC::vector<int>::const_iterator cite = ite;
		_NMSPC::vector<int>::reverse_iterator rit = v.rbegin();
		_NMSPC::vector<int>::reverse_iterator rite = v.rend();
		_NMSPC::vector<int>::const_reverse_iterator rcit = rit;
		_NMSPC::vector<int>::const_reverse_iterator rcite = rite;

		(void)cit;
		(void)rcit;
		std::cout << "Iterator output\n";
		for (; it != cite; ++it)
			std::cout << *it << std::endl;
		std::cout << "Reverse iterator output\n";
		for (; rit != rcite; ++rit)
			std::cout << *rit << std::endl;
	}
	std::cout << "\nResize tests\n";
	{
		_NMSPC::vector<int> v(a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		std::cout << "resize to 10\n";
		v.resize(10);
		printInfo(v);
		std::cout << "resize to 10 with 21\n";
		v.resize(15, 21);
		printInfo(v);
		std::cout << "resize to 5\n";
		v.resize(5);
		printInfo(v);
	}
	std::cout << "\nReserve tests\n";
	{
		_NMSPC::vector<int> v(a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		std::cout << "reserve to 3\n";
		v.reserve(3);
		printInfo(v);
		std::cout << "reserve to 10 \n";
		v.resize(10);
		printInfo(v);
		std::cout << "reserve to 5\n";
		v.resize(5);
		printInfo(v);
	}
	std::cout << "\nAccess operator tests\n";
	{
		_NMSPC::vector<int> v1(a+0, a+6);
		for (int i = 0; i < 6; ++i)
			std::cout << v1[i] << std::endl;
		std::cout << "const\n";
		_NMSPC::vector<int> const v2(a+0, a+6);
		for (int i = 0; i < 6; ++i)
			std::cout << v2[i] << std::endl;
	}
	std::cout << "\n\"at\" tests\n";
	{
		_NMSPC::vector<int> v1(a+0, a+6);
		try {
			for (int i = 0; i < 10; ++i)
				std::cout << v1.at(i) << std::endl;
		}
		catch (std::out_of_range &oor) {
			std::cout << oor.what() << ": out of range access\n";
		}
		std::cout << "const copy\n";
		_NMSPC::vector<int> const v2(v1);
		try {
			for (int i = 0; i < 10; ++i)
				std::cout << v2.at(i) << std::endl;
		}
		catch (std::out_of_range &oor) {
			std::cout << oor.what() << ": out of range access\n";
		}
	}
	std::cout << "\nFront tests\n";
	{
		_NMSPC::vector<int> v1(5, 10);
		std::cout << "v\n";
		printInfo(v1);
		std::cout << "First element: " << v1.front() << std::endl;
		v1.front() = 20;
		printInfo(v1);
		std::cout << "const copy\n";
		_NMSPC::vector<int> const v2(v1);
		std::cout << "First element: " << v2.front() << std::endl;
	}
	std::cout << "\nBack tests\n";
	{
		_NMSPC::vector<int> v1(5, 10);
		std::cout << "v\n";
		printInfo(v1);
		std::cout << "Last element: " << v1.back() << std::endl;
		v1.back() = 20;
		printInfo(v1);
		std::cout << "const copy v\n";
		_NMSPC::vector<int> const v2(v1);
		std::cout << "Last element: " << v2.back() << std::endl;
	}
	std::cout << "\nData tests\n";
	{
		_NMSPC::vector<int> v1(a+0, a+6);
		std::cout << "v\n";
		printInfo(v1);
		int *arr = v1.data();
		std::cout << "Data print with int*\n";
		for (int i = 0; i < 6; ++i)
			std::cout << arr[i] << std::endl;
		std::cout << "Change 6 element to 21 in int*\n";
		arr[5] = 21;
		std::cout << "v\n";
		printInfo(v1);
		std::cout << "const copy v\n";
		_NMSPC::vector<int> const v2(v1);
		std::cout << "v\n";
		printInfo(v2);
		const int *const_arr = v2.data();
		std::cout << "Data print with int*\n";
		for (int i = 0; i < 6; ++i)
			std::cout << const_arr[i] << std::endl;
	}
	std::cout << "\nAssign tests\n";
	{
		_NMSPC::vector<int> v1(a + 0, a + 6);
		_NMSPC::vector<int> v2(v1);
		std::cout << "v\n";
		printInfo(v1);
		v1.assign(6, 21);
		std::cout << "v\n";
		printInfo(v1);
		v1.assign(v2.begin(), v2.end());
		std::cout << "v\n";
		printInfo(v1);
		v1.assign(2, 42);
		std::cout << "v\n";
		printInfo(v1);
	}
	std::cout << "\nPush back tests\n";
	{
		_NMSPC::vector<int> v;
		std::cout << "v\n";
		printInfo(v);
		v.push_back(4);
		std::cout << "v\n";
		printInfo(v);
		v.push_back(8);
		std::cout << "v\n";
		printInfo(v);
		v.push_back(15);
		std::cout << "v\n";
		printInfo(v);
		v.push_back(16);
		std::cout << "v\n";
		printInfo(v);
		v.push_back(23);
		std::cout << "v\n";
		printInfo(v);
		v.push_back(42);
		std::cout << "v\n";
		printInfo(v);
	}
	std::cout << "\nPop back tests\n";
	{
		_NMSPC::vector<int> v(a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		v.pop_back();
		std::cout << "v\n";
		printInfo(v);
		v.pop_back();
		std::cout << "v\n";
		printInfo(v);
		v.pop_back();
		std::cout << "v\n";
		printInfo(v);
		v.pop_back();
		std::cout << "v\n";
		printInfo(v);
		v.pop_back();
		std::cout << "v\n";
		printInfo(v);
		v.pop_back();
		std::cout << "v\n";
		printInfo(v);
	}
	std::cout << "\nInsert tests\n";
	{
		_NMSPC::vector<int> v;
		std::cout << "v\n";
		printInfo(v);
		v.insert(v.begin(), 4);
		std::cout << "v\n";
		printInfo(v);
		v.insert(v.begin(), 4, 4);
		std::cout << "v\n";
		printInfo(v);
		v.insert(v.begin(), a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		v.insert(v.begin() + 6, 4, 21);
		std::cout << "v\n";
		printInfo(v);
		v.insert(v.begin() + 10, a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		v.insert(v.end(), v.rbegin(), v.rend());
		std::cout << "v\n";
		printInfo(v);
	}
	std::cout << "\nErase tests\n";
	{
		_NMSPC::vector<int> v(a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		v.erase(v.begin());
		std::cout << "v\n";
		printInfo(v);
		v.erase(v.end() - 1);
		std::cout << "v\n";
		printInfo(v);
		v.erase(v.begin() + 1, v.end() - 1);
		std::cout << "v\n";
		printInfo(v);
		v.erase(v.begin(), v.end());
		std::cout << "v\n";
		printInfo(v);
	}
	std::cout << "\nSwap and std::Swap tests\n";
	{
		_NMSPC::vector<int> v1(a+0, a+6);
		_NMSPC::vector<int> v2(b+0, b+6);
		std::cout << "v1\n";
		printInfo(v1);
		std::cout << "v2\n";
		printInfo(v2);
		std::cout << "vector swap\n";
		v1.swap(v2);
		std::cout << "v1\n";
		printInfo(v1);
		std::cout << "v2\n";
		printInfo(v2);
		std::cout << "std swap\n";
		std::swap(v1, v2);
		std::cout << "v1\n";
		printInfo(v1);
		std::cout << "v2\n";
		printInfo(v2);
	}
	std::cout << "\nClear test\n";
	{
		_NMSPC::vector<int> v(a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		v.clear();
		std::cout << "v\n";
		printInfo(v);
	}
	std::cout << "\nGet allocator tests\n";
	{
		_NMSPC::vector<int> v1;

		std::cout << std::boolalpha << (typeid(v1.get_allocator()) == typeid(std::allocator<int>)) << ' ' << typeid(v1.get_allocator()).name() << std::endl;

		_NMSPC::vector<std::string> v2;

		std::cout << std::boolalpha << (typeid(v2.get_allocator()) == typeid(std::allocator<std::string>)) << ' ' << typeid(v2.get_allocator()).name() << std::endl;

	}
	std::cout << "\nCompression tests\n";
	{
		_NMSPC::vector<int> v1(10, 100), v2(10, 200), v3(10, 50), v4(5, 100), v5(5, 200), v6(5, 50);

		std::cout << "==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		vec_coprassion(v1, v1);
		vec_coprassion(v1, v2);
		vec_coprassion(v1, v3);
		vec_coprassion(v1, v4);
		vec_coprassion(v1, v5);
		vec_coprassion(v1, v6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		vec_coprassion(v2, v1);
		vec_coprassion(v2, v2);
		vec_coprassion(v2, v3);
		vec_coprassion(v2, v4);
		vec_coprassion(v2, v5);
		vec_coprassion(v2, v6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		vec_coprassion(v3, v1);
		vec_coprassion(v3, v2);
		vec_coprassion(v3, v3);
		vec_coprassion(v3, v4);
		vec_coprassion(v3, v5);
		vec_coprassion(v3, v6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		vec_coprassion(v4, v1);
		vec_coprassion(v4, v2);
		vec_coprassion(v4, v3);
		vec_coprassion(v4, v4);
		vec_coprassion(v4, v5);
		vec_coprassion(v4, v6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		vec_coprassion(v5, v1);
		vec_coprassion(v5, v2);
		vec_coprassion(v5, v3);
		vec_coprassion(v5, v4);
		vec_coprassion(v5, v5);
		vec_coprassion(v5, v6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		vec_coprassion(v6, v1);
		vec_coprassion(v6, v2);
		vec_coprassion(v6, v3);
		vec_coprassion(v6, v4);
		vec_coprassion(v6, v5);
		vec_coprassion(v6, v6);
	}
}

template<class T, class C>
void stack_coprassion(const _NMSPC::stack<T, C> &st1, const _NMSPC::stack<T, C> &st2) {
	std::cout << std::boolalpha << (st1 == st2) << '\t';
	std::cout << std::boolalpha << (st1 != st2) << '\t';
	std::cout << std::boolalpha << (st1 < st2) << '\t';
	std::cout << std::boolalpha << (st1 <= st2) << '\t';
	std::cout << std::boolalpha << (st1 > st2) << '\t';
	std::cout << std::boolalpha << (st1 >= st2) << "\n";
}

void stack_test() {
	std::cout << "Push/top/pop tests\n";
	{
		_NMSPC::stack<int> st;

		std::cout << "stack is empty?: " << std::boolalpha << st.empty() << std::endl;
		st.push(4);
		st.push(8);
		st.push(15);
		st.push(16);
		st.push(23);
		st.push(42);
		std::cout << st.top() << std::endl;
		st.pop();
		std::cout << st.top() << std::endl;
		st.pop();
		std::cout << st.top() << std::endl;
		st.pop();
		std::cout << "stack is empty?: " << std::boolalpha << st.empty() << std::endl;
		std::cout << st.top() << std::endl;
		st.pop();
		std::cout << st.top() << std::endl;
		st.pop();
		std::cout << st.top() << std::endl;
		st.pop();
		std::cout << "stack is empty?: " << std::boolalpha << st.empty() << std::endl;
	}
	std::cout << "Stack compare tests\n";
	{
		_NMSPC::vector<int> v1(10, 100), v2(10, 200), v3(10, 50), v4(5, 100), v5(5, 200), v6(5, 50);
		_NMSPC::stack<int, _NMSPC::vector<int> > st1(v1), st2(v2), st3, st4(v4), st5(v5), st6(v6);

		std::cout << "==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		stack_coprassion(st1, st1);
		stack_coprassion(st1, st2);
		stack_coprassion(st1, st3);
		stack_coprassion(st1, st4);
		stack_coprassion(st1, st5);
		stack_coprassion(st1, st6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		stack_coprassion(st2, st1);
		stack_coprassion(st2, st2);
		stack_coprassion(st2, st3);
		stack_coprassion(st2, st4);
		stack_coprassion(st2, st5);
		stack_coprassion(st2, st6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		stack_coprassion(st3, st1);
		stack_coprassion(st3, st2);
		stack_coprassion(st3, st3);
		stack_coprassion(st3, st4);
		stack_coprassion(st3, st5);
		stack_coprassion(st3, st6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		stack_coprassion(st4, st1);
		stack_coprassion(st4, st2);
		stack_coprassion(st4, st3);
		stack_coprassion(st4, st4);
		stack_coprassion(st4, st5);
		stack_coprassion(st4, st6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		stack_coprassion(st5, st1);
		stack_coprassion(st5, st2);
		stack_coprassion(st5, st3);
		stack_coprassion(st5, st4);
		stack_coprassion(st5, st5);
		stack_coprassion(st5, st6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		stack_coprassion(st6, st1);
		stack_coprassion(st6, st2);
		stack_coprassion(st6, st3);
		stack_coprassion(st6, st4);
		stack_coprassion(st6, st5);
		stack_coprassion(st6, st6);
	}
}

void map_coprassion(const _NMSPC::map<int,int> &mp1, const _NMSPC::map<int,int> &mp2) {
	std::cout << std::boolalpha << (mp1 == mp2) << '\t';
	std::cout << std::boolalpha << (mp1 != mp2) << '\t';
	std::cout << std::boolalpha << (mp1 < mp2) << '\t';
	std::cout << std::boolalpha << (mp1 <= mp2) << '\t';
	std::cout << std::boolalpha << (mp1 > mp2) << '\t';
	std::cout << std::boolalpha << (mp1 >= mp2) << "\n";
}

void map_test() {
	_NMSPC::pair<int,int> a[6] = {_NMSPC::make_pair(4, -4), _NMSPC::make_pair(8, -8), _NMSPC::make_pair(15, -15), _NMSPC::make_pair(16, -16), _NMSPC::make_pair(23, -23), _NMSPC::make_pair(42, -42)};
	_NMSPC::pair<int,int> b[6] = {_NMSPC::make_pair(5, -4), _NMSPC::make_pair(9, -8), _NMSPC::make_pair(16, -15), _NMSPC::make_pair(17, -16), _NMSPC::make_pair(24, -23), _NMSPC::make_pair(43, -42)};

	std::cout << "Map constructors tests\n";
	{
		_NMSPC::map<int,int> mp1;
		_NMSPC::map<int,int> mp2(a+0, a+6);
		_NMSPC::map<int,int, std::greater<int> > mp3(a+0, a+6);
		_NMSPC::map<int,int, std::less_equal<int> > mp4(a+0, a+6);
		_NMSPC::map<int,int, std::greater_equal<int> > mp5(a+0, a+6);
		_NMSPC::map<int,int> mp6(mp2);

		std::cout << "mp1\n";
		printInfo(mp1);
		std::cout << "mp2\n";
		printInfo(mp2);
		std::cout << "mp3\n";
		printInfo(mp3);
		std::cout << "mp4\n";
		printInfo(mp4);
		std::cout << "mp5\n";
		printInfo(mp5);
		std::cout << "mp6\n";
		printInfo(mp6);

	}
	std::cout << "\nAssign operator tests\n";
	{
		_NMSPC::map<int,int> mp1(a + 0, a + 6);
		_NMSPC::map<int,int> mp2;

		std::cout << "mp1\n";
		printInfo(mp1);

		std::cout << "Before\n";
		std::cout << "mp2\n";
		printInfo(mp2);
		mp2 = mp1;
		std::cout << "After\n";
		std::cout << "mp2\n";
		printInfo(mp2);
	}
	std::cout << "\nIterators tests\n";
	{
		_NMSPC::map<int,int> mp(a + 0, a + 6);

		_NMSPC::map<int,int>::iterator it = mp.begin();
		_NMSPC::map<int,int>::iterator ite = mp.end();
		_NMSPC::map<int,int>::const_iterator cit = it;
		_NMSPC::map<int,int>::const_iterator cite = ite;
		_NMSPC::map<int,int>::reverse_iterator rit = mp.rbegin();
		_NMSPC::map<int,int>::reverse_iterator rite = mp.rend();
		_NMSPC::map<int,int>::const_reverse_iterator rcit = rit;
		_NMSPC::map<int,int>::const_reverse_iterator rcite = rite;

		(void)cit;
		(void)rcit;
		std::cout << "Iterator output\n";
		for (; it != cite; ++it)
			std::cout << it->first << std::endl;
		std::cout << "Reverse iterator output\n";
		for (; rit != rcite; ++rit)
			std::cout << rit->first << std::endl;
	}
	std::cout << "\nAccess operator tests\n";
	{
		_NMSPC::map<int,int> mp(a+0, a+6);
		std::cout << "mp before\n";
		printInfo(mp);
		for (int i = 0; i < 43; ++i)
			mp[i] = mp[i] == 0 ? i : -i;
		std::cout << "mp after\n";
		printInfo(mp);
	}
	std::cout << "\n\"at\" tests\n";
	{
		_NMSPC::map<int,int> mp1(a + 0, a + 6);
		try {
			std::cout << mp1.at(4) << std::endl;
			std::cout << mp1.at(8) << std::endl;
			std::cout << mp1.at(15) << std::endl;
			std::cout << mp1.at(16) << std::endl;
			std::cout << mp1.at(23) << std::endl;
			std::cout << mp1.at(42) << std::endl;
			std::cout << mp1.at(1) << std::endl;
		}
		catch (std::out_of_range &oor) {
			std::cout << oor.what() << ": out of range access\n";
		}
		std::cout << "const copy\n";
		_NMSPC::map<int,int> const mp2(mp1);
		try {
			std::cout << mp1.at(4) << std::endl;
			std::cout << mp1.at(8) << std::endl;
			std::cout << mp1.at(15) << std::endl;
			std::cout << mp1.at(16) << std::endl;
			std::cout << mp1.at(23) << std::endl;
			std::cout << mp1.at(42) << std::endl;
			std::cout << mp1.at(1) << std::endl;
		}
		catch (std::out_of_range &oor) {
			std::cout << oor.what() << ": out of range access\n";
		}
	}
	std::cout << "\nInsert tests\n";
	{
		_NMSPC::map<int,int> mp(a+0, a+6);
		std::cout << "mp in start\n";
		printInfo(mp);
		std::cout << std::boolalpha << mp.insert(_NMSPC::make_pair(4, 32)).second << std::endl;
		std::cout << "mp\n";
		printInfo(mp);
		mp.insert(_NMSPC::make_pair(32, 32));
		std::cout << "mp\n";
		printInfo(mp);
		mp.insert(b+0, b+6);
		std::cout << "mp\n";
		printInfo(mp);
	}
	std::cout << "\nErase tests\n";
	{
		_NMSPC::map<int,int> mp(a+0, a+6);
		std::cout << "mp in start\n";
		printInfo(mp);
		std::cout << "erase key ret: " << mp.erase(15) << std::endl;
		std::cout << "mp\n";
		printInfo(mp);
		mp.erase(mp.begin());
		std::cout << "mp\n";
		printInfo(mp);
		mp.erase(mp.begin(), mp.end());
		std::cout << "mp\n";
		printInfo(mp);
	}
	std::cout << "\nSwap and std::Swap tests\n";
	{
		_NMSPC::map<int,int> mp1(a + 0, a + 6);
		_NMSPC::map<int,int> mp2(b + 0, b + 6);
		std::cout << "mp1\n";
		printInfo(mp1);
		std::cout << "mp2\n";
		printInfo(mp2);
		std::cout << "vector swap\n";
		mp1.swap(mp2);
		std::cout << "mp1\n";
		printInfo(mp1);
		std::cout << "mp2\n";
		printInfo(mp2);
		std::cout << "std swap\n";
		std::swap(mp1, mp2);
		std::cout << "mp1\n";
		printInfo(mp1);
		std::cout << "mp2\n";
		printInfo(mp2);
	}
	std::cout << "\nClear test\n";
	{
		_NMSPC::map<int,int> mp(a+0, a+6);
		std::cout << "mp\n";
		printInfo(mp);
		mp.clear();
		std::cout << "mp\n";
		printInfo(mp);
	}
	std::cout << "\nFind test\n";
	{
		_NMSPC::map<int,int> mp1(a+0, a+6);
		std::cout << "mp1\n";
		printInfo(mp1);
		std::cout << mp1.find(4)->second << std::endl;
		std::cout << mp1.find(8)->second << std::endl;
		std::cout << mp1.find(15)->second << std::endl;
		std::cout << mp1.find(16)->second << std::endl;
		std::cout << mp1.find(23)->second << std::endl;
		std::cout << mp1.find(42)->second << std::endl;
		std::cout << std::boolalpha << (mp1.find(7) == mp1.end()) << std::endl;
		std::cout << "const copy\n";
		_NMSPC::map<int,int> const mp2(mp1);
		std::cout << "mp2\n";
		printInfo(mp2);
		std::cout << mp2.find(4)->second << std::endl;
		std::cout << mp2.find(8)->second << std::endl;
		std::cout << mp2.find(15)->second << std::endl;
		std::cout << mp2.find(16)->second << std::endl;
		std::cout << mp2.find(23)->second << std::endl;
		std::cout << mp2.find(42)->second << std::endl;
		std::cout << std::boolalpha << (mp2.find(7) == mp2.end()) << std::endl;
	}
	std::cout << "\nCount test\n";
	{
		_NMSPC::map<int,int> mp1(a+0, a+6);
		std::cout << "mp1\n";
		printInfo(mp1);
		std::cout << mp1.count(4) << std::endl;
		std::cout << mp1.count(8) << std::endl;
		std::cout << mp1.count(15) << std::endl;
		std::cout << mp1.count(16)<< std::endl;
		std::cout << mp1.count(23) << std::endl;
		std::cout << mp1.count(42) << std::endl;
		std::cout << mp1.count(7) << std::endl;
	}
	std::cout << "\nLower bound test\n";
	{
		_NMSPC::map<int,int> mp1(a+0, a+6);
		std::cout << "mp1\n";
		printInfo(mp1);
		for (int i = 0; i < 43; ++i)
			std::cout << mp1.lower_bound(i)->second << std::endl;
	}
	std::cout << "\nUpper bound test\n";
	{
		_NMSPC::map<int,int> mp1(a+0, a+6);
		std::cout << "mp1\n";
		printInfo(mp1);
		for (int i = 0; i < 42; ++i)
			std::cout << mp1.upper_bound(i)->second << std::endl;
	}
	std::cout << "\nEqual range test\n";
	{
		_NMSPC::pair<_NMSPC::map<int,int>::iterator, _NMSPC::map<int,int>::iterator> erit;
		_NMSPC::map<int,int> mp1(a+0, a+6);
		std::cout << "mp1\n";
		printInfo(mp1);
		for (int i = 0; i < 42; ++i) {
			erit = mp1.equal_range(i);
			std::cout << erit.first->second << ' ';
			std::cout << erit.second->second << std::endl;
		}
	}
	std::cout << "\nCompression test\n";
	{
		_NMSPC::map<int,int> mp1, mp2, mp3, mp4, mp5, mp6;

		for (int i = 0; i < 10; ++i)
			mp1.insert(_NMSPC::make_pair(i, i));
		for (int i = 0; i < 10; ++i)
			mp2.insert(_NMSPC::make_pair(i, i+1));
		for (int i = 0; i < 10; ++i)
			mp3.insert(_NMSPC::make_pair(i+1, i));
		for (int i = 0; i < 10; ++i)
			mp4.insert(_NMSPC::make_pair(i+1, i+1));
		for (int i = 0; i < 20; ++i)
			mp5.insert(_NMSPC::make_pair(i, i));
		for (int i = 0; i < 20; ++i)
			mp6.insert(_NMSPC::make_pair(i, i+1));

		std::cout << "==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		map_coprassion(mp1, mp1);
		map_coprassion(mp1, mp2);
		map_coprassion(mp1, mp3);
		map_coprassion(mp1, mp4);
		map_coprassion(mp1, mp5);
		map_coprassion(mp1, mp6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		map_coprassion(mp2, mp1);
		map_coprassion(mp2, mp2);
		map_coprassion(mp2, mp3);
		map_coprassion(mp2, mp4);
		map_coprassion(mp2, mp5);
		map_coprassion(mp2, mp6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		map_coprassion(mp3, mp1);
		map_coprassion(mp3, mp2);
		map_coprassion(mp3, mp3);
		map_coprassion(mp3, mp4);
		map_coprassion(mp3, mp5);
		map_coprassion(mp3, mp6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		map_coprassion(mp4, mp1);
		map_coprassion(mp4, mp2);
		map_coprassion(mp4, mp3);
		map_coprassion(mp4, mp4);
		map_coprassion(mp4, mp5);
		map_coprassion(mp4, mp6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		map_coprassion(mp5, mp1);
		map_coprassion(mp5, mp2);
		map_coprassion(mp5, mp3);
		map_coprassion(mp5, mp4);
		map_coprassion(mp5, mp5);
		map_coprassion(mp5, mp6);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		map_coprassion(mp6, mp1);
		map_coprassion(mp6, mp2);
		map_coprassion(mp6, mp3);
		map_coprassion(mp6, mp4);
		map_coprassion(mp6, mp5);
		map_coprassion(mp6, mp6);
	}
}

template<class T>
void printInfo(const _NMSPC::set<int,T> &mp) {
	std::cout << "=======set======\n";
	std::cout << "| Is empty?: " << std::boolalpha << mp.empty() << '\n';
	std::cout << "| Size: " << mp.size() << '\n';
	std::cout << "| Contain:\n";
	typename _NMSPC::set<int>::const_iterator it = mp.begin();
	typename _NMSPC::set<int>::const_iterator ite = mp.end();
	for (; it != ite; ++it)
		std::cout << "| " << *it << '\n';
	std::cout << "================\n";
}

void set_coprassion(const _NMSPC::set<int> &mp1, const _NMSPC::set<int> &mp2) {
	std::cout << std::boolalpha << (mp1 == mp2) << '\t';
	std::cout << std::boolalpha << (mp1 != mp2) << '\t';
	std::cout << std::boolalpha << (mp1 < mp2) << '\t';
	std::cout << std::boolalpha << (mp1 <= mp2) << '\t';
	std::cout << std::boolalpha << (mp1 > mp2) << '\t';
	std::cout << std::boolalpha << (mp1 >= mp2) << "\n";
}

void set_test() {
	int a[6] = {4, 8, 15, 16, 23, 42};
	int b[6] = {42, 23, 16, 15, 8, 4};

	std::cout << "Map constructors tests\n";
	{
		_NMSPC::set<int> s1;
		_NMSPC::set<int> s2(a+0, a+6);
		_NMSPC::set<int, std::greater<int> > s3(a+0, a+6);
		_NMSPC::set<int, std::less_equal<int> > s4(a+0, a+6);
		_NMSPC::set<int, std::greater_equal<int> > s5(a+0, a+6);
		_NMSPC::set<int> s6(s2);

		std::cout << "s1\n";
		printInfo(s1);
		std::cout << "s2\n";
		printInfo(s2);
		std::cout << "s3\n";
		printInfo(s3);
		std::cout << "s4\n";
		printInfo(s4);
		std::cout << "s5\n";
		printInfo(s5);
		std::cout << "s6\n";
		printInfo(s6);
	}
	std::cout << "\nAssign operator tests\n";
	{
		_NMSPC::set<int> s1(a + 0, a + 6);
		_NMSPC::set<int> s2;

		std::cout << "s1\n";
		printInfo(s1);

		std::cout << "Before\n";
		std::cout << "s2\n";
		printInfo(s2);
		s2 = s1;
		std::cout << "After\n";
		std::cout << "s2\n";
		printInfo(s2);
	}
	std::cout << "\nIterators tests\n";
	{
		_NMSPC::set<int> s(a + 0, a + 6);

		_NMSPC::set<int>::iterator it = s.begin();
		_NMSPC::set<int>::iterator ite = s.end();
		_NMSPC::set<int>::const_iterator cit = it;
		_NMSPC::set<int>::const_iterator cite = ite;
		_NMSPC::set<int>::reverse_iterator rit = s.rbegin();
		_NMSPC::set<int>::reverse_iterator rite = s.rend();
		_NMSPC::set<int>::const_reverse_iterator rcit = rit;
		_NMSPC::set<int>::const_reverse_iterator rcite = rite;

		(void)cit;
		(void)rcit;
		std::cout << "Iterator output\n";
		for (; it != cite; ++it)
			std::cout << *it << std::endl;
		std::cout << "Reverse iterator output\n";
		for (; rit != rcite; ++rit)
			std::cout << *rit << std::endl;
	}
	std::cout << "\nInsert tests\n";
	{
		_NMSPC::set<int> s(a + 0, a + 6);
		std::cout << "s in start\n";
		printInfo(s);
		std::cout << std::boolalpha << s.insert(4).second << std::endl;
		std::cout << "s\n";
		printInfo(s);
		s.insert(32);
		std::cout << "s\n";
		printInfo(s);
		s.insert(b + 0, b + 6);
		std::cout << "s\n";
		printInfo(s);
	}
	std::cout << "\nErase tests\n";
	{
		_NMSPC::set<int> s(a + 0, a + 6);
		std::cout << "s in start\n";
		printInfo(s);
		std::cout << "erase key ret: " << s.erase(15) << std::endl;
		std::cout << "s\n";
		printInfo(s);
		s.erase(s.begin());
		std::cout << "s\n";
		printInfo(s);
		s.erase(s.begin(), s.end());
		std::cout << "s\n";
		printInfo(s);
	}
	std::cout << "\nSwap and std::Swap tests\n";
	{
		_NMSPC::set<int> s1(a + 0, a + 6);
		_NMSPC::set<int> s2(b + 0, b + 6);
		std::cout << "s1\n";
		printInfo(s1);
		std::cout << "s2\n";
		printInfo(s2);
		std::cout << "set swap\n";
		s1.swap(s2);
		std::cout << "s1\n";
		printInfo(s1);
		std::cout << "s2\n";
		printInfo(s2);
		std::cout << "std swap\n";
		std::swap(s1, s2);
		std::cout << "s1\n";
		printInfo(s1);
		std::cout << "s2\n";
		printInfo(s2);
	}
	std::cout << "\nClear test\n";
	{
		_NMSPC::set<int> s(a+0, a+6);
		std::cout << "s\n";
		printInfo(s);
		s.clear();
		std::cout << "s\n";
		printInfo(s);
	}
	std::cout << "\nFind test\n";
	{
		_NMSPC::set<int> s1(a+0, a+6);
		std::cout << "s1\n";
		printInfo(s1);
		std::cout << *s1.find(4) << std::endl;
		std::cout << *s1.find(8) << std::endl;
		std::cout << *s1.find(15) << std::endl;
		std::cout << *s1.find(16) << std::endl;
		std::cout << *s1.find(23) << std::endl;
		std::cout << *s1.find(42) << std::endl;
		std::cout << std::boolalpha << (s1.find(7) == s1.end()) << std::endl;
		std::cout << "const copy\n";
		_NMSPC::set<int> const s2(s1);
		std::cout << "s2\n";
		printInfo(s2);
		std::cout << *s2.find(4) << std::endl;
		std::cout << *s2.find(8) << std::endl;
		std::cout << *s2.find(15) << std::endl;
		std::cout << *s2.find(16) << std::endl;
		std::cout << *s2.find(23) << std::endl;
		std::cout << *s2.find(42) << std::endl;
		std::cout << std::boolalpha << (s2.find(7) == s2.end()) << std::endl;
	}
	std::cout << "\nCount test\n";
	{
		_NMSPC::set<int> s(a+0, a+6);
		std::cout << "s\n";
		printInfo(s);
		std::cout << s.count(4) << std::endl;
		std::cout << s.count(8) << std::endl;
		std::cout << s.count(15) << std::endl;
		std::cout << s.count(16)<< std::endl;
		std::cout << s.count(23) << std::endl;
		std::cout << s.count(42) << std::endl;
		std::cout << s.count(7) << std::endl;
	}
	std::cout << "\nLower bound test\n";
	{
		_NMSPC::set<int> s(a+0, a+6);
		std::cout << "s\n";
		printInfo(s);
		for (int i = 0; i < 43; ++i)
			std::cout << *s.lower_bound(i) << std::endl;
	}
	std::cout << "\nUpper bound test\n";
	{
		_NMSPC::set<int> s(a+0, a+6);
		std::cout << "s\n";
		printInfo(s);
		for (int i = 0; i < 42; ++i)
			std::cout << *s.upper_bound(i) << std::endl;
	}
	std::cout << "\nEqual range test\n";
	{
		_NMSPC::pair<_NMSPC::set<int>::iterator, _NMSPC::set<int>::iterator> erit;
		_NMSPC::set<int> s(a+0, a+6);
		std::cout << "s\n";
		printInfo(s);
		for (int i = 0; i < 42; ++i) {
			erit = s.equal_range(i);
			std::cout << *erit.first << ' ';
			std::cout << *erit.second << std::endl;
		}
	}
	std::cout << "\nCompression test\n";
	{
		_NMSPC::set<int> s1, s2, s3, s4, s5;

		for (int i = 0; i < 10; ++i)
			s1.insert(i);
		for (int i = 0; i < 10; ++i)
			s2.insert(i+1);
		for (int i = 0; i < 10; ++i)
			s3.insert(i-1);
		for (int i = 0; i < 20; ++i)
			s4.insert(i);
		for (int i = 0; i < 20; ++i)
			s5.insert(i+1);

		std::cout << "==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		set_coprassion(s1, s1);
		set_coprassion(s1, s2);
		set_coprassion(s1, s3);
		set_coprassion(s1, s4);
		set_coprassion(s1, s5);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		set_coprassion(s2, s1);
		set_coprassion(s2, s2);
		set_coprassion(s2, s3);
		set_coprassion(s2, s4);
		set_coprassion(s2, s5);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		set_coprassion(s3, s1);
		set_coprassion(s3, s2);
		set_coprassion(s3, s3);
		set_coprassion(s3, s4);
		set_coprassion(s3, s5);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		set_coprassion(s4, s1);
		set_coprassion(s4, s2);
		set_coprassion(s4, s3);
		set_coprassion(s4, s4);
		set_coprassion(s4, s5);

		std::cout << "\n==\t\t!=\t\t<\t\t<=\t\t>\t\t>=\n";
		set_coprassion(s5, s1);
		set_coprassion(s5, s2);
		set_coprassion(s5, s3);
		set_coprassion(s5, s4);
		set_coprassion(s5, s5);
	}
}

int main() {
	vector_test();
	stack_test();
	map_test();
	set_test();
}


