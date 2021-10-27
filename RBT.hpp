#ifndef RBT_HPP
#define RBT_HPP

#include "RBNode.hpp"

template<class T, class Compare, class Alloc>
class RBT {
public:
	typedef typename RBNode<T, Compare, Alloc>::value_type value_type;
	typedef Alloc allocator_type;
	typedef Compare key_compare;
private:
	RBNode<value_type, key_compare, allocator_type> *root;
public:

	RBNode<value_type, key_compare, allocator_type> *getroot() { return root; }

	void print() const { RBNode<value_type, key_compare, allocator_type>::print(root); }

	RBNode<value_type, key_compare, allocator_type> *search(T v) const { return RBNode<value_type, key_compare, allocator_type>::find(root, v); }

	void insert(T v) {
		if (root)
			RBNode<value_type, key_compare, allocator_type>::add(root, v);
		else {
			root = new RBNode<value_type, key_compare, allocator_type>(v);
			RBNode<value_type, key_compare, allocator_type>::balance(root);
		}
		if (not RBNode<value_type, key_compare, allocator_type>::is_root(root))
			root = RBNode<value_type, key_compare, allocator_type>::getroot(root);
	}

	RBT() : root(NULL) {}

	RBT(const RBT &other) {
		if (other.root)
			this->root = new RBNode<value_type, key_compare, allocator_type>(*other.root);
		else
			this->root = NULL;
	}

	explicit RBT(T v) : root(new RBNode<value_type, key_compare, allocator_type>(v)) { RBNode<value_type, key_compare, allocator_type>::balance(root); }

	~RBT(){ delete root; }

	RBT &operator=(const RBT &other) {
		if (this == &other)
			return *this;
		delete this->root;
		this->root = NULL;
		if (other.root)
			this->root = new RBNode<value_type, key_compare, allocator_type>(*other.root);
		return *this;
	}
};


#endif //RBT_HPP
