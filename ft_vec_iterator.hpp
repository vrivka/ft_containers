#ifndef FT_VEC_ITERATOR_HPP
#define FT_VEC_ITERATOR_HPP

#include "ft_utilities.hpp"

namespace ft {
template<class IteratorType>
class vec_iterator {
public:
	typedef IteratorType												iterator_type;		//	Iterator's type
	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;	//	Preserves Iterator's category
	typedef typename iterator_traits<iterator_type>::value_type			value_type;			//	Preserves Iterator's value type
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;	//	Preserves Iterator's difference type
	typedef typename iterator_traits<iterator_type>::pointer			pointer;		//	Preserves Iterator's pointer type
	typedef typename iterator_traits<iterator_type>::reference			reference;			//	Preserves Iterator's reference type
private:
	iterator_type _pointer;
public:
	/** Constructors **/

	vec_iterator() : _pointer() {}

	template<class U>
	vec_iterator(const vec_iterator<U> &other) : _pointer(other.base()) {}

	vec_iterator(const vec_iterator &other) : _pointer(other._pointer) {}

	vec_iterator(iterator_type param) : _pointer(param) {}

	/** Destructors **/

	~vec_iterator() {}

	/** Member functions **/

	pointer base() const { return _pointer; }

	reference operator*() const throw() { return *_pointer; }

	vec_iterator operator+(difference_type num) { return _pointer + num; }
	vec_iterator operator+(difference_type num) const { return _pointer + num; }

	vec_iterator &operator++() {
		++_pointer;
		return *this;
	}
	vec_iterator operator++(int) {
		vec_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	vec_iterator &operator+=(difference_type num) {
		_pointer += num;
		return *this;
	}

	vec_iterator operator-(difference_type num) { return _pointer - num; }
	vec_iterator operator-(difference_type num) const { return _pointer - num; }

	difference_type operator-(vec_iterator other) { return _pointer - other._pointer; }
	difference_type operator-(vec_iterator other) const { return _pointer - other._pointer; }

	vec_iterator &operator--() {
		--_pointer;
		return *this;
	}
	vec_iterator operator--(int) {
		vec_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	vec_iterator &operator-=(difference_type num) {
		_pointer -= num;
		return *this;
	};

	pointer operator->() const { return _pointer; }

	vec_iterator &operator=(vec_iterator const &other) {
		_pointer = other._pointer;
		return *this;
	}

	reference operator[](difference_type num) { return _pointer[num]; }
	reference operator[](difference_type num) const { return _pointer[num]; }

	/*Non-member functions */

	friend bool operator==(const vec_iterator &left, const vec_iterator &right)	{ return left._pointer == right._pointer; }
	friend bool operator!=(const vec_iterator &left, const vec_iterator &right)	{ return left._pointer != right._pointer; }
	friend bool operator<(const vec_iterator &left, const vec_iterator &right)	{ return left._pointer < right._pointer; }
	friend bool operator<=(const vec_iterator &left, const vec_iterator &right)	{ return left._pointer <= right._pointer; }
	friend bool operator>(const vec_iterator &left, const vec_iterator &right)	{ return left._pointer > right._pointer; }
	friend bool operator>=(const vec_iterator &left, const vec_iterator &right)	{ return left._pointer >= right._pointer; }

	friend vec_iterator operator+(difference_type num, const vec_iterator &iter) { return iter + num; };
	friend vec_iterator operator-(difference_type num, const vec_iterator &iter) { return iter - num; };
};
}

#endif
