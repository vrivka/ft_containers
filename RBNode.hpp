#ifndef RBNODE_HPP
#define RBNODE_HPP

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
	typedef Alloc													allocator_type;		//	Allocator type for value type
	typedef typename allocator_type::pointer						pointer;			//	Pointer to value type
	typedef typename allocator_type::template rebind<RBNode>::other	node_allocator_type;//	Allocator type for node type
	typedef typename node_allocator_type::pointer					node_pointer;		//	Pointer to node
	typedef typename node_allocator_type::reference					node_reference;		//	Reference to node

	/**	Allocators	**/
	allocator_type		allocator;
	node_allocator_type	node_allocator;
	/**	Value	**/
	pointer				value;
	/**	Node color	**/
	int16_t				color;
	/**	Node branches	**/
	node_pointer		parent;
	node_pointer		left;
	node_pointer		right;

	/*	Return first element	*/
	node_pointer min(node_pointer node) {
		if (not node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

	/*	Return last element	*/
	node_pointer max(node_pointer node) {
		if (not node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	/*	Max height of tree	*/
	static int max_height(RBNode *node) {
		if (not node)
			return 0;
		int left_h = max_height(node->left);
		int right_h = max_height(node->right);
		if (left_h > right_h)
			return left_h + 1;
		else
			return right_h + 1;
	}

	/*	Print tree by level	*/
	static void print_lvl(RBNode *node, int print_lvl, int lvl) {
		if (node) {
			if (print_lvl == lvl) {
				std::cout << node->value->first;
				std::cout << (node->color == RED ? 'r' : 'b') << ' ';
			}
			else {
				print_lvl(node->left, print_lvl, lvl + 1);
				print_lvl(node->right, print_lvl, lvl + 1);
			}
		}
	}

	/*	Tree balancer after inserting	*/
	static void balance(node_pointer node) {
		node_pointer _uncle, _grandparent;

		if (not node->parent)
			node->color = BLACK;
		else if (node->parent->color == BLACK)
			return;
		else if ((_uncle = uncle(node)) and _uncle->color == RED) {
			node->parent->color = BLACK;
			_uncle->color = BLACK;
			_grandparent = grandparent(node);
			_grandparent->color = RED;
			balance(_grandparent);
		}
		else {
			_grandparent = grandparent(node);
			if (node == node->parent->right and node->parent == _grandparent->left) {
				rotate_left(node->parent);
				node = node->left;
			}
			else if (node == node->parent->left and node->parent == _grandparent->right) {
				rotate_right(node->parent);
				node = node->right;
			}
			_grandparent = grandparent(node);
			node->parent->color = BLACK;
			_grandparent->color = RED;
			if (node == node->parent->left and node->parent == _grandparent->left)
				rotate_right(_grandparent);
			else
				rotate_left(_grandparent);
		}
	}

	/*	Tree balancer before deleting	*/
	static node_pointer erase_balancer(node_pointer node) {
		if (node->left and node->right) { // If there are two children, then we change the values with the left largest node
			node_pointer max_left_child;

			max_left_child = node->max(node->left);
			swap_nodes1(node, max_left_child);
		}
		if (node->color == RED and (not node->right and not node->left)) { // If node is RED and no children, delete it
			if (node->parent->left == node)
				node->parent->left = NULL;
			else if (node->parent->right == node)
				node->parent->right = NULL;
			return node;
		}
		else if (node->color == BLACK and (not node->right and not node->left)) { // If node is BLACK and no children
			black_node_balancer(node);
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
				return erase_balancer(node);
			}
			else if (node->left) {
				swap_nodes(node, node->left);
				return erase_balancer(node);
			}
		}
		return node;
	}

	/*	Increment node value	*/
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

	/*	Decrement node value	*/
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

	/**	Constructors	**/

	/*	Default constructor	*/
	RBNode() : allocator(), node_allocator(), value(NULL), color(RED), parent(NULL), left(NULL), right(NULL) {}

	/*	Copy constructor	*/
	RBNode(const RBNode &other) : allocator(), node_allocator(), color(other.color), parent(NULL), left(NULL), right(NULL) {
		if (other.left) {
			left = node_allocator.allocate(1);
			node_allocator.construct(left, *other.left);
			left->parent = this;
		}
		value = allocator.allocate(1);
		allocator.construct(value, *other.value);
		if (other.right) {
			right = node_allocator.allocate(1);
			node_allocator.construct(right, *other.right);
			right->parent = this;
		}
	}

	/*	Destructor	*/
	~RBNode() {
		if (left) {
			node_allocator.destroy(left);
			node_allocator.deallocate(left, 1);
		}
		if (right) {
			node_allocator.destroy(right);
			node_allocator.deallocate(right, 1);
		}
		if (color != HEAD) {
			allocator.destroy(value);
			allocator.deallocate(value, 1);
		}
	}

	/*	Assign operator overload	*/
	node_reference operator=(const node_reference other) {
		if (this == &other)
			return *this;
		allocator.destroy(value);
		allocator.deallocate(value, 1);
		value = allocator.allocate(1);
		allocator.construct(value, *other.value);
		color = other.color;
		parent = NULL;
		if (left) {
			node_allocator.destroy(left);
			node_allocator.deallocate(left, 1);
			left = NULL;
		}
		if (right) {
			node_allocator.destroy(right);
			node_allocator.deallocate(right, 1);
			right = NULL;
		}
		if (other.left) {
			left = node_allocator.allocate(1);
			node_allocator.construct(left, *other.left);
		}
		if (other.right) {
			right = node_allocator.allocate(1);
			node_allocator.construct(right, *other.right);
		}
		return *this;
	}

private:
	/*	Get grandparent of node (node->parent->parent)	*/
	static node_pointer grandparent(node_pointer node) { return (node and node->parent ? node->parent->parent : NULL); }

	/*	Get uncle of node (node->parent->parent->left/right)	*/
	static node_pointer uncle(node_pointer node) {
		node_pointer _grandparent = grandparent(node);

		if (not _grandparent)
			return NULL;
		else if (_grandparent->left == node->parent)
			return _grandparent->right;
		else
			return _grandparent->left;
	}

	/*	Single left rotate	*/
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

	/*	Single right rotate	*/
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

	/*	Get sibling (node->parent->left/right)	*/
	static node_pointer sibling(node_pointer node) {
		if (node->parent->right == node)
			return node->parent->left;
		else if (node->parent->left == node)
			return node->parent->right;
		return NULL;
	}

	/*	Get right nephew (node->parent->left/right->right)	*/
	static node_pointer right_nephew(node_pointer sibling) {
		if (not sibling)
			return NULL;
		return sibling->right;
	}

	/*	Get left nephew (node->parent->left/right->left)	*/
	static node_pointer left_nephew(node_pointer sibling) {
		if (not sibling)
			return NULL;
		return sibling->left;
	}

	/*	Balancer if black node has no children	*/
	static void black_node_balancer(node_pointer node) {
		node_pointer _parent = node->parent, _sibling, _right_nephew, _left_nephew;

		if (not _parent)
			return ;
		_sibling = sibling(node);
		_right_nephew = right_nephew(_sibling);
		_left_nephew = left_nephew(_sibling);
		if (_parent->color == BLACK and (_sibling and _sibling->color == RED)) {
			_parent->color = RED;
			_sibling->color = BLACK;
			if (_parent->right == node)
				rotate_right(_parent);
			else if (_parent->left == node)
				rotate_left(_parent);
			_sibling = sibling(node);
			_right_nephew = right_nephew(_sibling);
			_left_nephew = left_nephew(_sibling);
		}
		if (_sibling and _sibling->color == BLACK) {
			if ((not _right_nephew or _right_nephew->color == BLACK) and
				(not _left_nephew or _left_nephew->color == BLACK)) {
				if (_parent->color == BLACK) {
					_sibling->color = RED;
					black_node_balancer(_parent);
				}
				else if (_parent->color == RED) {
					_parent->color = BLACK;
					_sibling->color = RED;
					return ;
				}
			}
			else if (_parent->right == node) {
				if (_right_nephew and _right_nephew->color == RED) {
					_sibling->color = RED;
					_right_nephew->color = BLACK;
					rotate_left(_sibling);
				}
				_sibling = sibling(node);
				_left_nephew = left_nephew(_sibling);
				if (_left_nephew and _left_nephew->color == RED) {
					_sibling->color = _parent->color;
					_parent->color = BLACK;
					_left_nephew->color = BLACK;
					rotate_right(_parent);
					return ;
				}
			}
			else if (_parent->left == node) {
				if (_left_nephew and _left_nephew->color == RED) {
					_sibling->color = RED;
					_left_nephew->color = BLACK;
					rotate_right(_sibling);
				}
				_sibling = sibling(node);
				_right_nephew = right_nephew(_sibling);
				if (_right_nephew and _right_nephew->color == RED) {
					_sibling->color = _parent->color;
					_parent->color = BLACK;
					_right_nephew->color = BLACK;
					rotate_left(_parent);
					return ;
				}
			}
		}
	}

	/*	Swap nodes if black node has one child	*/
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

	/*	Swap nodes if black node has two children	*/
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

};
}

#endif
