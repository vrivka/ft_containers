#include <iostream>
#include "ft_vector.hpp"
#include <vector>

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
		std::cout << "const " << this << std::endl; };
	A(A const &r) : i(r.i), a(new int[5]()) {
		for (int t = 0; t < 5; t++)
			a[t] = r.a[t];
		std::cout << "copy const " << this << std::endl; };
	~A() { std::cout << "des " << this << std::endl; delete [] a; }
};


int main() {
//	std::string arr[6] = {"4","8","15","16","23","42"};
//	::vector<int> a;
//	::vector<int> b(10u, 100);
//	::vector<int> c(b);
//	::vector<std::string> d(arr, arr + 6);
	A a;
	A b[500];
	std::vector<A> c(500);
	std::vector<A> d(500, a);
	std::vector<A> e(b, b+500);
	std::vector<A> f(c);
	std::vector<A> g(d);
	std::vector<A> h(e);


//	e.arr[0].a[0] = 111111111;
//	for(int m = 0; m < 5; ++m)
//		e.arr[m].print();
	//	for (int i = 0; i < 10; i++)
//		std::cout << b.arr[i] << std::endl;
//	for (int i = 0; i < 10; i++)
//		std::cout << c.arr[i] << std::endl;
//	for (int i = 0; i < 6; i++)
//		std::cout << d.arr[i] << std::endl;
	return 0;
}
