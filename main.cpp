#include <iostream>
#include "ft_vector.hpp"
#include "ft_stack.hpp"
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include "ft_map.hpp"
#include "RBNode.hpp"
#include "RBTree.hpp"
#include <memory>
#include <utility>


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
	bool operator==(const A &other) const { std::cout << other.i << " equal operator\n"; return i == other.i; }
	bool operator!=(const A &other) const { std::cout << other.i << " not equal operator\n"; return !(*this == other); }
	bool operator<(const A &other) const { std::cout << other.i << " less operator\n"; return i < other.i; }
	bool operator<=(const A &other) const { std::cout << other.i << " less-equal operator\n"; return i <= other.i; }
	bool operator>(const A &other) const { std::cout << other.i << " more operator\n"; return i > other.i; }
	bool operator>=(const A &other) const { std::cout << other.i << " more-equal operator\n"; return i >= other.i; }
	friend std::ostream &operator<<(std::ostream &out, A const &c) {
		out << c.i;
		return out;
	}
};


int main() {
//	namespace ft = std;
	ft::pair<int, A> p[  3] = {ft::pair<int,A>(1, 2),ft::pair<int,A>(2, 3),ft::pair<int,A>(3, 4)};
	//	std::pair<int, A> p1[3] = {std::pair<int,A>(1, 2),std::pair<int,A>(2, 3),std::pair<int,A>(3, 4)};
	std::cout << "\n";
	ft::map<int, A> *a = new ft::map<int,A>(p+0, p+3);
	std::cout << "\n";
	ft::map<int, A> b(*a);

	delete a;

	b.insert(ft::make_pair(0, 1));
	b.insert(ft::make_pair(4, 5));
	b.insert(ft::make_pair(5, 6));
	b.insert(ft::make_pair(6, 7));
	b.insert(ft::make_pair(7, 8));

	a = new ft::map<int,A>(b);

	delete a;
//	for (int i = 0; i < 1000000; i++)
//		a.insert(ft::make_pair(i, i * 5));

//	ft::map<int, A>::iterator it = a.begin();
//	ft::map<int, A>::iterator ite = a.end();

//	for (; it != ite; it++ )
//		std::cout << it->first << ' ' << it->second << std::endl;
//	std::cout << "\n";
//	a.print();
//	std::cout << a.size() << std::endl;
	std::cout << "\n";
}
// 9.262
// 9.079