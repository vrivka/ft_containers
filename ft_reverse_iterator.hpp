#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
template<class Iterator>
class reverse_vec_iterator {
public:
	typedef Iterator iterator_type;//	Iterator's type
	typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;//	Preserves Iterator's category
	typedef typename ft::iterator_traits<Iterator>::value_type value_type;//	Preserves Iterator's value type
	typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;//	Preserves Iterator's difference type
	typedef typename ft::iterator_traits<Iterator>::pointer pointer;//	Preserves Iterator's pointer type
	typedef typename ft::iterator_traits<Iterator>::reference reference;//	Preserves Iterator's reference type
private:
	iterator_type iter;
	reverse_vec_iterator(iterator_type x) : iter(x) {};
public:
	reverse_vec_iterator() : iter() {};
	reverse_vec_iterator(reverse_vec_iterator const &other) : iter(other.iter) {};
	~reverse_vec_iterator() {};

	/* Member functions */

	iterator_type base() { return iter; };

	reference operator*() const { return *iter; };

	reverse_vec_iterator<iterator_type> operator+(difference_type n) { return iter - n; };
	reverse_vec_iterator<iterator_type> operator+(difference_type n) const { return iter - n; };

	reverse_vec_iterator<iterator_type> &operator++() {
		--iter;
		return *this;
	};
	reverse_vec_iterator<iterator_type> operator++(int) {
		reverse_vec_iterator<iterator_type> tmp(*this);
		++(*this);
		return tmp;
	};

	reverse_vec_iterator<iterator_type> &operator+=(difference_type n) {
		this->iter -= n;
		return *this;
	};

	reverse_vec_iterator<iterator_type> operator-(difference_type n) { return this->iter + n; };
	reverse_vec_iterator<iterator_type> operator-(difference_type n) const { return this->iter + n; };

	difference_type operator-(reverse_vec_iterator<iterator_type> n) { return this->iter - n.iter; };
	difference_type operator-(reverse_vec_iterator<iterator_type> n) const { return this->iter - n.iter; };

	reverse_vec_iterator<iterator_type> &operator--() {
		++iter;
		return *this;
	};
	reverse_vec_iterator<iterator_type> operator--(int) {
		reverse_vec_iterator<iterator_type> tmp(*this);
		--(*this);
		return tmp;
	};

	reverse_vec_iterator<iterator_type> &operator-=(difference_type n) {
		this->iter += n;
		return *this;
	};

	pointer operator->() const { return iter; };

	reverse_vec_iterator<iterator_type> &operator=(reverse_vec_iterator<iterator_type> const &other) {
		this->iter = other.iter;
		return *this;
	};

	reference operator[](difference_type n) { return iter[n]; };
	reference operator[](difference_type n) const { return iter[n]; };

	/* Non-member functions */

	friend bool operator==(const reverse_vec_iterator<iterator_type> &lhs, const reverse_vec_iterator<iterator_type> &rhs) { return lhs.iter == rhs.iter; };
	friend bool operator!=(const reverse_vec_iterator<iterator_type> &lhs, const reverse_vec_iterator<iterator_type> &rhs) { return lhs.iter != rhs.iter; };
	friend bool operator<(const reverse_vec_iterator<iterator_type> &lhs, const reverse_vec_iterator<iterator_type> &rhs) { return lhs.iter > rhs.iter; };
	friend bool operator<=(const reverse_vec_iterator<iterator_type> &lhs, const reverse_vec_iterator<iterator_type> &rhs) { return lhs.iter >= rhs.iter; };
	friend bool operator>(const reverse_vec_iterator<iterator_type> &lhs, const reverse_vec_iterator<iterator_type> &rhs) { return lhs.iter < rhs.iter; };
	friend bool operator>=(const reverse_vec_iterator<iterator_type> &lhs, const reverse_vec_iterator<iterator_type> &rhs) { return lhs.iter <= rhs.iter; };

	friend reverse_vec_iterator<iterator_type> operator+(reverse_vec_iterator<iterator_type>::difference_type n, const reverse_vec_iterator<iterator_type>& rev_it) { return rev_it + n; };
	friend reverse_vec_iterator<iterator_type> operator-(reverse_vec_iterator<iterator_type>::difference_type n, const reverse_vec_iterator<iterator_type>& rev_it) { return rev_it - n; };
};
}

#endif //FT_REVERSE_ITERATOR_HPP
