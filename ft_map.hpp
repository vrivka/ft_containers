#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "RBNode.hpp"
#include <memory>
#include "ft_pair.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_tree_iterator.hpp"
#include "ft_utilities.hpp"

namespace ft {
template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
class map {
public:
	typedef Key															key_type;				//	The first template parameter (Key)
	typedef T															mapped_type;			//	The second template parameter (T)
	typedef pair<const key_type, mapped_type>							value_type;				//	Store type (pair<const key_type,mapped_type>)
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
	typedef typename allocator_type::size_type							size_type;				//	An unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
private:
	allocator_type		_allocator;
	node_allocator_type	_node_allocator;
	value_compare		_val_comp;
	node_pointer		_root;
	node_pointer		_head;
	size_type			_size;

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

	value_type *alloc_val(const key_type &key) {
		pointer val_ptr = _allocator.allocate(1);
		_allocator.construct(val_ptr, key, mapped_type());
		return val_ptr;
	}

	node_pointer create_node(node_pointer node, node_pointer parent, pointer val_ptr) {
		node = _node_allocator.allocate(1);
		_node_allocator.construct(node);
		node->parent = parent;
		node->value = val_ptr;
		return node;
	}

	node_pointer create_node(node_pointer node, node_pointer parent, const value_type &value) {
		node = _node_allocator.allocate(1);
		_node_allocator.construct(node);
		node->parent = parent;
		node->value = _allocator.allocate(1);
		_allocator.construct(node->value, value);
		return node;
	}

	ft::pair<iterator,bool> insert(pointer val_ptr) {
		node_pointer node = _root;
		bool b = false;

		if (node) {
			disable_head();
			while (node) {
				if (_val_comp(*val_ptr, *node->value)) {
					if (node->left)
						node = node->left;
					else {
						node->left = create_node(node->left, node, val_ptr);
						node = node->left;
						node_type::balance(node);
						b = true;
						break ;
					}
				} else if (_val_comp(*node->value, *val_ptr)) {
					if (node->right)
						node = node->right;
					else {
						node->right = create_node(node->right, node, val_ptr);
						node = node->right;
						node_type::balance(node);
						b = true;
						break ;
					}
				} else break;
			}
		} else {
			_root = create_node(_root, NULL, val_ptr);
			node_type::balance(_root);
			enable_head();
			b = true;
			_size++;
			return ft::make_pair(_root, b);
		}
		while (_root->parent)
			_root = _root->parent;
		enable_head();
		if (b)
			_size++;
		return ft::make_pair(node, b);
	}

public:

	/**	Iterators	**/

	iterator begin() { return _root ? _root->min(_root) : _head; }
	const_iterator begin() const { return _root ? iterator(_root->min(_root)) : end(); }

	iterator end() { return _head; }
	const_iterator end() const { return iterator(_head); }

	reverse_iterator rbegin() { return end(); }
	const_reverse_iterator rbegin() const { return end(); }

	reverse_iterator rend() { return begin(); }
	const_reverse_iterator rend() const { return begin(); }

	/**	Capacity	**/

	bool empty() const { return _size == 0; }

	size_type size() const { return _size; }

	size_type max_size() const { return _node_allocator.max_size(); }

	/**	Element access	**/

	mapped_type &operator[](const key_type &key) {
		node_pointer node = _root;
		key_compare k_comp;

		while (node) {
			if (k_comp(key, node->value->first))
				node = node->left;
			else if (k_comp(node->value->first, key))
				node = node->right;
			else
				return node->value->second;
		}
		pointer val_ptr = alloc_val(key);
		pair<iterator,bool> ret = insert(val_ptr);
		return ret.first->second;
	}

	mapped_type &at(const key_type &key) {
		node_pointer node = _root;
		key_compare k_comp;
		while (node) {
			if (k_comp(key, node->value->first))
				node = node->left;
			else if (k_comp(node->value->first, key))
				node = node->right;
			else
				return node->value->second;
		}
		throw std::out_of_range("map::at:  key not found");
	}
	const mapped_type &at(const key_type& key) const {
		node_pointer node = _root;
		key_compare k_comp;
		while (node) {
			if (k_comp(key, node->value->first))
				node = node->left;
			else if (k_comp(node->value->first, key))
				node = node->right;
			else
				return node->value->second;
		}
		throw std::out_of_range("map::at:  key not found");
	}

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

	void erase(iterator position) { erase(position->first); }

