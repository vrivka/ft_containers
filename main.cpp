#include <iostream>
#include "ft_map.hpp"
#include "ft_vector.hpp"
#include "ft_stack.hpp"
#include "ft_set.hpp"
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <ctime>


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
	bool operator==(const A &other) const { std::cout << this->i << "==" << other.i << " equal operator\n"; return i == other.i; }
	bool operator!=(const A &other) const { std::cout << this->i << "!=" << other.i << " not equal operator\n"; return !(*this == other); }
	bool operator<(const A &other) const { std::cout << this->i << "<" << other.i << " less operator\n"; return i < other.i; }
	bool operator<=(const A &other) const { std::cout << this->i << "<=" << other.i << " less-equal operator\n"; return i <= other.i; }
	bool operator>(const A &other) const { std::cout << this->i << ">" << other.i << " more operator\n"; return i > other.i; }
	bool operator>=(const A &other) const { std::cout << this->i << ">=" << other.i << " more-equal operator\n"; return i >= other.i; }
	friend std::ostream &operator<<(std::ostream &out, A const &c) { out << c.i; return out; }
};

#include <sys/time.h>

time_t timer() {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}

#include <fstream>
time_t g_start2 = 0;
time_t g_end2 = 0;
time_t g_start1 = 0;
time_t g_end1 = 0;

#include "set"

class SetBoolTest {
public:
	std::set<int> s1, s2, s3, s4;
	std::set<std::string> s5, s6, s7, s8, s9;
	ft::set<int> st1, st2, st3, st4;
	ft::set<std::string> st5, st6, st7, st8, st9;

	SetBoolTest() {
		s1.insert(2); st1.insert(2);
		s2.insert(3); st2.insert(3);
		s3.insert(3); st3.insert(3);
		s4.insert(4); st4.insert(4);
		s4.insert(4); st4.insert(4);
		s5.insert("122"); st5.insert("122");
		s6.insert("123"); st6.insert("123");
		s7.insert("124"); st7.insert("124");
		s8.insert("12"); st8.insert("12");
		s9.insert("123"); st9.insert("123");
	}
};

int main() {
//	namespace ft = std;
	ft::map<A,int> a;

	a.insert(ft::make_pair(00, 2));
	a.insert(ft::make_pair(10, 2));
	a.insert(ft::make_pair(20, 2));
	a.insert(ft::make_pair(30, 2));
	a.insert(ft::make_pair(40, 2));
	a.insert(ft::make_pair(50, 2));
	a.insert(ft::make_pair(60, 2));
	a.insert(ft::make_pair(70, 2));
	std::cout << "\n";
	std::cout << std::boolalpha << a.upper_bound(30)->first << '\n';
	std::cout << "\n";
}

