#include <iostream>
#include "ft_vector.hpp"
#include <vector>
static int k = 0;

int printc() {
	std::cout << "print" << std::endl;
	return (k++);
}

class A {
public:
	int i;
	int *a;

	void print() const {
		for (int c = 0; c < 10; c++)
			std::cout << a[c] << std::endl;
	}
	A() : i(printc()), a(new int[10]()) {
		for (int c = 0; c < 10; c++)
			a[c] = c;
		std::cout << "const" << std::endl; }
	~A() { std::cout << "des" << std::endl; delete [] a; }
};


int main() {
//	std::string arr[6] = {"4","8","15","16","23","42"};
//	::vector<int> a;
//	::vector<int> b(10u, 100);
//	::vector<int> c(b);
//	::vector<std::string> d(arr, arr + 6);
	::vector<A> e(10);

	e.arr[0].a[0] = 111111111;
	for(int m = 0; m < 10; ++m)
		e.arr[m].print();
	//	for (int i = 0; i < 10; i++)
//		std::cout << b.arr[i] << std::endl;
//	for (int i = 0; i < 10; i++)
//		std::cout << c.arr[i] << std::endl;
//	for (int i = 0; i < 6; i++)
//		std::cout << d.arr[i] << std::endl;
	return 0;
}
