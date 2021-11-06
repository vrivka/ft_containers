#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "RBNode.hpp"
#include <iostream>
#include <memory>
#include "ft_pair.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_tree_iterator.hpp"
#include "iterator_traits.hpp"
#include "ft_enable_if.hpp"
#include "ft_is_integral.hpp"

namespace ft {
template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
class map {
public: //	it's done
	typedef Key															key_type;				//	The first template parameter (Key)
	typedef T															mapped_type;			//	The second template parameter (T)
	typedef ft::pair<const key_type, mapped_type>						value_type;				//	Store type (pair<const key_type,mapped_type>)
	typedef Compare														key_compare;			//	The third template parameter (Compare)
	class	value_compare {
	protected:
		key_compare comp;
	public:
		value_compare(key_compare c) : comp(c) {}
		bool operator()(const value_type &x, const value_type &y) const {
			return comp(x.first, y.first);
		}
	};																//	Nested function class to compare elements
	typedef Alloc														allocator_type;			//	The fourth template parameter (Alloc)
private:
	typedef RBNode<allocator_type>										node_type;				//	Node type
	typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;	//	Allocator type for node
	typedef node_type*													node_pointer;			//	Node pointer
public:
	typedef value_type&													reference;				//	allocator_type::reference for the default allocator
	typedef const value_type&											const_reference;		//	allocator_type::const_reference	for the default allocator
	typedef typename allocator_type::pointer							pointer;				//	allocator_type::pointer	for the default allocator
	typedef typename allocator_type::const_pointer						const_pointer;			//	allocator_type::const_pointer for the default allocator
	typedef tree_iterator<node_pointer, value_type>						iterator;				//	A bidirectional iterator to value_type convertible to const_iterator
	typedef tree_const_iterator<iterator, const value_type>				const_iterator;			//	A bidirectional iterator to const value_type
	typedef reverse_iterator<const_iterator>							const_reverse_iterator;	//	Constant reverse iterator
	typedef reverse_iterator<iterator>									reverse_iterator;		//	Reverse iterator
	typedef typename iterator_traits<iterator>::difference_type			difference_type;		//	A signed integral type, identical to: iterator_traits<iterator>::difference_type usually the same as ptrdiff_t
	typedef typename allocator_type::size_type							size_type;				//	an unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
private:
	allocator_type		A;
	node_allocator_type	An;
	value_compare		comp;
	node_pointer		root;
	node_pointer		head;
	size_type			len;
public:
	void print_lvl() {
		int h = node_type::max_height(root);
		for (int i = 0; i < h; i++) {
			node_type::print_lvl(root, i, 0);
			std::cout << std::endl;
		}
	}///

	void disable_head() {
		if (root)
			root->parent = NULL;
		head->left = NULL;
		head->right = NULL;
	}///

	void enable_head() {
		if (root)
			root->parent = head;
		head->left = root;
		head->right = root;
	}///

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

	node_pointer create_node(node_pointer node, node_pointer parent, pointer v) {
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
			disable_head();
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
			enable_head();
			b = true;
			len++;
			return ft::make_pair(root, b);
		}
		while (root->parent)
			root = root->parent;
		enable_head();
		len++;
		return ft::make_pair(node, b);
	} ///

	/**	Iterators	**/

	iterator begin() { return root->min(root); }
	const_iterator begin() const { return root->min(root); }

	iterator end() { return head; }
	const_iterator end() const { return head; }

	reverse_iterator rbegin() { return --end(); }
	const_reverse_iterator rbegin() const { return --end(); }

	reverse_iterator rend() { return --begin(); }
	const_reverse_iterator rend() const { return --begin(); }

	/**	Capacity	**/

	bool empty() const { return len == 0; }

	size_type size() const { return len; }

	size_type max_size() const { return An.max_size(); }

	/**	Element access	**/

	mapped_type &operator[](const key_type &k) {
		node_pointer node = root;
		key_compare com;
		while (node) {
			if (com(k, node->val->first)) {
				node = node->left;
			}
			else if (com(node->val->first, k)) {
				node = node->right;
			}
			else {
				return node->val->second;
			}
		}
		pointer v = alloc_val(k);
		return insert(v).first->second;

	}

	/**	Modifier	**/

