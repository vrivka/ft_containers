#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <memory>

enum { RED, BLACK, HEAD };

namespace ft {
template<class T>
void swap_h(T *a, T *b) {
	T c = *a;
	*a = *b;
	*b = c;
}

template<class Alloc>
class RBNode {
public:
	typedef Alloc allocator_type;        //	Allocator type for value type
	typedef typename allocator_type::pointer pointer;            //	Pointer to value type
	typedef typename allocator_type::template rebind<RBNode>::other node_allocator_type;//	Allocator type for node type
	typedef typename node_allocator_type::pointer node_pointer;        //	Pointer to node
	typedef typename node_allocator_type::reference node_reference;        //	Reference to node

	/**	allocators	**/
	allocator_type A;
	node_allocator_type An;
	/**	value	**/
	pointer val;
	/**	Node color	**/
	int16_t color;
	/**	Node branches	**/
	node_pointer parent;
	node_pointer left;
	node_pointer right;

	node_pointer min(node_pointer node) {
		if (not node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

	node_pointer max(node_pointer node) {
		if (not node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	static int max_height(RBNode *node) {
		if (not node)
			return 0;
		int h_left = max_height(node->left);
		int h_right = max_height(node->right);
		if (h_left > h_right)
			return h_left + 1;
		else
			return h_right + 1;
	}

	static void print_lvl(RBNode *node, int n, int lvl) {
		if (node) {
			if (n == lvl) {
				std::cout << node->val->first;
				std::cout << (node->color == RED ? 'r' : 'b') << ' ';
			}
			else {
				print_lvl(node->left, n, lvl + 1);
				print_lvl(node->right, n, lvl + 1);
			}
		}
	}

	static node_pointer grandparent(node_pointer node) { return (node and node->parent ? node->parent->parent : NULL); }

	static node_pointer uncle(node_pointer node) {
		RBNode *grandparent_ = grandparent(node);

		if (not grandparent_)
			return NULL;
		else if (grandparent_->left == node->parent)
			return grandparent_->right;
		else
			return grandparent_->left;
	}

	static void rotate_left(node_pointer node) {
		if (not node or not node->right) return ;
		node_pointer pivot = node->right;

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

	static void rotate_right(node_pointer node) {
		if (not node or not node->left) return ;
		node_pointer pivot = node->left;

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

	static void balance(node_pointer node) {
		node_pointer uncle_, grandparent_;

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

	static void swap_values(pointer *a, pointer *b) {
		pointer c = *a;
		*a = *b;
		*b = c;
	}

	static node_pointer sibling(node_pointer node) {
		if (node->parent->right == node)
			return node->parent->left;
		else if (node->parent->left == node)
			return node->parent->right;
		return NULL;
	}

	static node_pointer right_nephew(node_pointer sibling) {
		if (not sibling)
			return NULL;
		return sibling->right;
	}

	static node_pointer left_nephew(node_pointer sibling) {
		if (not sibling)
			return NULL;
		return sibling->left;
	}

	static void erase_balance(node_pointer node) {
		node_pointer parent = node->parent, sibling_, right_nephew_, left_nephew_;
		if (not parent)
			return ;
		sibling_ = sibling(node);
		right_nephew_ = right_nephew(sibling_);
		left_nephew_ = left_nephew(sibling_);
		if (parent->color == BLACK and (sibling_ and sibling_->color == RED)) {
			parent->color = RED;
			sibling_->color = BLACK;
			if (parent->right == node)
				rotate_right(parent);
			else if (parent->left == node)
				rotate_left(parent);
			sibling_ = sibling(node);
			right_nephew_ = right_nephew(sibling_);
			left_nephew_ = left_nephew(sibling_);
		}
		if (sibling_ and sibling_->color == BLACK) {
			if ((not right_nephew_ or right_nephew_->color == BLACK) and
				(not left_nephew_ or left_nephew_->color == BLACK)) {
				if (parent->color == BLACK) {
					sibling_->color = RED;
					erase_balance(parent);
				}
				else if (parent->color == RED) {
					parent->color = BLACK;
					sibling_->color = RED;
					return ;
				}
			}
			else if (parent->right == node) {
				if (right_nephew_ and right_nephew_->color == RED) {
					sibling_->color = RED;
					right_nephew_->color = BLACK;
					rotate_left(sibling_);
				}
				sibling_ = sibling(node);
				left_nephew_ = left_nephew(sibling_);
				if (left_nephew_ and left_nephew_->color == RED) {
					sibling_->color = parent->color;
					parent->color = BLACK;
					left_nephew_->color = BLACK;
					rotate_right(parent);
					return ;
				}
			}
			else if (parent->left == node) {
				if (left_nephew_ and left_nephew_->color == RED) {
					sibling_->color = RED;
					left_nephew_->color = BLACK;
					rotate_right(sibling_);
				}
				sibling_ = sibling(node);
				right_nephew_ = right_nephew(sibling_);
				if (right_nephew_ and right_nephew_->color == RED) {
					sibling_->color = parent->color;
					parent->color = BLACK;
					right_nephew_->color = BLACK;
					rotate_left(parent);
					return ;
				}
			}
		}
	}

	static void swap_nodes(node_pointer a, node_pointer b) {
		node_pointer a_parent = a->parent;
		if (a_parent and a_parent->left == a)
			a_parent->left = b;
		else if (a_parent and a_parent->right == a)
			a_parent->right = b;
		b->parent = a_parent;
		a->parent = b;
		if (a->left == b) {
			a->left = b->left;
			b->left = a;
		}
		else if (a->right == b) {
			a->right = b->right;
			b->right = a;
		}
		uint16_t c = a->color;
		a->color = b->color;
		b->color = c;
	}

	static void swap_nodes1(node_pointer a, node_pointer b) {

		node_pointer a_parent = a->parent;
		node_pointer a_left = a->left;
		node_pointer a_right = a->right;

		node_pointer b_parent = b->parent;
		node_pointer b_left = b->left;
		node_pointer b_right = b->right;

		if (a_parent and a_parent->left == a)
			a_parent->left = b;
		else if (a_parent and a_parent->right == a)
			a_parent->right = b;
		if (b_parent and b_parent->left == b)
			b_parent->left = a;
		else if (b_parent and b_parent->right == b)
			b_parent->right = a;
		if (a_left)
			a_left->parent = b;
		if (a_right)
			a_right->parent = b;
		if (b_left)
			b_left->parent = a;
		if (b_right)
			b_right->parent = a;
		ft::swap_h(&a->left, &b->left);
		ft::swap_h(&a->right, &b->right);
		ft::swap_h(&a->parent, &b->parent);
		ft::swap_h(&a->color, &b->color);
	}

	static node_pointer erase(node_pointer node) {
		if (node->left and node->right) { // If there are two children, then we change the values with the left largest node
			node_pointer swaps;

			swaps = node->max(node->left);
			swap_nodes1(node, swaps);
		}
		if (node->color == RED and (not node->right and not node->left)) { // If node is RED and no children, delete it
			if (node->parent->left == node)
				node->parent->left = NULL;
			else if (node->parent->right == node)
				node->parent->right = NULL;
			return node;
		}
		else if (node->color == BLACK and (not node->right and not node->left)) { // If node is BLACK and no children
			erase_balance(node);
			if (not node->parent)
				return node;
			else if (node->parent->right == node)
				node->parent->right = NULL;
			else if (node->parent->left == node)
				node->parent->left = NULL;
			return node;
		}
		else if (node->color == BLACK) { // If node is BLACK and has one child(always RED), swap values and delete child
			if (node->right) {
				swap_nodes(node, node->right);
				return erase(node);
			}
			else if (node->left) {
				swap_nodes(node, node->left);
				return erase(node);
			}
		}
		return node;
	}

	RBNode() : A(), An(), val(NULL), color(RED), parent(NULL), left(NULL), right(NULL) {}

	RBNode(const RBNode &other) : A(), An(), color(other.color), parent(NULL), left(NULL), right(NULL) {
		if (other.left) {
			left = An.allocate(1);
			An.construct(left, *other.left);
			left->parent = this;
		}
		val = A.allocate(1);
		A.construct(val, *other.val);
		if (other.right) {
			right = An.allocate(1);
			An.construct(right, *other.right);
			right->parent = this;
		}
	}

	~RBNode() {
		if (left) {
			An.destroy(left);
			An.deallocate(left, 1);
		}
		if (right) {
			An.destroy(right);
			An.deallocate(right, 1);
		}
		if (this->color != HEAD) {
			A.destroy(val);
			A.deallocate(val, 1);
		}
	}

	node_pointer increment(node_pointer node) {
		if (not node) return NULL;
		if (node->right) return min(node->right);
		else if (node->parent) {
			if (node->parent->left == node) return node->parent;
			else if (node->parent->right == node) {
				while (node->parent and node->parent->color != HEAD and node->parent->right == node)
					node = node->parent;
				return node->parent;
			}
		}
		return node;
	}

	node_pointer decrement(node_pointer node) {
		if (not node) return NULL;
		if (node->left) return max(node->left);
		else if (node->parent) {
			if (node->parent->right == node) return node->parent;
			else if (node->parent->left == node) {
				while (node->parent and node->parent->left == node)
					node = node->parent;
				return node->parent;
			}
		}
		return node;
	}

	node_reference operator=(const node_reference other) {
		if (this == &other)
			return *this;
		A.destroy(val);
		A.deallocate(val, 1);
		val = A.allocate(1);
		A.construct(val, *other.val);
		color = other.color;
		parent = NULL;
		if (left) {
			An.destroy(left);
			An.deallocate(left, 1);
			left = NULL;
		}
		if (right) {
			An.destroy(right);
			An.deallocate(right, 1);
			right = NULL;
		}
		if (other.left) {
			left = An.allocate(1);
			An.construct(left, *other.left);
		}
		if (other.right) {
			right = An.allocate(1);
			An.construct(right, *other.right);
		}
		return *this;
	}
};

}
#endif
