#ifndef FT_SET_HPP
#define FT_SET_HPP

#include "RBNode.hpp"
#include <iostream>
#include <memory>
#include "ft_pair.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_tree_iterator.hpp"
#include "ft_utilities.hpp"

namespace ft {
template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class set {
public:
	typedef T															key_type;				//	The first template parameter (Key)
	typedef T															value_type;				//	The first template parameter (Key)
	typedef Compare														key_compare;			//	The second template parameter (Compare)
	typedef Compare														value_compare;			//	The second template parameter (Compare)
	typedef Alloc														allocator_type;			//	The third template parameter (Alloc)
private:
	typedef RBNode<allocator_type>										node_type;				//	Node type
	typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;	//	Allocator type for node
	typedef node_type*													node_pointer;			//	Node pointer
public:
	typedef value_type&													reference;				//	allocator_type::reference for the default allocator
	typedef const value_type&											const_reference;		//	allocator_type::const_reference	for the default allocator
	typedef typename allocator_type::pointer							pointer;				//	allocator_type::pointer	for the default allocator
	typedef typename allocator_type::const_pointer						const_pointer;			//	allocator_type::const_pointer for the default allocator
	typedef tree_iterator<node_pointer, const value_type>				iterator;				//	A bidirectional iterator to value_type convertible to const_iterator
	typedef tree_const_iterator<iterator, const value_type>				const_iterator;			//	A bidirectional iterator to const value_type
	typedef reverse_iterator<const_iterator>							const_reverse_iterator;	//	Constant reverse iterator
	typedef reverse_iterator<iterator>									reverse_iterator;		//	Reverse iterator
	typedef typename iterator_traits<iterator>::difference_type			difference_type;		//	A signed integral type, identical to: iterator_traits<iterator>::difference_type usually the same as ptrdiff_t
	typedef typename allocator_type::size_type							size_type;				//	an unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
private:
	allocator_type		_allocator;
	node_allocator_type	_node_allocator;
	value_compare		_val_comp;
	node_pointer		_root;
	node_pointer		_head;
	size_type			_size;

	void print_lvl() {
		int height = node_type::max_height(_root);
		for (int index = 0; index < height; index++) {
			node_type::print_lvl(_root, index, 0);
			std::cout << std::endl;
		}
	}

	void disable_head() {
		if (_root)
			_root->parent = NULL;
		_head->left = NULL;
		_head->right = NULL;
	}

	void enable_head() {
		if (_root)
			_root->parent = _head;
		_head->left = _root;
		_head->right = _root;
	}

	node_pointer create_node(node_pointer node, node_pointer parent, const value_type &value) {
		node = _node_allocator.allocate(1);
		_node_allocator.construct(node);
		node->parent = parent;
		node->value = _allocator.allocate(1);
		_allocator.construct(node->value, value);
		return node;
	}
public:
	/**	Iterators	**/

	iterator begin() { return _root ? _root->min(_root) : _head; }
	const_iterator begin() const { return _root ? iterator(_root->min(_root)) : end(); }

	iterator end() { return _head; }
	const_iterator end() const { return iterator(_head); }

	reverse_iterator rbegin() { return --end(); }
	const_reverse_iterator rbegin() const { return --end(); }

	reverse_iterator rend() { return --begin(); }
	const_reverse_iterator rend() const { return --begin(); }

	/**	Capacity	**/

	bool empty() const { return _size == 0; }

	size_type size() const { return _size; }

	size_type max_size() const { return _node_allocator.max_size(); }

	/**	Modifier	**/

	pair<iterator,bool> insert(const value_type &value) {
		node_pointer node = _root;
		bool is_insert = false;

		if (node) {
			disable_head();
			while (node) {
				if (_val_comp(value, *node->value)) {
					if (node->left)
						node = node->left;
					else {
						node->left = create_node(node->left, node, value);
						node = node->left;
						node_type::balance(node);
						is_insert = true;
						break ;
					}
				} else if (_val_comp(*node->value, value)) {
					if (node->right)
						node = node->right;
					else {
						node->right = create_node(node->right, node, value);
						node = node->right;
						node_type::balance(node);
						is_insert = true;
						break ;
					}
				} else break;
			}
		}
		else {
			_root = create_node(_root, NULL, value);
			node_type::balance(_root);
			enable_head();
			is_insert = true;
			_size++;
			return ft::make_pair(_root, is_insert);
		}
		while (_root->parent)
			_root = _root->parent;
		enable_head();
		if (is_insert)
			_size++;
		return ft::make_pair(node, is_insert);
	}

	iterator insert(iterator position, const value_type &value) {
		(void)position;
		return insert(value).first;
	}

	template<class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		for (; first != last; ++first)
			insert(*first);
	}

	void erase(iterator position) { erase(*position); }

	size_type erase(const key_type& key) {
		node_pointer node = _root;

		while (node) {
			if (_val_comp(key, *node->value))
				node = node->left;
			else if (_val_comp(*node->value, key))
				node = node->right;
			else
				break ;
		}
		if (node) {
			disable_head();
			node = node_type::erase_balancer(node);
			if (node == _root) {
				if (not _root->parent)
					_root = NULL;
				else
					_root = _root->parent;
			}
			_node_allocator.destroy(node);
			_node_allocator.deallocate(node, 1);
			_size--;
			while (_root and _root->parent)
				_root = _root->parent;
			enable_head();
			return 1;
		}
		return 0;
	}

