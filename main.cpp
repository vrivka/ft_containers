#include <iostream>
#include "ft_vector.hpp"
#include "ft_stack.hpp"
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
//#include "ft_map.hpp"
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
	std::less<int> l;
	std::allocator<ft::pair<int,int> > a;
	RBTree<ft::pair<int,int>, std::less<int>, std::allocator<ft::pair<int,int> > > t(&a, &l);

	t.insert(ft::make_pair(1, 2));
	t.insert(ft::make_pair(2, 2));
	t.insert(ft::make_pair(3, 2));
	t.insert(ft::make_pair(4, 2));
	t.insert(ft::make_pair(5, 2));
	t.print();

	RBTree<ft::pair<int,int>, std::less<int>, std::allocator<ft::pair<int,int> > >::iterator it = t.begin();
	RBTree<ft::pair<int,int>, std::less<int>, std::allocator<ft::pair<int,int> > >::const_iterator ite;

	ite = it;

	for (; it != ite; it++)
		std::cout << it->first << std::endl;
}
