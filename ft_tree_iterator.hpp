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
	iterator_type	_iter;
	iterator_type	_head;
	int64_t			_overflow;
public:

	/**	Constructors	**/

	tree_iterator() : _iter(), _head(), _overflow(0) {};

	tree_iterator(const tree_iterator &other) : _iter(other._iter), _head(other._head), _overflow(other._overflow) {};

	tree_iterator(iterator_type x) : _iter(x), _head(x) {
		_overflow = x->parent ? 0 : 1;
		while (_head->parent)
			_head = _head->parent;
	};

	/**	Destructors	**/

	~tree_iterator() {};

	/**	Member functions	**/

	reference operator*() const { return *(_iter->value); };

	tree_iterator &operator++() {
		if (not _overflow) {
			_iter = _iter->increment(_iter);
			if (not _iter or _iter == _head) {
				_iter = _head;
				_overflow++;
			}
		}
		else if (_overflow == -1) {
			_overflow++;
			_iter = _head->min(_head);
		}
		else {
			_iter++;
			_overflow++;
		}
		return *this;
	};

	tree_iterator operator++(int) {
		tree_iterator tmp(*this);
		++(*this);
		return tmp;
	};

	tree_iterator &operator--() {
		if (not _overflow) {
			_iter = _iter->decrement(_iter);
			if (not _iter or _iter == _head) {
				_overflow--;
				_iter = _head;
			}
		}
		else if (_overflow == 1) {
			_overflow--;
			_iter = _head->max(_head);
		}
		else {
			_iter--;
			_overflow--;
		}
		return *this;
	};

	tree_iterator operator--(int) {
		tree_iterator tmp(*this);
		--(*this);
		return tmp;
	};

	pointer operator->() const { return _iter->value; };

	tree_iterator &operator=(const tree_iterator &other) {
		if (this == &other)
			return *this;
		this->_iter = other._iter;
		this->_head = other._head;
		this->_overflow = other._overflow;
		return *this;
	};

	/**	Non-member functions	**/

	friend bool operator==(const tree_iterator<V, VT> &lhs, const tree_iterator<V, VT> &rhs) { return lhs._iter == rhs._iter; };

	friend bool operator!=(const tree_iterator<V, VT> &lhs, const tree_iterator<V, VT> &rhs) { return lhs._iter != rhs._iter; };
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

	reference operator*() const { return *iter; };

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

	/**	Non-member functions	**/

	friend bool operator==(const tree_const_iterator<I, VT> &lhs, const tree_const_iterator<I, VT> &rhs) { return lhs.iter == rhs.iter; };

	friend bool operator!=(const tree_const_iterator<I, VT> &lhs, const tree_const_iterator<I, VT> &rhs) { return lhs.iter != rhs.iter; };
};

}

#endif