	void erase(iterator first, iterator last) {
		for (; first != last;)
			erase(first++);
	}

	void swap(set &other) {
		node_pointer tmp_root = _root;
		_root = other._root;
		other._root = tmp_root;

		node_pointer tmp_head = _head;
		_head = other._head;
		other._head = tmp_head;

		size_type tmp_len = _size;
		_size = other._size;
		other._size = tmp_len;
	}

	void clear() {
		disable_head();
		if (_root) {
			_node_allocator.destroy(_root);
			_node_allocator.deallocate(_root, 1);
		}
		_root = NULL;
		enable_head();
		_size = 0;
	}// Clear content (public member function )

	/**	Observer	**/

	key_compare key_comp() {
		return key_compare();
	}

	/**	Operations **/

	iterator find (const key_type &key) {
		node_pointer node = _root;

		while (node) {
			if (_val_comp(key, *node->value))
				node = node->left;
			else if (_val_comp(*node->value, key))
				node = node->right;
			else
				return node;
		}
		return end();
	}

	const_iterator find (const key_type &key) const {
		node_pointer node = _root;

		while (node) {
			if (_val_comp(key, *node->value))
				node = node->left;
			else if (_val_comp(*node->value, key))
				node = node->right;
			else
				return node;
		}
		return end();
	}	//	Get iterator to element (public member function )

	size_type count (const key_type &key) const {
		node_pointer node = _root;

		while (node) {
			if (_val_comp(key, *node->value))
				node = node->left;
			else if (_val_comp(*node->value, key))
				node = node->right;
			else
				return 1;
		}
		return 0;
	}//	Count elements with a specific key (public member function )

	iterator lower_bound(const key_type& key) {
		node_pointer node = _root,  tmp = NULL;

		while (node) {
			if (_val_comp(*node->value, key))
				node = node->right;
			else {
				tmp = node;
				node = node->left;
			}
		}
		if (not tmp)
			return end();
		return tmp;
	}

	iterator upper_bound(const key_type& key) {
		node_pointer node = _root,  tmp = NULL;

		while (node) {
			if (not _val_comp(key, *node->value))
				node = node->right;
			else {
				tmp = node;
				node = node->left;
			}
		}
		if (not tmp)
			return end();
		return tmp;
	}

	pair<iterator,iterator> equal_range(const key_type& key) { return ft::make_pair<iterator,iterator>(lower_bound(key), upper_bound(key)); }//	Get range of equal elements (public member function )

	/**	Constructors	**/

	/*	Default constructor	*/
	explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _allocator(alloc), _node_allocator(), _val_comp(comp), _root(NULL), _size(0) {
		_head = _node_allocator.allocate(1);
		_node_allocator.construct(_head);
		_head->color = HEAD;
		enable_head();
	}

	/*	Range iterator constructor	*/
	template<class InputIterator>
	set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
	: _allocator(alloc), _node_allocator(), _val_comp(comp), _root(NULL), _size(0) {
		_head = _node_allocator.allocate(1);
		_node_allocator.construct(_head);
		_head->color = HEAD;
		for (; first != last; ++first, ++_size)
			insert(*first);
	};

	/*	Copy constructor	**/
	set(const set &other) : _allocator(other._allocator), _node_allocator(other._node_allocator), _val_comp(other._val_comp), _size(other._size) {
		_head = _node_allocator.allocate(1);
		_node_allocator.construct(_head);
		if (other._root) {
			_root = _node_allocator.allocate(1);
			_node_allocator.construct(_root, *other._root);
		}
		else
			_root = NULL;
		_head->color = HEAD;
		enable_head();
	};

	/*	Destructor	*/

	~set() {
		disable_head();
		if (_root) {
			_node_allocator.destroy(_root);
			_node_allocator.deallocate(_root, 1);
		}
		_node_allocator.destroy(_head);
		_node_allocator.deallocate(_head, 1);
	}

	/**	Assign overload	**/

	set &operator=(const set &other) {
		if (this == &other)
			return *this;
		disable_head();
		if (_root) {
			_node_allocator.destroy(_root);
			_node_allocator.deallocate(_root, 1);
		}
		_root = NULL;
		if (other._root) {
			_root = _node_allocator.allocate(1);
			_node_allocator.construct(_root, *other._root);
		}
		enable_head();
		_size = other._size;
		return *this;
	}

	/**	Non-member function	**/

	/*	Relational operators	*/
	friend bool operator==(const set &left, const set &right) {
		if (left._size == right._size)
			return ft::equal(left.begin(), left.end(), right.begin());
		else
			return false;
	}

	friend bool operator!=(const set &left, const set &right) { return !(left == right); }

	friend bool operator<(const set &left, const set &right) { return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end(), std::less<value_type>()); }

	friend bool operator<=(const set &left, const set &right) { return !(right < left); }

	friend bool operator>(const set &left, const set &right) { return right < left; }

	friend bool operator>=(const set &left, const set &right) { return !(left < right); }

};

}

namespace std{
template<class K, class compare, class alloc>
void swap(ft::set<K, compare, alloc> &x, ft::set<K, compare, alloc> &y) { x.swap(y); }
}

#endif
