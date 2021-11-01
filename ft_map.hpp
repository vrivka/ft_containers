#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "ft_pair.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_tree_iterator.hpp"
#include "RBTree.hpp"
#include "RBNode.hpp"

namespace ft {
template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
public:
	typedef Key key_type;//	The first template parameter (Key)
	typedef T mapped_type;//	The second template parameter (T)
	typedef ft::pair<const key_type, mapped_type> value_type;//	pair<const key_type,mapped_type>
	typedef Compare key_compare;//	The third template parameter (Compare)	defaults to: less<key_type>
//	typedef  value_compare;//	Nested function class to compare elements	see value_comp
	typedef Alloc allocator_type;//	The fourth template parameter (Alloc)	defaults to: allocator<value_type>
	typedef RBTree<value_type, key_compare, allocator_type> tree_type;
	typedef typename allocator_type::reference reference;//	allocator_type::reference	for the default allocator: value_type&
	typedef typename allocator_type::const_reference const_reference;//	allocator_type::const_reference	for the default allocator: const value_type&
	typedef typename allocator_type::pointer pointer;//	allocator_type::pointer	for the default allocator: value_type*
	typedef typename allocator_type::const_pointer const_pointer;//	allocator_type::const_pointer	for the default allocator: const value_type*
	typedef typename tree_type::iterator iterator;//	a bidirectional iterator to value_type convertible to const_iterator
	typedef typename tree_type::const_iterator const_iterator;//	a bidirectional iterator to const value_type
	typedef ft::reverse_iterator<iterator> reverse_iterator;//	reverse_iterator<iterator>
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;//	reverse_iterator<const_iterator>
//	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;//	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
	typedef typename allocator_type::size_type size_type;//	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
private:
	typedef typename tree_type::node_allocator_type node_allocator_type;
	allocator_type A;
	key_compare comp;
	tree_type tree;
	size_type len;
public:
	void print() { tree.print(); }

	///*	Iterators	*/
	iterator begin() { return tree.begin(); }

	const_iterator begin() const { return tree.begin(); }

	iterator end() { return tree.end(); }

	const_iterator end() const { return tree.end(); }

	///*	Capacity	*/

	bool empty() const { return len == 0; }
	size_type size() const { return len; }
	size_type max_size() const { return node_allocator_type().max_size(); }

	///*	Element access	*/

//	mapped_type &operator[] (const key_type& k) {}

	///*	Modifier	*/

	ft::pair<iterator,bool> insert(const value_type &val) {
		ft::pair<iterator,bool> ret = tree.insert(val);
		if (ret.second)
			len++;
		return ret;
	}

//	iterator insert (iterator position, const value_type &val) {}
//	template <class InputIterator>
//	void insert (InputIterator first, InputIterator last) {}

	///*	Constructors	*/

	/*	Default constructor	*/
	explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), comp(comp), tree(), len(0) {
		tree.A = &A;
		tree.comp = &this->comp;
	}

	/*	Range iterator constructor	*/
	template<class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), comp(comp), tree(), len(0) {
		tree.A = &A;
		tree.comp = &this->comp;
		for (; first != last; first++, len++)
			tree.insert(*first);
	};

	/*	Copy constructor	*/
	map(const map &x) : A(x.A), comp(x.comp), tree(x.tree), len(x.len) {};

	///*	Destructor	*/

	~map() {}

	///*	Assign overload	*/
	map &operator=(const map &x) {
		if (this == &x)
			return *this;
		this->A = x.A;
		this->comp = x.comp;
		this->tree = x.tree;
		this->len = x.len;
		this->cap = x.cap;
		return *this;
	};
};

}

#endif