	size_type erase(const key_type& key) {
		node_pointer node = _root;
		key_compare k_comp;

		while (node) {
			if (k_comp(key, node->value->first))
				node = node->left;
			else if (k_comp(node->value->first, key))
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

	void swap(map &other) {
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
	}

	/**	Observer	**/

	key_compare key_comp() { return key_compare(); }
	key_compare key_comp() const { return key_compare(); }

	value_compare value_comp() { return value_compare(key_compare()); }
	value_compare value_comp() const { return value_compare(key_compare()); }

	/**	Operations **/

	iterator find(const key_type &key) {
		node_pointer node = _root;
		key_compare key_comp;
		while (node) {
			if (key_comp(key, node->value->first))
				node = node->left;
			else if (key_comp(node->value->first, key))
				node = node->right;
			else
				return node;
		}
		return _head;
	}

	const_iterator find(const key_type &key) const {
		node_pointer node = _root;
		key_compare com;
		while (node) {
			if (com(key, node->value->first))
				node = node->left;
			else if (com(node->value->first, key))
				node = node->right;
			else
				return iterator(node);
		}
		return end();
	}

	size_type count(const key_type &key) const {
		node_pointer node = _root;
		key_compare k_comp;
		while (node) {
			if (k_comp(key, node->value->first))
				node = node->left;
			else if (k_comp(node->value->first, key))
				node = node->right;
			else
				return 1;
		}
		return 0;
	}

	iterator lower_bound(const key_type& key) {
		node_pointer node = _root,  tmp = NULL;
		key_compare k_comp;

		while (node) {
			if (k_comp(node->value->first, key))
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

	const_iterator lower_bound(const key_type &key) const {
		node_pointer node = _root,  tmp = NULL;
		key_compare k_comp;

		while (node) {
			if (k_comp(node->value->first, key))
				node = node->right;
			else {
				tmp = node;
				node = node->left;
			}
		}
		if (not tmp)
			return end();
		return iterator(tmp);
	}

	iterator upper_bound(const key_type& key) {
		node_pointer node = _root,  tmp = NULL;
		key_compare k_comp;

		while (node) {
			if (not k_comp(key, node->value->first))
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

	const_iterator upper_bound(const key_type& key) const {
		node_pointer node = _root,  tmp = NULL;
		key_compare k_comp;

		while (node) {
			if (not k_comp(key, node->value->first))
				node = node->right;
			else {
				tmp = node;
				node = node->left;
			}
		}
		if (not tmp)
			return end();
		return iterator(tmp);
	}

	pair<const_iterator,const_iterator> equal_range(const key_type& key) const { return ft::make_pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key)); }

	pair<iterator,iterator> equal_range(const key_type& key) { return ft::make_pair<iterator,iterator>(lower_bound(key), upper_bound(key)); }

	/**	Constructors	**/

	explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _allocator(alloc), _node_allocator(), _val_comp(comp), _root(NULL), _size(0) {
		_head = _node_allocator.allocate(1);
		_node_allocator.construct(_head);
		_head->color = HEAD;
		enable_head();
	}

	template<class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
	: _allocator(alloc), _node_allocator(), _val_comp(comp), _root(NULL), _size(0) {
		_head = _node_allocator.allocate(1);
		_node_allocator.construct(_head);
		_head->color = HEAD;
		for (; first != last; ++first)
			insert(*first);
	}

	map(const map &other) : _allocator(other._allocator), _node_allocator(other._node_allocator), _val_comp(other._val_comp), _size(other._size) {
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
	}

	/**	Destructor	**/

	~map() {
		disable_head();
		if (_root) {
			_node_allocator.destroy(_root);
			_node_allocator.deallocate(_root, 1);
		}
		_node_allocator.destroy(_head);
		_node_allocator.deallocate(_head, 1);
	}

	/**	Assign overload	**/

	map &operator=(const map &other) {
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

	friend bool operator==(const map &left, const map &rhs) {
		if (left._size == rhs._size)
			return ft::equal(left.begin(), left.end(), rhs.begin());
		else
			return false;
	}

	friend bool operator!=(const map &left, const map &right) { return !(left == right); }

	friend bool operator<(const map &left, const map &right) { return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end(), std::less<value_type>()); }

	friend bool operator<=(const map &left, const map &right) { return !(right < left); }

	friend bool operator>(const map &left, const map &right) { return right < left; }

	friend bool operator>=(const map &left, const map &right) { return !(left < right); }

};

}

namespace std{
template<class K, class V, class compare, class alloc>
void swap(ft::map<K, V, compare, alloc> &left, ft::map<K, V, compare, alloc> &right) { left.swap(right); }
}
#endif
