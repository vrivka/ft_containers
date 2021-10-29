#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "ft_pair.hpp"

enum { RED, BLACK };

template<class Key, class T, class Compare, class Alloc>
class RBNode {
public:
	typedef ft::pair<Key,T> value_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;
	typedef typename allocator_type::template rebind<RBNode>::other node_allocator_type;

	allocator_type *A;
	node_allocator_type *An;
	key_compare *comp;
	value_type *val;
	int16_t color;
	RBNode *parent;
	RBNode *left;
	RBNode *right;

	RBNode *min(RBNode *node) {
		if (not node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

	RBNode *max(RBNode *node) {
		if (not node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

//	RBNode *

	void print(RBNode *node) {
		if (not node)
			return ;
		RBNode::print(node->left);
		std::cout << "value: " << node->val->second << " color: " << (node->color ? "BLACK " : "RED   ")
		<< "address: " << std::setw(14) << node << " parent: " << std::setw(14) << node->parent
		<< "\tleft: " << std::setw(14) << node->left << "\tright: " << std::setw(14) << node->right << std::endl;
		RBNode::print(node->right);
	}

	RBNode *find(RBNode *node, value_type &v) {
		while (node) {
			if (v.first == *node->val->first)
				return node;
			else if (comp(v.first, node->val->first))
				node = node->left;
			else
				node = node->right;
		}
		return NULL;
	}


	RBNode *grandparent(RBNode *node)  {
		if (node and node->parent)
			return node->parent->parent;
		else
			return NULL;
	}

	RBNode *uncle(RBNode *node) {
		RBNode *grandparent_ = grandparent(node);

		if (not grandparent_)
			return NULL;
		else if (grandparent_->left == node->parent)
			return grandparent_->right;
		else
			return grandparent_->left;
	}

	void rotate_left(RBNode *node) {
		if (not node) return ;
		RBNode *pivot = node->right;

		if (not pivot) return ;
		pivot->parent = node->parent;
		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left = pivot;
			else
				node->parent->right = pivot;
		}
		node->right = pivot->left;
		if (pivot->left)
			pivot->left->parent = node;
		node->parent = pivot;
		pivot->left = node;
	}

	void rotate_right(RBNode *node) {
		if (not node) return ;
		RBNode *pivot = node->left;

		if (not pivot) return ;
		pivot->parent = node->parent;
		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left = pivot;
			else
				node->parent->right = pivot;
		}
		node->left = pivot->right;
		if (pivot->right)
			pivot->right->parent = node;
		node->parent = pivot;
		pivot->right = node;
	}

	void add(RBNode *node, const value_type &v) {
		while (node) {
			if ((*comp)(v.first, node->val->first) && v.first != node->val->first) {
				if (node->left)
					node = node->left;
				else {
					node->left = An->allocate(1);
					An->construct(node->left);
					node->left->A = A;
					node->left->An = An;
					node->left->comp = comp;
					node->left->parent = node;
					node = node->left;
					node->val = A->allocate(1);
					A->construct(node->val, v);
					balance(node);
					return ;
				}
			}
			else if (!(*comp)(v.first, node->val->first) && v.first != node->val->first) {
				if (node->right)
					node = node->right;
				else {
					node->right = An->allocate(1);
					An->construct(node->right);
					node->right->A = A;
					node->right->An = An;
					node->right->comp = comp;
					node->right->parent = node;
					node = node->right;
					node->val = A->allocate(1);
					A->construct(node->val, v);
					balance(node);
					return ;
				}
			}
			else return ;
		}
	}

	void balance(RBNode *node) {
		RBNode *uncle_, *grandparent_;

		if (not node->parent)
			node->color = BLACK;
		else if (node->parent->color == BLACK)
			return;
		else if ((uncle_ = uncle(node)) && uncle_->color == RED) {
			node->parent->color = BLACK;
			uncle_->color = BLACK;
			grandparent_ = grandparent(node);
			grandparent_->color = RED;
			balance(grandparent_);
		}
		else {
			grandparent_ = grandparent(node);
			if (node == node->parent->right and node->parent == grandparent_->left) {
				rotate_left(node->parent);
				node = node->left;
			}
			else if (node == node->parent->left and node->parent == grandparent_->right) {
				rotate_right(node->parent);
				node = node->right;
			}
			grandparent_ = grandparent(node);
			node->parent->color = BLACK;
			grandparent_->color = RED;
			if (node == node->parent->left and node->parent == grandparent_->left)
				rotate_right(grandparent_);
			else
				rotate_left(grandparent_);
		}
	}


//	static void erase(RBNode *node) {
//
//	}


	RBNode(allocator_type *alloc = NULL, node_allocator_type *node_alloc = NULL, key_compare *compare = NULL)
	: A(alloc), An(node_alloc), comp(compare), val(NULL), color(RED), parent(NULL), left(NULL), right(NULL) {}

	RBNode(const RBNode &other)
	: A(other.A), An(other.An), comp(other.comp), color(other.color), parent(NULL), left(NULL), right(NULL) {
		this->val = A->allocate(1);
		A->construct(this->val, *other.val);
		if (other.left) {
			this->left = An->allocate(1);
			An->construct(this->left, *other.left);
			this->left->parent = this;
		}
		if (other.right) {
			this->right = An->allocate(1);
			An->construct(this->right, *other.left);
			this->right->parent = this;
		}
	}

	~RBNode() {
		if (right) {
			An->destroy(right);
			An->deallocate(right, 1);
		}
		A->destroy(val);
		A->deallocate(val, 1);
		if (left) {
			An->destroy(left);
			An->deallocate(left, 1);
		}
	}

	RBNode *increment(RBNode *node) {
		if (not node)
			return NULL;
		if (node->right)
			return min(node->right);
		else if (node->parent) {
			if (node->parent->left == node)
				return node->parent;
			else if (node->parent->right == node) {
				while (node->parent and node->parent->right == node)
					node = node->parent;
				return node->parent;
			}
		}
		return node;
	}

	RBNode *decrement(RBNode *node) {
		if (not node)
			return NULL;
		if (node->left)
			return max(node->left);
		else if (node->parent) {
			if (node->parent->right == node)
				return node->parent;
			else if (node->parent->left == node) {
				while (node->parent and node->parent->left == node)
					node = node->parent;
				return node->parent;
			}
		}
		return node;
	}

	RBNode &operator=( const RBNode &other ) {
		if (this == &other)
			return *this;
		this->val = other.val;
		this->color = other.color;
		this->parent = NULL;
		delete this->left;
		this->left = NULL;
		delete this->right;
		this->right = NULL;
		if (other.left)
			this->left = new RBNode(*other.left);
		if (other.right)
			this->right = new RBNode(*other.right);
		return *this;
	}
};

#endif
