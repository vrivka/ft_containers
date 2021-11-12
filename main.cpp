#include <iostream>
#include "ft_vector.hpp"
#include "ft_stack.hpp"
#include "ft_map.hpp"
#include "ft_set.hpp"
#include <iomanip>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

class A {
public:
	int i;
	int *a;

	A() : i(0), a(new int[5]()) { std::cout << i << " constructor\n"; };
	A(int i) : i(i), a(new int[5]()) { std::cout << i << " int constructor\n"; };
	A(A const &r) : i(r.i), a(new int[5]()) { std::cout << r.i << " copy constructor\n"; };
	~A() { std::cout << i << " destructor\n"; delete [] a; }
	A &operator=(A const &other) { std::cout << other.i << " assign operator\n"; if (this == &other) return *this; this->i = other.i; return *this; };
	A &operator=(int const &other) { std::cout << other << " int assign operator\n"; if (this->i == other) return *this; this->i = other; return *this; };
	bool operator==(const A &other) const { std::cout << this->i << "==" << other.i << " equal operator\n"; return i == other.i; }
	bool operator!=(const A &other) const { std::cout << this->i << "!=" << other.i << " not equal operator\n"; return !(*this == other); }
	bool operator<(const A &other) const { std::cout << this->i << "<" << other.i << " less operator\n"; return i < other.i; }
	bool operator<=(const A &other) const { std::cout << this->i << "<=" << other.i << " less-equal operator\n"; return i <= other.i; }
	bool operator>(const A &other) const { std::cout << this->i << ">" << other.i << " more operator\n"; return i > other.i; }
	bool operator>=(const A &other) const { std::cout << this->i << ">=" << other.i << " more-equal operator\n"; return i >= other.i; }
	friend std::ostream &operator<<(std::ostream &out, A const &c) { out << c.i; return out; }
};

template<class T>
void printInfo(const ft::vector<T> &vec) {
	std::cout << "=======Vector<T>======\n";
	std::cout << "| Is empty?: " << std::boolalpha << vec.empty() << '\n';
	std::cout << "| Size: " << vec.size() << '\n';
	std::cout << "| Capacity: " << vec.capacity() << '\n';
	std::cout << "| Contain:\n";
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename ft::vector<T>::const_iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << "| " << *it << '\n';
	std::cout << "======================\n";
}

template<class T1, class T2>
void printInfo(const ft::vector<ft::pair<T1, T2> > &vec) {
	std::cout << "=======Vector<pair<T1,T2>>======\n";
	std::cout << "| Is empty?: " << std::boolalpha << vec.empty() << '\n';
	std::cout << "| Size: " << vec.size() << '\n';
	std::cout << "| Capacity: " << vec.capacity() << '\n';
	std::cout << "| Contain:\n";
	typename ft::vector<ft::pair<T1, T2> >::const_iterator it = vec.begin();
	typename ft::vector<ft::pair<T1, T2> >::const_iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << "| first: " << it->first << " second: " << it->second << '\n';
	std::cout << "=============================\n";
}

template<class T>
void printInfo(const std::vector<T> &vec) {
	std::cout << "=======Vector<T>======\n";
	std::cout << "| Is empty?: " << std::boolalpha << vec.empty() << '\n';
	std::cout << "| Size: " << vec.size() << '\n';
	std::cout << "| Capacity: " << vec.capacity() << '\n';
	std::cout << "| Contain:\n";
	typename std::vector<T>::const_iterator it = vec.begin();
	typename std::vector<T>::const_iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << "| " << *it << '\n';
	std::cout << "======================\n";
}

template<class T1, class T2>
void printInfo(const std::vector<std::pair<T1, T2> > &vec) {
	std::cout << "=======Vector<pair<T1,T2>>======\n";
	std::cout << "| Is empty?: " << std::boolalpha << vec.empty() << '\n';
	std::cout << "| Size: " << vec.size() << '\n';
	std::cout << "| Capacity: " << vec.capacity() << '\n';
	std::cout << "| Contain:\n";
	typename std::vector<std::pair<T1, T2> >::const_iterator it = vec.begin();
	typename std::vector<std::pair<T1, T2> >::const_iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << "| first: " << it->first << " second: " << it->second << '\n';
	std::cout << "=============================\n";
}

template<class T>
void vec_coprassion(const ft::vector<T> &v1, const ft::vector<T> &v2) {
	std::cout << std::boolalpha << (v1 == v2) << '\t';
	std::cout << std::boolalpha << (v1 != v2) << '\t';
	std::cout << std::boolalpha << (v1 < v2) << '\t';
	std::cout << std::boolalpha << (v1 <= v2) << '\t';
	std::cout << std::boolalpha << (v1 > v2) << '\t';
	std::cout << std::boolalpha << (v1 >= v2) << "\n";
}

template<class T>
void vec_coprassion(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::cout << std::boolalpha << (v1 == v2) << '\t';
	std::cout << std::boolalpha << (v1 != v2) << '\t';
	std::cout << std::boolalpha << (v1 < v2) << '\t';
	std::cout << std::boolalpha << (v1 <= v2) << '\t';
	std::cout << std::boolalpha << (v1 > v2) << '\t';
	std::cout << std::boolalpha << (v1 >= v2) << "\n";
}

