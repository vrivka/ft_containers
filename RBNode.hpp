#ifndef RBNODE_HPP
#define RBNODE_HPP

enum { RED, BLACK };

template<class T, class Alloc>
class RBNode {
public:
	typedef Alloc													allocator_type;		//	Allocator type for value type
	typedef typename allocator_type::pointer						pointer;			//	Pointer to value type
	typedef typename allocator_type::template rebind<RBNode>::other	node_allocator_type;//	Allocator type for node type
	typedef typename node_allocator_type::pointer					node_pointer;		//	Pointer to node
	typedef typename node_allocator_type::reference					node_reference;		//	Reference to node

	/**	allocators	**/
	allocator_type		A;
	node_allocator_type	An;
	/**	value	**/
	pointer				val;
	/**	Node color	**/
	int16_t				color;
	/**	Node branches	**/
	node_pointer		parent;
	node_pointer		left;
	node_pointer		right;

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

	static node_pointer grandparent(node_pointer node) { return (node and node->parent ? node->parent->parent : NULL); }

	static node_pointer uncle(node_pointer node) { return (not (node = grandparent(node)) ? NULL : node->left == node->parent ? node->right : node->left); }

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

	static void swap_color(node_pointer a, node_pointer b) {
		uint16_t color = a->color;
		a->color = b->color;
		b->color = color;
	}

	static uint16_t right_caser(node_pointer node) {
		if (node->color == RED) {
			if (node->left->color == BLACK) {
				if	((not node->left->left and not node->left->right) or
					(node->left->left->color == BLACK && node->left->right->color == BLACK)) return 1;
				else if (node->left->left and node->left->left->color == RED) return 2;
				else if (node->left->right and node->left->right->color == RED) return 3;
			}
		} else {
			if (node->left->color == RED) {
				if	(node->left->right->color == BLACK and
					((not node->left->right->left and not node->left->right->right) or
					(node->left->right->left->color == BLACK and node->left->right->right->color == BLACK))) return 4;
				else if (node->left->right->color == BLACK and node->left->right->left->color == RED) return 5;
			}
			else {
				if (node->left->right and node->left->right->color == RED) return 6;
			}
		} return 7;
	}

	static void right_balance(node_pointer node) {
		switch (right_caser(node)) {
			case 1:
				swap_color(node, node->left);
				return ;
			case 2:
				node->color = BLACK;
				node->left->color = RED;
				node->left->left->color = BLACK;
				rotate_right(node);
				return ;
			case 3:
				node->color = BLACK;
				rotate_left(node->left);
				rotate_right(node);
				return ;
			case 4:
				node->left->right->color = RED;
				node->left->color = BLACK;
				rotate_right(node);
				return ;
			case 5:
				node->left->right->left->color == BLACK;
				rotate_left(node->left);
				rotate_right(node);
				return ;
			case 6:
				node->left->right->color = BLACK;
				rotate_left(node->left);
				rotate_right(node);
				return ;
			default:
				node->left->color = RED;
				erase_balance(node);
				return ;
		}
	}

	static uint16_t left_caser(node_pointer node) {
		if (node->color == RED) {
			if (node->right->color == BLACK) {
				if	((not node->right->left and not node->right->right) or
					(node->right->left->color == BLACK and node->right->right->color == BLACK)) return 1;
				else if (node->right->right and node->right->right->color == RED) return 2;
				else if (node->right->left and node->right->left->color == RED) return 3;
			}
		}
		else {
			if (node->right->color == RED) {
				if	(node->right->left->color == BLACK and
					((not node->right->left->left and not node->right->left->right) or
					(node->right->left->left->color == BLACK and node->right->left->right->color == BLACK))) return 4;
				else if (node->right->left->color == BLACK and node->right->left->right->color == RED) return 5;
			}
			else {
				if (node->right->left and node->right->left->color == RED) return 6;
			}
		}
		return 7;
	}

	static void left_balance(node_pointer node) {
		switch (left_caser(node)) {
			case 1:
				swap_color(node, node->right);
				return ;
			case 2:
				node->color = BLACK;
				node->right->color = RED;
				node->right->right->color = BLACK;
				rotate_left(node);
				return ;
			case 3:
				node->color = BLACK;
				rotate_right(node->right);
				rotate_left(node);
				return ;
			case 4:
				node->right->left->color = RED;
				node->right->color = BLACK;
				rotate_left(node);
				return ;
			case 5:
				node->right->left->right->color == BLACK;
				rotate_right(node->right);
				rotate_left(node);
				return ;
			case 6:
				node->right->left->color = BLACK;
				rotate_right(node->right);
				rotate_left(node);
				return ;
			default:
				node->right->color = RED;
				erase_balance(node);
				return ;
		}
	}

	static void erase_balance(node_pointer node) {
		node_pointer parent = node->parent;
		if (not parent) return ;
		if (parent->right == node)
			right_balance(parent);
		else
			left_balance(parent);
	}

	static node_pointer erase(node_pointer node) {
		if (node->left and node->right) { // If there are two children, then we change the values with the left largest node
			node_pointer swaps;

			swaps = swaps->max(node->left);
			swap_values(&node->val, &swaps->val);
			node = swaps;
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
				swap_values(&node->val, &node->right->val);
				return erase(node->right);
			}
			else {
				swap_values(&node->val, &node->left->val);
				return erase(node->left);
			}
		}
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
		A.destroy(val);
		A.deallocate(val, 1);
	}

	node_pointer increment(node_pointer node) {
		if (not node) return NULL;
		if (node->right) return min(node->right);
		else if (node->parent) {
			if (node->parent->left == node) return node->parent;
			else if (node->parent->right == node) {
				while (node->parent and node->parent->right == node)
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

#endif
