#ifndef RBT_HPP
#define RBT_HPP

#include "RBNode.hpp"

template<class Key, class T, class Compare, class Alloc>
class RBT {
public:
	typedef Alloc allocator_type;
	typedef Compare key_compare;
	typedef typename allocator_type::template rebind<RBNode<Key, T, key_compare, allocator_type> >::other node_allocator_type;
	typedef typename node_allocator_type::pointer node_pointer;
	typedef ft::pair<Key,T> value_type;

	allocator_type *A;
	node_allocator_type An;
	key_compare *comp;
	node_pointer root;


	node_pointer getroot() { return root; }

	void print() const { root->print(root); }

	node_pointer search(T v) const { return root->find(root, v); }

	void insert(const value_type &v) {
		if (root)
			root->add(root, v);
		else {
			root = An.allocate(1);
			An.construct(root);
			root->A = A;
			root->An = &An;
			root->comp = comp;
			root->val = A->allocate(1);
			A->construct(root->val, v);
			root->balance(root);
		}
		while (root->parent)
			root = root->parent;
	}

	RBT(allocator_type *alloc = NULL, key_compare *compare = NULL, const node_allocator_type &node_allocator = node_allocator_type())
	: A(alloc), An(node_allocator), comp(compare), root(NULL) {}

//	RBT(const RBT &other) {
//		if (other.root)
//			this->root = new node_type(*other.root);
//		else
//			this->root = NULL;
//	}

	~RBT() {
		An.destroy(root);
		An.deallocate(root, 1);
	}

//	RBT &operator=(const RBT &other) {
//		if (this == &other)
//			return *this;
//		delete this->root;
//		this->root = NULL;
//		if (other.root)
//			this->root = new node_type(*other.root);
//		return *this;
//	}
};


#endif //RBT_HPP
