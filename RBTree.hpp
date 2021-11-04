#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "RBNode.hpp"
#include "ft_tree_iterator.hpp"

namespace ft {
template<class T, class Compare, class Alloc>
class RBTree {
public:
	typedef T															value_type;				//	Store value type
	typedef Alloc														allocator_type;			//	Allocator type for value type
	typedef Compare														value_comp;				//	Nested function class to compare elements
	typedef RBNode<value_type, allocator_type>							node;					//	Node type
	typedef typename allocator_type::template rebind<node>::other		node_allocator_type;	//	Allocator type for node
	typedef typename node_allocator_type::pointer						node_pointer;			//	Node pointer
	typedef typename node_allocator_type::const_pointer					const_node_pointer;		//	Constant node pointer
	typedef tree_iterator<node_pointer, value_type> const				const_iterator;			//	A bidirectional iterator to const value_type
	typedef tree_iterator<node_pointer, value_type>						iterator;				//	A bidirectional iterator to value_type convertible to const_iterator
	typedef reverse_iterator<const_iterator>							const_reverse_iterator;	//	Constant reverse iterator
	typedef reverse_iterator<iterator>									reverse_iterator;		//	Reverse iterator
	value_comp			*comp;
private:
	allocator_type		A;
	node_allocator_type	An;
	node_pointer		root;
public:

	ft::pair<iterator, bool> insert(value_type *v) {
		node_pointer node = root;
		bool b = false;
		if (node) {
			while (node) {
				if ((*comp)(*v, *node->val)) {
					if (node->left)
						node = node->left;
					else {
						node->left = create_node(node->left, node, v);
						node::balance(node->left);
						b = true;
						break ;
					}
				} else if ((*comp)(*node->val, *v)) {
					if (node->right)
						node = node->right;
					else {
						node->right = create_node(node->right, node, v);
						node::balance(node->right);
						b = true;
						break ;
					}
				} else break;
			}
		} else {
			root = create_node(root, NULL, v);
			node::balance(root);
			b = true;
			return ft::make_pair(iterator(root, &root), b);
		}
		while (root->parent)
			root = root->parent;
		return ft::make_pair(iterator(node, &root), b);
	}

	RBTree() : comp(NULL), A(), An(), root(NULL) {}

	RBTree(const RBTree &other) : comp(/***/), A(), An(), root(NULL) {
		if (other.root) {
			this->root = An.allocate(1);
			An.construct(this->root, *other.root);
		}
	}

	~RBTree() {
		if (root) {
			An.destroy(root);
			An.deallocate(root, 1);
		}
	}

	RBTree &operator=(const RBTree &other) {
		if (this == &other)
			return *this;
		if (this->root) {
			An.destroy(this->root);
			An.deallocate(this->root, 1);
		}
		this->root = NULL;
		if (other.root) {
			this->root = An.allocate(1);
			An.construct(this->root, *other.root);
		}
		return *this;
	}
};

}

#endif //RBTREE_HPP
