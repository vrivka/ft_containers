#ifndef FT_TREE_ITERATOR_HPP
#define FT_TREE_ITERATOR_HPP

namespace ft {
template<class V, class VT>
class tree_iterator {
public:
	typedef V								iterator_type;		//	Iterator's type
	typedef VT								value_type;			//	Preserves Iterator's value type
	typedef ptrdiff_t						difference_type;	//	Preserves Iterator's difference type
	typedef value_type*						pointer;			//	Preserves Iterator's pointer type
	typedef value_type&						reference;			//	Preserves Iterator's reference type
	typedef std::bidirectional_iterator_tag	iterator_category;	//	Preserves Iterator's category
private:
	iterator_type iter;
	iterator_type head;
	int64_t overflow;
public:
	/**	Constructors	**/

	tree_iterator() : iter(), head(), overflow(0) {};

	tree_iterator(const tree_iterator &other) : iter(other.iter), head(other.head), overflow(other.overflow) {};

	tree_iterator(iterator_type x) : iter(x), overflow(0) {
		head = x;
		while (head->parent)
			head = head->parent;
	};

	/**	Destructors	**/

	~tree_iterator() {};

	/**	Member functions	**/

	reference operator*() const throw() { return *(iter->val); };

	tree_iterator &operator++() {
		if (not overflow) {
			if (iter == head) {
				iter++;
				overflow++;
				return *this;
			}
			iter = iter->increment(iter);
		}
		else if (overflow == -1) {
			overflow++;
			iter = head->min(head);
		}
		else {
			iter++;
			overflow++;
		}
		return *this;
	};

	tree_iterator operator++(int) {
		tree_iterator tmp(*this);
		++(*this);
		return tmp;
	};

	tree_iterator &operator--() {
		if (not overflow) {
			if (iter == head) {
				iter--;
				overflow--;
				return *this;
			}
			iter = iter->decrement(iter);
		}
		else if (overflow == 1) {
			overflow--;
			iter = head->max(head);
		}
		else {
			iter--;
			overflow--;
		}
		return *this;
	};

	tree_iterator operator--(int) {
		tree_iterator tmp(*this);
		--(*this);
		return tmp;
	};

	pointer operator->() const { return iter->val; };

	tree_iterator &operator=(const tree_iterator &other) {
		if (this == &other)
			return *this;
		this->iter = other.iter;
		this->head = other.head;
		this->overflow = other.overflow;
		return *this;
	};

	/*Non-member functions */

	friend bool operator==(const tree_iterator<V, VT> &lhs, const tree_iterator<V, VT> &rhs) { return lhs.iter == rhs.iter; };

	friend bool operator!=(const tree_iterator<V, VT> &lhs, const tree_iterator<V, VT> &rhs) { return lhs.iter != rhs.iter; };
};

template<class I, class VT>
class tree_const_iterator {
public:
	typedef I								iterator_type;		//	Iterator's type
	typedef VT								value_type;			//	Preserves Iterator's value type
	typedef ptrdiff_t						difference_type;	//	Preserves Iterator's difference type
	typedef value_type*						pointer;			//	Preserves Iterator's pointer type
	typedef value_type &					reference;			//	Preserves Iterator's reference type
	typedef std::bidirectional_iterator_tag	iterator_category;	//	Preserves Iterator's category
private:
	iterator_type iter;
public:
	/**	Constructors	**/

	tree_const_iterator() : iter() {};

	tree_const_iterator(const tree_const_iterator &other) : iter(other.iter) {};

	tree_const_iterator(iterator_type x) : iter(x) {};

	/**	Destructors	**/

	~tree_const_iterator() {};

	/**	Member functions	**/

	reference operator*() const throw() { return *iter; };

	tree_const_iterator &operator++() {
		++iter;
		return *this;
	};

	tree_const_iterator operator++(int) {
		tree_const_iterator tmp(*this);
		++(*this);
		return tmp;
	};

	tree_const_iterator &operator--() {
		--iter;
		return *this;
	};

	tree_const_iterator operator--(int) {
		tree_const_iterator tmp(*this);
		--(*this);
		return tmp;
	};

	pointer operator->() const { return &(*iter); };

	tree_const_iterator &operator=(const tree_const_iterator &other) {
		if (this == &other)
			return *this;
		this->iter = other.iter;
		return *this;
	};

	/*Non-member functions */

	friend bool operator==(const tree_const_iterator<I, VT> &lhs, const tree_const_iterator<I, VT> &rhs) { return lhs.iter == rhs.iter; };

	friend bool operator!=(const tree_const_iterator<I, VT> &lhs, const tree_const_iterator<I, VT> &rhs) { return lhs.iter != rhs.iter; };
};

}

#endif
