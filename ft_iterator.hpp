#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

#include <iterator>

namespace ft {
template<class V, class Category = std::random_access_iterator_tag>
class iterator : public std::iterator<Category, V> {
public:
	typedef V													iterator_type;		//	Iterator's type
	typedef typename std::iterator_traits<V>::iterator_category	iterator_category;	//	Preserves Iterator's category
	typedef typename std::iterator_traits<V>::value_type		value_type;			//	Preserves Iterator's value type
	typedef typename std::iterator_traits<V>::difference_type	difference_type;	//	Preserves Iterator's difference type
	typedef typename std::iterator_traits<V>::pointer			pointer;			//	Preserves Iterator's pointer type
	typedef typename std::iterator_traits<V>::reference			reference;			//	Preserves Iterator's reference type
private:
	iterator_type iter;
public:
	/* Constructors */

	iterator() : iter() {};
	iterator(iterator const &other) : iter(other.iter) {};
	iterator(iterator_type x) : iter(x) {};

	/* Destructors */

	~iterator() {};

	/* Member functions */

	iterator_type base() { return iter; };

	reference operator*() const throw() { return *iter; };

	iterator<iterator_type> operator+(difference_type n) { return iter + n; };
	iterator<iterator_type> operator+(difference_type n) const { return iter + n; };

	iterator<iterator_type> &operator++() {
		++iter;
		return *this;
	};
	iterator<iterator_type> operator++(int) {
		iterator<iterator_type> tmp(*this);
		++(*this);
		return tmp;
	};

	iterator<iterator_type> &operator+=(difference_type n) {
		this->iter += n;
		return *this;
	};
	iterator<iterator_type> &operator+=(difference_type n) const {
		this->iter += n;
		return *this;
	};

	iterator<iterator_type> operator-(difference_type n) { return iter - n; };
	iterator<iterator_type> operator-(difference_type n) const { return iter - n; };

	difference_type operator-(iterator<iterator_type> n) { return this->iter - n.iter; };
	difference_type operator-(iterator<iterator_type> n) const { return this->iter - n.iter; };

	iterator<iterator_type> &operator--() {
		--iter;
		return *this;
	};
	iterator<iterator_type> operator--(int) {
		iterator<iterator_type> tmp(*this);
		--(*this);
		return tmp;
	};

	iterator<iterator_type> &operator-=(difference_type n) {
		this->iter -= n;
		return *this;
	};
	iterator<iterator_type> &operator-=(difference_type n) const {
		this->iter -= n;
		return *this;
	};

	pointer operator->() const { return iter; };

	iterator<iterator_type> &operator=(iterator<iterator_type> const &other) {
		this->iter = other.iter;
		return *this;
	};
	iterator<iterator_type> &operator=(iterator<iterator_type> const &other) const {
		this->iter = other.iter;
		return *this;
	};

	reference operator[](difference_type n) { return iter[n]; };
	reference operator[](difference_type n) const { return iter[n]; };

	/*Non-member functions */

	friend bool operator==(const iterator<V> &lhs, const iterator<V> &rhs) { return lhs.iter == rhs.iter; };
	friend bool operator!=(const iterator<V> &lhs, const iterator<V> &rhs) { return lhs.iter != rhs.iter; };
	friend bool operator<(const iterator<V> &lhs, const iterator<V> &rhs) { return lhs.iter < rhs.iter; };
	friend bool operator<=(const iterator<V> &lhs, const iterator<V> &rhs) { return lhs.iter <= rhs.iter; };
	friend bool operator>(const iterator<V> &lhs, const iterator<V> &rhs) { return lhs.iter > rhs.iter; };
	friend bool operator>=(const iterator<V> &lhs, const iterator<V> &rhs) { return lhs.iter >= rhs.iter; };

	friend iterator<iterator_type> operator+(typename iterator<iterator_type>::difference_type n, const iterator<iterator_type>& rev_it) { return rev_it + n; };
	friend iterator<iterator_type> operator-(typename iterator<iterator_type>::difference_type n, const iterator<iterator_type>& rev_it) { return rev_it - n; };
};
}

#endif //FT_ITERATOR_HPP
