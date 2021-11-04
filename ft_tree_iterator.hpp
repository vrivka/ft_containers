#ifndef FT_TREE_ITERATOR_HPP
#define FT_TREE_ITERATOR_HPP

#include "ft_map.hpp"

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
	iterator_type *root;
	int64_t overflow;
public:
	/**	Constructors	**/

	tree_iterator() : iter(), root(), overflow(0) {};

	tree_iterator(const tree_iterator &other) : iter(other.iter), root(other.root), overflow(other.overflow) {};

	tree_iterator(iterator_type x, iterator_type *root) : iter(x), root(root), overflow(0) {};

	/**	Destructors	**/

	~tree_iterator() {};

	/**	Member functions	**/

	reference operator*() const throw() { return *(iter->val); };

	tree_iterator &operator++() {
		if (not overflow) {
			if (iter == (*root)->max(*root)) {
				iter++;
				overflow++;
				return *this;
			}
			iter = iter->increment(iter);
		} else if (overflow == -1) {
			overflow++;
			iter = (*root)->min(*root);
		} else {
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
			if (iter == (*root)->min(*root)) {
				iter--;
				overflow--;
				return *this;
			}
			iter = iter->decrement(iter);
		} else if (overflow == 1) {
			overflow--;
			iter = (*root)->max(*root);
		} else {
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
		this->root = other.root;
		this->overflow = other.overflow;
		return *this;
	};

	/*Non-member functions */

	friend bool operator==(const tree_iterator<V, VT> &lhs, const tree_iterator<V, VT> &rhs) {
		return lhs.iter == rhs.iter;
	};

	friend bool operator!=(const tree_iterator<V, VT> &lhs, const tree_iterator<V, VT> &rhs) {
		return lhs.iter != rhs.iter;
	};
};
}

#endif
