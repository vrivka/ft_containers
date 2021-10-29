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
#include "RBT.hpp"


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

void func1(A &i) {
	std::cout << ' ' << i.i;
}

//void func1(int &i) {
//	std::cout << ' ' << i;
//}

bool func2(int i) {
	return i == 4 * 4;
}

bool func3(int i) {
	return i <= 11;
}

int ge = 1;

int gen() {
	return ge++;
}

typedef RBNode<int,A, std::greater<int>, std::allocator<ft::pair<int,A> > > NODE;

#include <memory>

int main() {
//	std::allocator<ft::pair<int,A> > Al;
//	std::allocator<int>::rebind<NODE>::other An;
//	std::greater<int> Co;
//	NODE *b = An.allocate(1);
//	An.construct(b, NODE(ft::make_pair<int,A>(0, 0), Al, An, Co));
//	b->color = BLACK;

//	std::cout << b->val->first << std::endl;
//	std::cout << b->val->second << std::endl;
//	b = b->add(b, ft::make_pair<int,A>(1, 1));
//	b = b->add(b, ft::make_pair<int,A>(2, 12));
//	b->add(b, ft::make_pair(2, 16));
//	b->add(b, ft::make_pair(2, 16));
//	b->add(b, ft::make_pair(2, 16));
//	b->add(b, ft::make_pair(2, 16));
//	b->add(b, ft::make_pair(2, 16));
//	b->add(b, 15);
//	b->add(b, 28);
//	b->add(b, 12);
//	b->add(b, 44);
//	b->add(b, 0);
//	b->print(b);

//	An.destroy(b);
//	An.deallocate(b, 1);
//	std::allocator<ft::pair<int,A> > a;
//	std::less<int> c;
//	ft::pair<int,A> pt[3] = {ft::make_pair<int,A>(0, 10), ft::make_pair<int,A>(0, 11), ft::make_pair<int,A>(0, 12)};
//	std::pair<int,A> pm[3] = {std::make_pair(0, 20), std::make_pair<int,A>(0, 21), std::make_pair<int,A>(0, 22)};
//	std::cout << "\n";
//	RBT<int,A,std::less<int>,std::allocator<ft::pair<int,A> > > t(&a, &c);
//
//	t.insert(pt[0]);
//	t.insert(pt[1]);
//	t.insert(pt[2]);
//
//
//	std::cout << "\n";
//	std::map<int, A, std::less<int> > m;
//
//	m.insert(pm[0]);
//	m.insert(pm[1]);
//	m.insert(pm[2]);
//	a.inse
	std::vector<A> a(10);
}