	ft::pair<iterator,bool> insert(const value_type &val) {
		node_pointer node = root;
		bool b = false;
		if (node) {
			disable_head();
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
			enable_head();
			b = true;
			len++;
			return ft::make_pair(root, b);
		}
		while (root->parent)
			root = root->parent;
		enable_head();
		len++;
		return ft::make_pair(node, b);
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

	void erase(iterator position) { erase(position->first); }

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
			disable_head();
			node = node_type::erase(node);
			if (node == root) {
				if (not root->parent)
					root = NULL;
				else
					root = root->parent;
			}
			An.destroy(node);
			An.deallocate(node, 1);
			len--;
			while (root and root->parent)
				root = root->parent;
			enable_head();
			return 1;
		}
		return 0;
	}

	void erase(iterator first, iterator last) {
		for (; first != last;)
			erase(first++);
	} //Erase elements (public member function )

	void swap(map& x) {
		node_pointer tmp_root = this->root;
		this->root = x.root;
		x.root = tmp_root;

		node_pointer tmp_head = this->head;
		this->head = x.head;
		x.head = tmp_head;

		size_type tmp_len = this->len;
		this->len = x.len;
		x.len = tmp_len;
	}// Swap content (public member function )

	void clear() {
		disable_head();
		if (root) {
			An.destroy(root);
			An.deallocate(root, 1);
		}
		root = NULL;
		enable_head();
		len = 0;
	}// Clear content (public member function )

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
				return node;
		}
		return end();
	}

	const_iterator find (const key_type &k) const {
		node_pointer node = root;
		key_compare com;
		while (node) {
			if (com(k, node->val->first))
				node = node->left;
			else if (com(node->val->first, k))
				node = node->right;
			else
				return node;
		}
		return end();
	}	//	Get iterator to element (public member function )

	size_type count (const key_type &k) const {
		node_pointer node = root;
		key_compare com;
		while (node) {
			if (com(k, node->val->first))
				node = node->left;
			else if (com(node->val->first, k))
				node = node->right;
			else
				return 1;
		}
		return 0;
	}//	Count elements with a specific key (public member function )

	iterator lower_bound(const key_type& k) {
		iterator it = begin();
		key_compare com;

		while (com(it->first, k))
			it++;
		while (it != end() and com(it->first, k))
			it--;
		return it;
	}

	const_iterator lower_bound(const key_type &k) const {
		const_iterator it = begin();
		key_compare com;

		while (com(it->first, k))
			it++;
		while (it != end() and com(it->first, k))
			it--;
		return it;
	}//	Return iterator to lower bound (public member function )

	iterator upper_bound(const key_type& k) {
		iterator it = begin();
		key_compare com;

		while (com(it->first, k))
			it++;
		while (it != end() and not com(k, it->first))
			it++;
		return it;
	}

	const_iterator upper_bound(const key_type& k) const {
		const_iterator it = begin();
		key_compare com;

		while (com(it->first, k))
			it++;
		while (it != end() and com(it->first, k))
			it--;
		it++;
		return it;
	}//	Return iterator to upper bound (public member function )

	pair<const_iterator,const_iterator> equal_range(const key_type& k) const { return make_pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)); }

	pair<iterator,iterator> equal_range(const key_type& k) { return ft::make_pair<iterator,iterator>(lower_bound(k), upper_bound(k)); }//	Get range of equal elements (public member function )

	/**	Constructors	**/

	/**	Default constructor	**/
	explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), An(), comp(comp), root(NULL), len(0) {
		head = An.allocate(1);
		An.construct(head);
		head->color = HEAD;
		enable_head();
	}

	/**	Range iterator constructor	**/
	template<class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), An(), comp(comp), root(NULL), len(0) {
		head = An.allocate(1);
		An.construct(head);
		head->color = HEAD;
		for (; first != last; first++, len++)
			insert(*first);
	};

	/**	Copy constructor	**/
	map(const map &x) : A(x.A), An(x.An), comp(x.comp), len(x.len) {
		head = An.allocate(1);
		An.construct(head);
		if (x.root) {
			this->root = An.allocate(1);
			An.construct(this->root, *x.root);
		}
		enable_head();
	};

	/**	Destructor	**/

	~map() {
		disable_head();
		if (root) {
			An.destroy(root);
			An.deallocate(root, 1);
		}
		An.destroy(head);
		An.deallocate(head, 1);
	}

	/**	Assign overload	**/
	map &operator=(const map &x) {
		if (this == &x)
			return *this;
		disable_head();
		if (root) {
			An.destroy(root);
			An.deallocate(root, 1);
		}
		root = NULL;
		if (x.root) {
			root = An.allocate(1);
			An.construct(root, *x.root);
		}
		enable_head();
		len = x.len;
		return *this;
	}

	/**	Non-member function	**/

	/*	Relational operators	*/
	friend bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		if (lhs.len == rhs.len) {
			iterator lit = lhs.begin();
			iterator lite = lhs.end();
			iterator rit = rhs.begin();
			iterator rite = rhs.end();
			for (; i < lhs.len;) {
				if (lhs.arr[i] != rhs.arr[i])
					return false;
			}
			return true;
		}
		return false;
	}

	friend bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return !(lhs == rhs); }

	friend bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		if (lhs.len < rhs.len)
			return true;
		for (size_type i = 0; i < lhs.len; i++) {
			if (lhs.arr[i] < rhs.arr[i])
				return true;
			else if (lhs.arr[i] > rhs.arr[i])
				return false;
		}
		return false;
	}

	friend bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return !(rhs < lhs); }

	friend bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return rhs < lhs; }

	friend bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return !(lhs < rhs); }

	template<class K, class V, class compare, class alloc>
	friend void swap(map<K, V, compare, alloc> &x, map<K, V, compare, alloc> &y) { x.swap(y); }
};

}

#endif
