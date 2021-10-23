#include <iostream>
#include "ft_vector.hpp"
#include <iomanip>
#include <vector>
#include <algorithm>

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

#include <deque>
#include <stack>
#include <queue>
#include <memory>

int main() {
	ft::vector<A> a(5);
	std::cout << "\n";
	ft::vector<A> b(9);
	std::cout << "\n";
	std::generate(a.begin(), a.end(), gen);
	std::cout << "\n";
	std::generate(b.begin(), b.end(), gen);
	std::cout << "\n";

	a = b;

	std::cout << "\n";
	std::cout << std::setiosflags(std::ios::boolalpha) << a.empty() << "\nsize: " << a.size() << "\ncap: " << a.capacity() << std::endl;
	std::cout << "\n";
}
