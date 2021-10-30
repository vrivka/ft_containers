#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "RBNode.hpp"
#include "ft_tree_iterator.hpp"

template<class T, class Compare, class Alloc>
class RBTree {
public:
	typedef Alloc allocator_type;
	typedef Compare key_compare;
	typedef typename allocator_type::template rebind<RBNode<T, allocator_type> >::other node_allocator_type;
	typedef typename node_allocator_type::value_type node_type;
	typedef typename node_allocator_type::pointer node_pointer;
	typedef typename node_allocator_type::const_pointer const_node_pointer;
	typedef T value_type;
	typedef typename value_type::first_type Key;
	typedef typename value_type::second_type V;
	typedef ft::tree_iterator<node_pointer, value_type>							iterator;				//	a bidirectional iterator to value_type convertible to const_iterator
	typedef ft::tree_iterator<const_node_pointer, value_type>					const_iterator;			//	a bidirectional iterator to const value_type
	typedef ft::reverse_iterator<iterator>						reverse_iterator;						//	reverse_iterator<iterator>
	typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;					//	reverse_iterator<const_iterator>
private:
	allocator_type *A;
	node_allocator_type An;
	key_compare *comp;
	node_pointer root;
public:
	iterator				begin() { return iterator(root->min(root), root->min(root), root->max(root)); }
	const_iterator			begin() const { return iterator(root->min(root), root->min(root), root->max(root)); }
	iterator				end() { return ++iterator(root->max(root), root->min(root), root->max(root)); }
	const_iterator			end() const { return ++iterator(root->max(root), root->min(root), root->max(root)); }

	reverse_iterator		rbegin() { return --end(); }
	const_reverse_iterator	rbegin() const { return --end(); }
	reverse_iterator		rend() { return --begin(); }
	const_reverse_iterator	rend() const { return --begin(); }

	node_pointer getroot() { return root; }

	void print() const { root->print(root); }

	node_pointer search(Key v) const {
		node_pointer node = root;
		while (node) {
			if (v == node->val->first)
				return node;
			else if ((*comp)(v, node->val->first))
				node = node->left;
			else
				node = node->right;
		}
		return NULL;
	}

	node_pointer create_node(node_pointer node, node_pointer parent, const value_type &v) {
		node = An.allocate(1);
		An.construct(node);
		node->A = A;
		node->An = &An;
		node->parent = parent;
		node->val = A->allocate(1);
		A->construct(node->val, v);
		return node;
	}

	node_pointer insert(value_type v) {
		node_pointer node = root;
		if (node) {
			while (node) {
				if ((*comp)(v.first, node->val->first)) {
					if (node->left)
						node = node->left;
					else {
						node->left = create_node(node->left, node, v);
						node_type::balance(node->left);
					}
				} else if (v.first != node->val->first) {
					if (node->right)
						node = node->right;
					else {
						node->right = create_node(node->right, node, v);
						node_type::balance(node->right);
					}
				} else break ;
			}
		}
		else {
			root = create_node(root, NULL, v);
			node_type::balance(root);
		}
		while (root->parent)
			root = root->parent;
		return node;
	}

	RBTree(allocator_type *alloc = NULL, key_compare *compare = NULL, const node_allocator_type &node_allocator = node_allocator_type())
	: A(alloc), An(node_allocator), comp(compare), root(NULL) {}

//	RBTree(const RBTree &other) {
//		if (other.root)
//			this->root = new node_type(*other.root);
//		else
//			this->root = NULL;
//	}

	~RBTree() {
		if (root) {
			An.destroy(root);
			An.deallocate(root, 1);
		}
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


#endif //RBTREE_HPP
