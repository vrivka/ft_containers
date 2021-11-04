#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "ft_pair.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_tree_iterator.hpp"
#include "ft_enable_if.hpp"
#include "ft_is_integral.hpp"
#include "RBNode.hpp"

namespace ft {
template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
class map {
public: ///	it's done
	typedef Key													key_type;				//	The first template parameter (Key)
	typedef T													mapped_type;			//	The second template parameter (T)
	typedef pair<const key_type, mapped_type>					value_type;				//	Store type (pair<const key_type,mapped_type>)
	typedef Compare												key_compare;			//	The third template parameter (Compare)
	class	value_compare {
	protected:
		key_compare comp;
	public:
		value_compare(key_compare c) : comp(c) {}
		bool operator()(const value_type &x, const value_type &y) const {
			return comp(x.first, y.first);
		}
	};														//	Nested function class to compare elements
	typedef Alloc												allocator_type;			//	The fourth template parameter (Alloc)
private:
	typedef Compare														value_comp;				//	Nested function class to compare elements
	typedef RBNode<value_type, allocator_type>							node_type;					//	Node type
	typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;	//	Allocator type for node
	typedef typename node_allocator_type::pointer						node_pointer;			//	Node pointer
	typedef typename node_allocator_type::const_pointer					const_node_pointer;		//	Constant node pointer
public:
	typedef value_type&											reference;				//	allocator_type::reference for the default allocator
	typedef const value_type&									const_reference;		//	allocator_type::const_reference	for the default allocator
	typedef typename allocator_type::pointer					pointer;				//	allocator_type::pointer	for the default allocator
	typedef typename allocator_type::const_pointer				const_pointer;			//	allocator_type::const_pointer for the default allocator
	typedef tree_iterator<node_pointer, value_type> const				const_iterator;			//	A bidirectional iterator to const value_type
	typedef tree_iterator<node_pointer, value_type>						iterator;				//	A bidirectional iterator to value_type convertible to const_iterator
	typedef reverse_iterator<const_iterator>					const_reverse_iterator;	//	Constant reverse iterator
	typedef reverse_iterator<iterator>							reverse_iterator;		//	Reverse iterator
	typedef typename iterator_traits<iterator>::difference_type	difference_type;		//	A signed integral type, identical to: iterator_traits<iterator>::difference_type usually the same as ptrdiff_t
	typedef typename allocator_type::size_type					size_type;				//	an unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
private:
	allocator_type A;
	node_allocator_type An;
	value_compare comp;
	node_pointer root;
	size_type len;
public:
	void print_lvl() {
		int h = node_type::max_height(root);
		for (int i = 0; i < h; i++) {
			node_type::print_lvl(root, i, 0);
			std::cout << std::endl;
		}
	}

	///*	Iterators	*/

	iterator begin() { return iterator(root->min(root), &root); }
	const_iterator begin() const { return iterator(root->root(root), &root); }

	iterator end() { return ++iterator(root->max(root), &root); }
	const_iterator end() const { return ++iterator(root->max(root), &root); }

	reverse_iterator rbegin() { return --end(); }
	const_reverse_iterator rbegin() const { return --end(); }

	reverse_iterator rend() { return --begin(); }
	const_reverse_iterator rend() const { return --begin(); }

	///*	Capacity	*/

	bool empty() const { return len == 0; }

	size_type size() const { return len; }

	size_type max_size() const { return node_allocator_type().max_size(); }

	///*	Element access	*/

	value_type *alloc_val(const key_type &v) {
		value_type *val_ptr = A.allocate(1);
		A.construct(val_ptr, v, mapped_type());
		return val_ptr;
	} ///

	value_type *alloc_val(const key_type &f, const mapped_type &s) {
		value_type *val_ptr = A.allocate(1);
		A.construct(val_ptr, f, s);
		return val_ptr;
	} ///

	mapped_type &operator[](const key_type &k) {
		node_pointer node = root;
		key_compare com;
		while (node) {
			if (com(k, node->val->first))
				node = node->left;
			else if (com(node->val->first, k))
				node = node->right;
			else
				return node->val->second;
		}
		pointer v = alloc_val(k);
		ft::pair<iterator,bool> ret = insert(v);
		return ret.first->second;
	}

	///*	Modifier	*/

	node_pointer create_node(node_pointer node, node_pointer parent, value_type *v) {
		node = An.allocate(1);
		An.construct(node);
		node->parent = parent;
		node->val = v;
		return node;
	} ///

	node_pointer create_node(node_pointer node, node_pointer parent, const value_type &v) {
		node = An.allocate(1);
		An.construct(node);
		node->parent = parent;
		node->val = A.allocate(1);
		A.construct(node->val, v);
		return node;
	} ///

