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
	friend std::ostream &operator<<(std::ostream &out, A const &c) { out << c.i; return out; }
};


int main() {
//	namespace ft = std;
//	ft::pair<int, A> p[  3] = {ft::pair<int,A>(1, 2),ft::pair<int,A>(2, 3),ft::pair<int,A>(3, 4)};
	//	std::pair<int, A> p1[3] = {std::pair<int,A>(1, 2),std::pair<int,A>(2, 3),std::pair<int,A>(3, 4)};
//	ft::map<int, A> a;
//	std::cout << "\n";
//
//	for (int i = 1; i < 8; i++)
//		a.insert(ft::make_pair(i, i * 5));
//	std::cout << "\n";
//
//
//	a[8] = 10;
//	std::cout << "\n";
	ft::pair<int,A> p1(1, 2);
	std::cout << std::boolalpha << (1 == p1) << std::endl;
}
// 2.618
//2.604

// 3.946
//3.989

// 3.925
//4.006