#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
template<class V>
class vec_iterator {
public:
	typedef V													iterator_type;		//	Iterator's type
	typedef typename ft::iterator_traits<V>::iterator_category	iterator_category;	//	Preserves Iterator's category
	typedef typename ft::iterator_traits<V>::value_type			value_type;			//	Preserves Iterator's value type
	typedef typename ft::iterator_traits<V>::difference_type	difference_type;	//	Preserves Iterator's difference type
	typedef typename ft::iterator_traits<V>::pointer			pointer;			//	Preserves Iterator's pointer type
	typedef typename ft::iterator_traits<V>::reference			reference;			//	Preserves Iterator's reference type
private:
	iterator_type iter;
public:
	/* Constructors */

	vec_iterator() : iter() {};
	vec_iterator(vec_iterator const &other) : iter(other.iter) {};
	vec_iterator(iterator_type x) : iter(x) {};

	/* Destructors */

	~vec_iterator() {};

	/* Member functions */

	iterator_type base() { return iter; };

	reference operator*() const throw() { return *iter; };

	vec_iterator<iterator_type> operator+(difference_type n) { return iter + n; };
	vec_iterator<iterator_type> operator+(difference_type n) const { return iter + n; };

	vec_iterator<iterator_type> &operator++() {
		++iter;
		return *this;
	};
	vec_iterator<iterator_type> operator++(int) {
		vec_iterator<iterator_type> tmp(*this);
		++(*this);
		return tmp;
	};

	vec_iterator<iterator_type> &operator+=(difference_type n) {
		this->iter += n;
		return *this;
	};

	vec_iterator<iterator_type> operator-(difference_type n) { return iter - n; };
	vec_iterator<iterator_type> operator-(difference_type n) const { return iter - n; };

	difference_type operator-(vec_iterator<iterator_type> n) { return this->iter - n.iter; };
	difference_type operator-(vec_iterator<iterator_type> n) const { return this->iter - n.iter; };

	vec_iterator<iterator_type> &operator--() {
		--iter;
		return *this;
	};
	vec_iterator<iterator_type> operator--(int) {
		vec_iterator<iterator_type> tmp(*this);
		--(*this);
		return tmp;
	};

	vec_iterator<iterator_type> &operator-=(difference_type n) {
		this->iter -= n;
		return *this;
	};

	pointer operator->() const { return iter; };

	vec_iterator<iterator_type> &operator=(vec_iterator<iterator_type> const &other) {
		this->iter = other.iter;
		return *this;
	};

	reference operator[](difference_type n) { return iter[n]; };
	reference operator[](difference_type n) const { return iter[n]; };

	/*Non-member functions */

	friend bool operator==(const vec_iterator<V> &lhs, const vec_iterator<V> &rhs) { return lhs.iter == rhs.iter; };
	friend bool operator!=(const vec_iterator<V> &lhs, const vec_iterator<V> &rhs) { return lhs.iter != rhs.iter; };
	friend bool operator<(const vec_iterator<V> &lhs, const vec_iterator<V> &rhs) { return lhs.iter < rhs.iter; };
	friend bool operator<=(const vec_iterator<V> &lhs, const vec_iterator<V> &rhs) { return lhs.iter <= rhs.iter; };
	friend bool operator>(const vec_iterator<V> &lhs, const vec_iterator<V> &rhs) { return lhs.iter > rhs.iter; };
	friend bool operator>=(const vec_iterator<V> &lhs, const vec_iterator<V> &rhs) { return lhs.iter >= rhs.iter; };

	friend vec_iterator<iterator_type> operator+(typename vec_iterator<iterator_type>::difference_type n, const vec_iterator<iterator_type>& rev_it) { return rev_it + n; };
	friend vec_iterator<iterator_type> operator-(typename vec_iterator<iterator_type>::difference_type n, const vec_iterator<iterator_type>& rev_it) { return rev_it - n; };
};
}

#endif //FT_ITERATOR_HPP