void vector_test() {
	namespace ft = std;
	int a[6] = {4, 8, 15, 16, 23, 42};
	int b[6] = {42, 23, 16, 15, 8, 4};

	std::cout << "Vector constructors tests\n";
	{
		ft::vector<int> v1;
		ft::vector<int> v2(6);
		ft::vector<int> v3(6, 100);
		ft::vector<int> v4(a + 0, a + 6);
		ft::vector<int> v5(v4.begin(), v4.end());
		ft::map<int, int> m;
		for (int i = 0; i < 6; ++i)
			m.insert(ft::make_pair(a[i], b[i]));
		ft::vector<ft::pair<int, int> > v6(m.begin(), m.end());
		const ft::vector<int> &v7(v5);
		const ft::vector<ft::pair<int, int> > &v8(v6);
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
		ft::vector<int> v1(10, 100);
		ft::vector<int> v2(5, 50);

		std::cout << "v1\n";
		printInfo(v1);

		std::cout << "Before\n";
		std::cout << "v2\n";
		printInfo(v2);
		v2 = v1;
		std::cout << "After\n";
		std::cout << "v2\n";
		printInfo(v2);

		ft::vector<int> v3(15, 150);
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
		ft::vector<int> v(a + 0, a + 6);

		ft::vector<int>::iterator it = v.begin();
		ft::vector<int>::iterator ite = v.end();
		ft::vector<int>::const_iterator cit = it;
		ft::vector<int>::const_iterator cite = ite;
		ft::vector<int>::reverse_iterator rit = v.rbegin();
		ft::vector<int>::reverse_iterator rite = v.rend();
		ft::vector<int>::const_reverse_iterator rcit = rit;
		ft::vector<int>::const_reverse_iterator rcite = rite;

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
		ft::vector<int> v(a+0, a+6);
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
		ft::vector<int> v(a+0, a+6);
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
		ft::vector<int> v1(a+0, a+6);
		for (int i = 0; i < 6; ++i)
			std::cout << v1[i] << std::endl;
		std::cout << "const\n";
		ft::vector<int> const v2(a+0, a+6);
		for (int i = 0; i < 6; ++i)
			std::cout << v2[i] << std::endl;
	}
	std::cout << "\n\"at\" tests\n";
	{
		ft::vector<int> v1(a+0, a+6);
		try {
			for (int i = 0; i < 10; ++i)
				std::cout << v1.at(i) << std::endl;
		}
		catch (std::out_of_range &oor) {
			std::cout << oor.what() << ": out of range access\n";
		}
		std::cout << "const copy\n";
		ft::vector<int> const v2(v1);
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
		ft::vector<int> v1(5, 10);
		std::cout << "v\n";
		printInfo(v1);
		std::cout << "First element: " << v1.front() << std::endl;
		v1.front() = 20;
		printInfo(v1);
		std::cout << "const copy\n";
		ft::vector<int> const v2(v1);
		std::cout << "First element: " << v2.front() << std::endl;
	}
	std::cout << "\nBack tests\n";
	{
		ft::vector<int> v1(5, 10);
		std::cout << "v\n";
		printInfo(v1);
		std::cout << "Last element: " << v1.back() << std::endl;
		v1.back() = 20;
		printInfo(v1);
		std::cout << "const copy v\n";
		ft::vector<int> const v2(v1);
		std::cout << "Last element: " << v2.back() << std::endl;
	}
	std::cout << "\nData tests\n";
	{
		ft::vector<int> v1(a+0, a+6);
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
		ft::vector<int> const v2(v1);
		std::cout << "v\n";
		printInfo(v2);
		const int *const_arr = v2.data();
		std::cout << "Data print with int*\n";
		for (int i = 0; i < 6; ++i)
			std::cout << const_arr[i] << std::endl;
	}
	std::cout << "\nAssign tests\n";
	{
		ft::vector<int> v1(a + 0, a + 6);
		ft::vector<int> v2(v1);
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
		ft::vector<int> v;
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
		ft::vector<int> v(a+0, a+6);
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
		ft::vector<int> v;
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
		ft::vector<int> v(a+0, a+6);
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
		ft::vector<int> v1(a+0, a+6);
		ft::vector<int> v2(b+0, b+6);
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
		ft::vector<int> v(a+0, a+6);
		std::cout << "v\n";
		printInfo(v);
		v.clear();
		std::cout << "v\n";
		printInfo(v);
	}
	std::cout << "\nGet allocator tests\n";
	{
		ft::vector<int> v1;

		std::cout << std::boolalpha << (typeid(v1.get_allocator()) == typeid(std::allocator<int>)) << ' ' << typeid(v1.get_allocator()).name() << std::endl;

		ft::vector<std::string> v2;

		std::cout << std::boolalpha << (typeid(v2.get_allocator()) == typeid(std::allocator<std::string>)) << ' ' << typeid(v2.get_allocator()).name() << std::endl;

	}
	std::cout << "\nCompression tests\n";
	{
		ft::vector<int> v1(10, 100), v2(10, 200), v3(10, 50), v4(5, 100), v5(5, 200), v6(5, 50);

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

void stack_test() {

}

int main() {
	vector_test();
}