	ft::pair<iterator,bool> insert(pointer val) {
		node_pointer node = root;
		bool b = false;
		if (node) {
			while (node) {
				if (comp(*val, *node->val)) {
					if (node->left)
						node = node->left;
					else {
						node->left = create_node(node->left, node, val);
						node_type::balance(node->left);
						b = true;
						break ;
					}
				} else if (comp(*node->val, *val)) {
					if (node->right)
						node = node->right;
					else {
						node->right = create_node(node->right, node, val);
						node_type::balance(node->right);
						b = true;
						break ;
					}
				} else break;
			}
		} else {
			root = create_node(root, NULL, val);
			node_type::balance(root);
			b = true;
			return ft::make_pair(iterator(root, &root), b);
		}
		while (root->parent)
			root = root->parent;
		return ft::make_pair(iterator(node, &root), b);
	} ///

	ft::pair<iterator,bool> insert(const value_type &val) {
		node_pointer node = root;
		bool b = false;
		if (node) {
			while (node) {
				if (comp(val, *node->val)) {
					if (node->left)
						node = node->left;
					else {
						node->left = create_node(node->left, node, val);
						node_type::balance(node->left);
						b = true;
						break ;
					}
				} else if (comp(*node->val, val)) {
					if (node->right)
						node = node->right;
					else {
						node->right = create_node(node->right, node, val);
						node_type::balance(node->right);
						b = true;
						break ;
					}
				} else break;
			}
		} else {
			root = create_node(root, NULL, val);
			node_type::balance(root);
			b = true;
			return ft::make_pair(iterator(root, &root), b);
		}
		while (root->parent)
			root = root->parent;
		return ft::make_pair(iterator(node, &root), b);
	}

	iterator insert(iterator position, const value_type &val) {
		(void)position;
		return insert(val).first;
	}

	template<class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		for (; first != last; first++)
			insert(*first);
	}

	void erase(iterator position) {
		node_pointer node = root;
		while (node) {
			if (comp(*position, *node->val))
				node = node->left;
			else if (comp(*node->val, *position))
				node = node->right;
			else
				break ;
		}
		if (node) {
			node = node_type::erase(node);
			if (node == root)
				root = NULL;
			An.destroy(node);
			An.deallocate(node, 1);
			while (root and root->parent)
				root = root->parent;
		}
	}

	size_type erase(const key_type& k) {
		node_pointer node = root;
		key_compare com;
		while (node) {
			if (com(k, node->val->first))
				node = node->left;
			else if (com(node->val->first, k))
				node = node->right;
			else
				break ;
		}
		if (node) {
			node = node_type::erase(node);
			if (node == root)
				root = NULL;
			An.destroy(node);
			An.deallocate(node, 1);
			while (root and root->parent)
				root = root->parent;
			return 1;
		}
		return 0;
	}

	void erase(iterator first, iterator last) {
		iterator it;
		while (first != last) {
			it = ++first;
			first--;
			erase(first);
			first = it;
		}
	} //Erase elements (public member function )
//
//	void swap(map& x);// Swap content (public member function )
//	void clear();// Clear content (public member function )

	/**	Operations **/
	iterator find (const key_type &k) {
		node_pointer node = root;
		key_compare com;
		while (node) {
			if (com(k, node->val->first))
				node = node->left;
			else if (com(node->val->first, k))
				node = node->right;
			else
				return iterator(node, &root);
		}
		return end();
	};

	const_iterator find (const key_type& k) const {
		node_pointer node = root;
		key_compare com;
		while (node) {
			if (com(k, node->val->first))
				node = node->left;
			else if (com(node->val->first, k))
				node = node->right;
			else
				return iterator(node, &root);
		}
		return end();
	};	//	Get iterator to element (public member function )
//	Count elements with a specific key (public member function )
//	Return iterator to lower bound (public member function )
//	Return iterator to upper bound (public member function )
//	Get range of equal elements (public member function )

	///*	Constructors	*/

	/*	Default constructor	*/
	explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), An(), comp(comp), root(NULL), len(0) {}

	/*	Range iterator constructor	*/
	template<class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), An(), comp(comp), root(NULL), len(0) {
		for (; first != last; first++, len++)
			insert(*first);
	};

	/*	Copy constructor	*/
	map(const map &x) : A(x.A), An(x.An), comp(x.comp), len(x.len) {
		if (x.root) {
			this->root = An.allocate(1);
			An.construct(this->root, *x.root);
		}
	};

	///*	Destructor	*/

	~map() {
		if (root) {
			An.destroy(root);
			An.deallocate(root, 1);
		}
	}

	///*	Assign overload	*/
	map &operator=(const map &x) {
		if (this == &x)
			return *this;
		this->A = x.A;
		this->An = x.An;
		this->comp = x.comp;
		if (this->root) {
			An.destroy(this->root);
			An.deallocate(this->root, 1);
		}
		this->root = NULL;
		if (x.root) {
			this->root = An.allocate(1);
			An.construct(this->root, *x.root);
		}
		this->len = x.len;
		return *this;
	};
};

}

#endif
