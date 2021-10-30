#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "ft_pair.hpp"

enum { RED, BLACK };

template<class T, class Alloc>
class RBNode {
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::template rebind<RBNode>::other node_allocator_type;
	typedef typename node_allocator_type::pointer pointer;
	typedef typename node_allocator_type::reference reference;

	allocator_type *A;
	node_allocator_type *An;
	value_type *val;
	int16_t color;
	pointer parent;
	pointer left;
	pointer right;

	pointer min(pointer node) {
		if (not node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

	pointer max(pointer node) {
		if (not node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	void print(pointer node) {
		if (not node)
			return ;
		RBNode::print(node->left);
		std::cout << "value: " << node->val->second << " color: " << (node->color ? "BLACK " : "RED   ")
		<< "address: " << std::setw(14) << node << " parent: " << std::setw(14) << node->parent
		<< "\tleft: " << std::setw(14) << node->left << "\tright: " << std::setw(14) << node->right << std::endl;
		RBNode::print(node->right);
	}

	static pointer grandparent(pointer node)  {
		if (node and node->parent)
			return node->parent->parent;
		else
			return NULL;
	}

	static pointer uncle(pointer node) {
		pointer grandparent_ = grandparent(node);

		if (not grandparent_)
			return NULL;
		else if (grandparent_->left == node->parent)
			return grandparent_->right;
		else
			return grandparent_->left;
	}

	static void rotate_left(pointer node) {
		if (not node) return ;
		pointer pivot = node->right;

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

	static void rotate_right(pointer node) {
		if (not node) return ;
		pointer pivot = node->left;

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

	static void balance(pointer node) {
		pointer uncle_, grandparent_;

		if (not node->parent)
			node->color = BLACK;
		else if (node->parent->color == BLACK)
			return;
		else if ((uncle_ = uncle(node)) and uncle_->color == RED) {
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


	RBNode()
	: A(NULL), An(NULL), val(NULL), color(RED), parent(NULL), left(NULL), right(NULL) {}

	RBNode(const RBNode &other)
	: A(other.A), An(other.An), color(other.color), parent(NULL), left(NULL), right(NULL) {
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

	pointer increment(pointer node) {
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

	pointer decrement(pointer node) {
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

	reference operator=(const reference other) {
		if (this == &other)
			return *this;
		this->val = other.val;
		this->color = other.color;
		this->parent = NULL;
		if (this->left) {
			An->destroy(this->left);
			An->deallocate(this->left, 1);
			this->left = NULL;
		}
		if (this->right) {
			An->destroy(this->right);
			An->deallocate(this->right, 1);
			this->right = NULL;
		}
		if (other.left) {
			this->left = An->allocate(1);
			An->construct(this->left, *other.left);
		}
		if (other.right) {
			this->right = An->allocate(1);
			An->construct(this->right, *other.right);
		}
		return *this;
	}
};

#endif
