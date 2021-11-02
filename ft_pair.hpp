#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

namespace ft {
template<class T1, class T2>
class pair {
public:
	typedef	T1	first_type;	//	The first template parameter (T1)
	typedef	T2	second_type;//	The second template parameter (T2)
	const first_type first;
	second_type	second;
	pair() : first(), second() {}
	template<class U, class V>
	pair(const pair<U,V> &other) : first(other.first), second(other.second) {}
	pair(const first_type &first, const second_type &second) : first(first), second(second) {}
	~pair() {}
	pair &operator=(const pair &other) {
		if (this == *other)
			return *this;
		this->first = other.first;
		this->second = other.second;
		return *this;
	}
	friend bool operator==(const pair &lhs, const pair &rhs) {
		if (lhs.first == rhs.first)
			if (lhs.second == rhs.second)
				return true;
		return false;
	}
	friend bool operator==(const first_type &lhs, const pair &rhs) { return lhs == rhs.first; }
	friend bool operator!=(const pair &lhs, const pair &rhs) { return !(lhs == rhs); }
	friend bool operator<(const pair &lhs, const pair &rhs) {
		if (lhs.first < rhs.first)
			return true;
		if (!(rhs.first < lhs.first))
			if (lhs.second < rhs.second)
				return true;
		return false;
	}
	friend bool operator<=(const pair &lhs, const pair &rhs) { return !(rhs < lhs); }
	friend bool operator>(const pair &lhs, const pair &rhs) { return rhs < lhs; }
	friend bool operator>=(const pair &lhs, const pair &rhs) { return !(lhs < rhs); }
};

template <class T1, class T2>
pair<T1,T2> make_pair(T1 x, T2 y) { return pair<T1,T2>(x, y); }

}


#endif //FT_PAIR_HPP
