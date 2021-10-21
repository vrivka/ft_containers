#include <iostream>
#include "ft_vector.hpp"
#include <iomanip>
#include <vector>
#include <algorithm>

class A {
public:
	int i;
	int *a;

	void print() const {
		for (int c = 0; c < 5; c++)
			std::cout << a[c] << std::endl;
	}
	A() : i(1), a(new int[5]()) {
		for (int c = 0; c < 5; c++)
			a[c] = c;
		std::cout << "const" << std::endl; };
	A(A const &r) : i(r.i), a(new int[5]()) {
		for (int t = 0; t < 5; t++)
			a[t] = r.a[t];
		std::cout << "copy const" << std::endl; };
	~A() { std::cout << "des" << std::endl; delete [] a; }
	bool operator==(const A &other) const {
		if (i == other.i) {
			for (int i = 0; i < 5; i++) {
				if (a[i] == other.a[i])
					continue;
				else
					return false;
			}
			return true;
		}
		return false;
	}
	bool operator!=(const A &other) const {
		return !(*this == other);
	}
	bool operator<(const A &other) const {
		if (i < other.i) {
			for (int i = 0; i < 5; i++) {
				if (a[i] < other.a[i])
					continue ;
				else
					return false;
			}
			return true;
		}
		return false;
	}
	bool operator<=(const A &other) const {
		return !(other < *this);
	}
	bool operator>(const A &other) const {
		return other < *this;
	}
	bool operator>=(const A &other) const {
		return !(*this < other);
	}
};


int main() {
	std::vector<A> a(5);
	std::cout << std::endl;
	a.insert(a.begin() += 3, A());
	std::cout << std::endl;
	a.insert(a.begin() += 3, A());
	std::cout << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	std::cout << std::endl;

//	::vector<int>::difference_type len = a.rbegin() - a.rend();

//	std::cout << *std::find(a.rbegin(), a.rend(), 7) << std::endl;
//	for (int d = 0; d < 10; d++)
//		std::cout << a[d] << std::endl;
	/*	A a;
	A b[500];
	std::vector<A> c(500);
	std::vector<A> d(500, a);
	std::vector<A> e(b, b+500);
	std::vector<A> f(c);
	std::vector<A> g(d);
	std::vector<A> h(e);
	A b;
	std::cout << std::endl;

	::vector<int> a(5u, 10);
	::vector<int> b(5u, 10);
	std::cout << std::endl;

	a[3] = 9;
	a[2] = 11;
	if (a > b)
		std::cout << "true\n";
	else
		std::cout << "false\n";
	a.swap(b);
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	a.clear();
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	std::cout << b.size() << std::endl;
	std::cout << b.capacity() << std::endl;
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.push_back(b);
	std::cout << std::endl;
	std::cout << std::endl;

	a.assign(6, A());
	std::cout << std::endl;

	A d = a.back();
	try {
		A const d = a.at(0);
	}
	catch (std::out_of_range &oor) {
		std::cerr << oor.what() << std::endl;
	}
	a.resize(7, A());
	a.resize(1);
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	std::cout << a.max_size() << std::endl;
	std::cout << a.empty() << std::endl;
	a[0].print();*/
	return 0;
}
