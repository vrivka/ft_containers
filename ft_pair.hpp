#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

namespace ft {
template<class T1, class T2>
class pair {
public:
	typedef	T1	first_type;	//	The first template parameter
	typedef	T2	second_type;//	The second template parameter

	first_type	first;
	second_type	second;

	/**	Constructors	**/

	pair() : first(), second() {}

	template<class U, class V>
	pair(const pair<U,V> &other) : first(other.first), second(other.second) {}

	pair(const first_type &first, const second_type &second) : first(first), second(second) {}

	/**	Destructor	**/

	~pair() {}

	/**	Assign overload	**/
	pair &operator=(const pair &other) {
		if (this == &other)
			return *this;
		first = other.first;
		second = other.second;
		return *this;
	}

	/**	Non-member functions	**/

	friend bool operator==(const pair &left, const pair &right) {
		if (left.first == right.first)
			if (left.second == right.second)
				return true;
		return false;
	}

	friend bool operator!=(const pair &left, const pair &right) { return !(left == right); }

	friend bool operator<(const pair &left, const pair &right) {
		if (left.first < right.first)
			return true;
		if (!(right.first < left.first))
			if (left.second < right.second)
				return true;
		return false;
	}

	friend bool operator<=(const pair &left, const pair &right) { return !(right < left); }

	friend bool operator>(const pair &left, const pair &right) { return right < left; }

	friend bool operator>=(const pair &left, const pair &right) { return !(left < right); }
};

template <class T1, class T2>
pair<T1,T2> make_pair(T1 x, T2 y) { return pair<T1,T2>(x, y); }

}

#endif
