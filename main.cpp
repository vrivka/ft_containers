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

int main() {
	std::allocator<RBNode<int> > A;
	RBNode<int> *b = A.allocate(1);
	A.construct(b, 5);
	b->color = BLACK;

	std::cout << b->val << std::endl;
	RBNode<int>::add(b, 1);
	RBNode<int>::add(b, 15);
	RBNode<int>::add(b, 28);
	RBNode<int>::add(b, 12);
	RBNode<int>::add(b, 44);
	RBNode<int>::add(b, 0);
	RBNode<int>::print(b);
}
