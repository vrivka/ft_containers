#include <iostream>
#include "ft_vector.hpp"
#include <iomanip>
#include <vector>
#include <algorithm>

class A {
public:
	int i;
	int *a;

	A() : i(0), a(new int[5]()) { std::cout << "constructor\n"; };
	A(int i) : i(i), a(new int[5]()) { std::cout << i << " int constructor\n"; };
	A(A const &r) : i(r.i), a(new int[5]()) { std::cout << r.i << " copy constructor\n"; };
	~A() { std::cout << i << " destructor\n"; delete [] a; }
	A &operator=(A const &other) { std::cout << other.i << " assign operator\n"; if (this == &other) return *this; this->i = other.i; return *this; };
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

bool func2(int i) {
	return i == 4 * 4;
}

bool func3(int i) {
	return i <= 11;
}

int gen() {
	return rand() % 100;
}

int main() {
	A arr[5] = {1, 2, 3, 4, 5};
	std::cout << "\n";
	A b(0);
	std::cout << "\n";
	A c(6);
	std::cout << "\n";
	A d(7);
	std::cout << "\n";
	std::vector<A> a(arr, arr + 5);
	std::cout << "\n";

	a.insert(a.begin() + 1, 1, c);
	std::cout << "\n";
	a.insert(a.end(), 2, d);
	std::cout << "\n";
	a.insert(a.begin(), 1, c);
	std::cout << "\n";
	a.insert(a.end() - 5, 11, d);
	std::cout << "\n";
//	a.insert(a.end(), d);
//	std::cout << "\n";
	std::for_each(a.begin(), a.end(), func1)(b);
	std::cout << "\nsize: " << a.size() << "\ncapacity: " << a.capacity() << std::endl;
}
