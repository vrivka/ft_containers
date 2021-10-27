#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <cstdlib>
#include <iomanip>
#include <iostream>

enum { RED, BLACK };

template<class T, class Compare = std::less<T> >
class RBNode {
public:
	typedef T value_type;
	typedef Compare key_compare;

	static std::allocator<RBNode<T> > A = std::allocator<RBNode<T> >();
	value_type val;
	int16_t color;
	RBNode *parent;
	RBNode *left;
	RBNode *right;

	static RBNode *min(RBNode *node) {
		if (not node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

	static RBNode *max(RBNode *node) {
		if (not node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	static void print(RBNode *node) {
		if (not node)
			return ;
		RBNode::print(node->left);
		std::cout << "value: " << node->val << " color: " << (node->color ? "BLACK " : "RED   ")
		<< "address: " << std::setw(14) << node << " parent: " << std::setw(14) << node->parent
		<< "\tleft: " << std::setw(14) << node->left << "\tright: " << std::setw(14) << node->right << std::endl;
		RBNode::print(node->right);
	}

	static RBNode *find(RBNode *node, value_type v, key_compare &comp = key_compare()) {
		while (node) {
			if (v == node->val)
				return node;
			else if (comp(v, node->val))
				node = node->left;
			else
				node = node->right;
		}
		return NULL;
	}


	static RBNode *grandparent(RBNode *node)  {
		if (node and node->parent)
			return node->parent->parent;
		else
			return NULL;
	}

	static RBNode *uncle(RBNode *node) {
		RBNode *grandparent = RBNode::grandparent(node);

		if (not grandparent)
			return NULL;
		else if (grandparent->left == node->parent)
			return grandparent->right;
		else
			return grandparent->left;
	}

	static void rotate_left(RBNode *node) {
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

	static void rotate_right(RBNode *node) {
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

	static void add(RBNode *node, value_type v, const key_compare &comp = key_compare()) {
		while (node) {
			if (comp(v, node->val)) {
				if (node->left)
					node = node->left;
				else {
					node->left = A.allocate(1);
					A.construct(node->left, v);
					node->left->parent = node;
					node = node->left;
					break;
				}
			}
			else if (!comp(v, node->val)) {
				if (node->right)
					node = node->right;
				else {
					node->right = A.allocate(1);
					A.construct(node->right, v);
					node->right->parent = node;
					node = node->right;
					break;
				}
			}
			else return;
		}
		RBNode::balance(node);
	}

	static void balance(RBNode *node) {
		RBNode *uncle, *grandparent;

		if (not node->parent)
			node->color = BLACK;
		else if (node->parent->color == BLACK)
			return;
		else if ((uncle = RBNode::uncle(node)) && uncle->color == RED) {
			node->parent->color = BLACK;
			uncle->color = BLACK;
			grandparent = RBNode::grandparent(node);
			grandparent->color = RED;
			RBNode::balance(grandparent);
		}
		else {
			grandparent = RBNode::grandparent(node);
			if (node == node->parent->right and node->parent == grandparent->left) {
				RBNode::rotate_left(node->parent);
				node = node->left;
			}
			else if (node == node->parent->left and node->parent == grandparent->right) {
				RBNode::rotate_right(node->parent);
				node = node->right;
			}
			grandparent = RBNode::grandparent(node);
			node->parent->color = BLACK;
			grandparent->color = RED;
			if (node == node->parent->left and node->parent == grandparent->left)
				rotate_right(grandparent);
			else
				rotate_left(grandparent);
		}
	}


//	static void erase(RBNode *node) {
//
//	}


	RBNode() : val(NULL), color(RED), parent(NULL), left(NULL), right(NULL) {}

	explicit RBNode(value_type v) : val(v), color(RED), parent(NULL), left(NULL), right(NULL) {}

	RBNode(const RBNode &other) : val(other.val), color(other.color), parent(NULL), left(NULL), right(NULL) {
		if (other.left) {
			this->left = new RBNode(*other.left);
			this->left->parent = this;
		}
		if (other.right) {
			this->right = new RBNode(*other.right);
			this->right->parent = this;
		}
	}

	~RBNode() {
		if (left)
			A.destroy(left);
		if (right)
			A.destroy(right);
	}

	static RBNode *increment(RBNode *node) {
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

	static RBNode *decrement(RBNode *node) {
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
