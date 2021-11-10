#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

#include "ft_utilities.hpp"

namespace ft {
template<class Iterator>
class reverse_iterator {
public:
	typedef Iterator 													iterator_type;		//	Iterator's type
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;	//	Preserves Iterator's category
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;			//	Preserves Iterator's value type
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;	//	Preserves Iterator's difference type
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;			//	Preserves Iterator's pointer type
	typedef typename ft::iterator_traits<Iterator>::reference			reference;			//	Preserves Iterator's reference type
private:
	iterator_type _iterator;
public:
	reverse_iterator() : _iterator() {};

	reverse_iterator(const reverse_iterator &other) : _iterator(other._iterator) {};

	reverse_iterator(iterator_type param) : _iterator(param) {};

	~reverse_iterator() {};

	/* Member functions */

	iterator_type base() { return _iterator; };

	reference operator*() const { return *_iterator; };

	reverse_iterator operator+(difference_type num) { return _iterator - num; };
	reverse_iterator operator+(difference_type num) const { return _iterator - num; };

	reverse_iterator &operator++() {
		--_iterator;
		return *this;
	};
	reverse_iterator operator++(int) {
		reverse_iterator tmp(*this);
		++(*this);
		return tmp;
	};

	reverse_iterator &operator+=(difference_type num) {
		_iterator -= num;
		return *this;
	};

	reverse_iterator operator-(difference_type num) { return _iterator + num; };
	reverse_iterator operator-(difference_type num) const { return _iterator + num; };

	difference_type operator-(reverse_iterator other) { return _iterator - other._iterator; };
	difference_type operator-(reverse_iterator other) const { return _iterator - other._iterator; };

	reverse_iterator &operator--() {
		++_iterator;
		return *this;
	};
	reverse_iterator operator--(int) {
		reverse_iterator tmp(*this);
		--(*this);
		return tmp;
	};

	reverse_iterator &operator-=(difference_type num) {
		_iterator += num;
		return *this;
	};

	pointer operator->() const { return &(*_iterator); };

	reverse_iterator &operator=(const reverse_iterator &other) {
		_iterator = other._iterator;
		return *this;
	};

	reference operator[](difference_type num) { return _iterator[num]; };
	reference operator[](difference_type num) const { return _iterator[num]; };

	/* Non-member functions */

	friend bool operator==(const reverse_iterator &left, const reverse_iterator &right)	{ return left._iterator == right._iterator; };
	friend bool operator!=(const reverse_iterator &left, const reverse_iterator &right)	{ return left._iterator != right._iterator; };
	friend bool operator<(const reverse_iterator &left, const reverse_iterator &right)	{ return left._iterator > right._iterator; };
	friend bool operator<=(const reverse_iterator &left, const reverse_iterator &right)	{ return left._iterator >= right._iterator; };
	friend bool operator>(const reverse_iterator &left, const reverse_iterator &right)	{ return left._iterator < right._iterator; };
	friend bool operator>=(const reverse_iterator &left, const reverse_iterator &right)	{ return left._iterator <= right._iterator; };

	friend reverse_iterator operator+(reverse_iterator::difference_type num, const reverse_iterator &rev_it) { return rev_it + num; };
	friend reverse_iterator operator-(reverse_iterator::difference_type num, const reverse_iterator &rev_it) { return rev_it - num; };
};
}

#endif
