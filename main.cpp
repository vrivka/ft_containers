#include <iostream>
#include "ft_map.hpp"
#include "ft_vector.hpp"
#include "ft_stack.hpp"
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


//class B {
//public:
//	char *l;
//	int i;
//	B():l(nullptr), i(1) {};
//	B(const int &ex) {
//		this->i = ex;
//		this->l = new char('a');
//	};
//	virtual ~B() {
//		delete this->l;
//		this->l = nullptr;
//	};
//};
//
//class A : public B {
//public:
//	A():B(){};
//	A(const B* ex){
//		this->l = new char(*(ex->l));
//		this->i = ex->i;
//		if (ex->i == -1) throw "n";
//	}
//	~A() {
//		delete this->l;
//		this->l = nullptr;
//	};
//};
#include <fstream>
time_t g_start2 = 0;
time_t g_end2 = 0;
time_t g_start1 = 0;
time_t g_end1 = 0;

template<class C>
void fillMap(std::map<int, int, C> &mp) {
	mp.insert(std::make_pair(16, 3));
	mp.insert(std::make_pair(8, 3));
	mp.insert(std::make_pair(23, 3));
	mp.insert(std::make_pair(7, 3));
	mp.insert(std::make_pair(19, 3));
	mp.insert(std::make_pair(29, 3));
	mp.insert(std::make_pair(41, 3));
	mp.insert(std::make_pair(4, 3));
	mp.insert(std::make_pair(11, 3));
}

class MapBoolTest {
	public:
		std::map<int, int, std::greater<int> > m1, m2, m3, m4;
		std::map<std::string, std::string, std::greater<std::string> > m5, m6, m7, m8, m9;
		ft::map<int, int, std::greater<int> > mp1, mp2, mp3, mp4;
		ft::map<std::string, std::string, std::greater<std::string> > mp5, mp6, mp7, mp8, mp9;

		MapBoolTest() {
			m1.insert(std::make_pair(2, 3)); mp1.insert(ft::make_pair(2, 3));
			m2.insert(std::make_pair(3, 3)); mp2.insert(ft::make_pair(3, 3));
			m3.insert(std::make_pair(3, 4)); mp3.insert(ft::make_pair(3, 4));
			m4.insert(std::make_pair(4, 4)); mp4.insert(ft::make_pair(4, 4));
			m4.insert(std::make_pair(4, 5)); mp4.insert(ft::make_pair(4, 5));
			m5.insert(std::make_pair("123", "123")); mp5.insert(ft::make_pair("123", "123"));
			m6.insert(std::make_pair("123", "124")); mp6.insert(ft::make_pair("123", "124"));
			m7.insert(std::make_pair("124", "123")); mp7.insert(ft::make_pair("124", "123"));
			m8.insert(std::make_pair("12", "123")); mp8.insert(ft::make_pair("12", "123"));
			m9.insert(std::make_pair("123", "12")); mp9.insert(ft::make_pair("123", "12"));
		}
	};

int main() {
	{
		std::ofstream out("./std");
		out.clear();
		std::map<int,int> mp;
		std::vector<int> v;
		mp.insert(std::make_pair(3, 3));
		std::map<int,int>::iterator it = mp.begin();
		g_start1 = timer();
		v.push_back(it->first);
		v.push_back(it->second);
		mp[3] = 10;
		v.push_back(it->first);
		v.push_back(it->second);
		mp[2] = 9;
		it = mp.begin();
		v.push_back(it->first);
		v.push_back(it->second);
		it++;
		v.push_back(it->first);
		v.push_back(it->second);
		v.push_back(mp.size());
		g_end1 = timer();
		for (int i = 0, d = v.size(); i < d; i++)
			out << v[i] << std::endl;
		out << difftime(g_end1, g_start1) << std::endl;
		out.close();
	}
	{
		std::ofstream out("./ft");
		out.clear();
		ft::map<int,int> mp;
		std::vector<int> v;
		mp.insert(ft::make_pair(3, 3));
		ft::map<int,int>::iterator it = mp.begin();
		g_start2 = timer();
		v.push_back(it->first);
		v.push_back(it->second);
		mp[3] = 10;
		v.push_back(it->first);
		v.push_back(it->second);
		mp[2] = 9;
		it = mp.begin();
		v.push_back(it->first);
		v.push_back(it->second);
		it++;
		v.push_back(it->first);
		v.push_back(it->second);
		v.push_back(mp.size());
		g_end2 = timer();
		for (int i = 0, d = v.size(); i < d; i++)
			out << v[i] << std::endl;
		out << difftime(g_end2, g_start2) << std::endl;
		out.close();
	}
}

