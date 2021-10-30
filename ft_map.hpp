#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "ft_pair.hpp"
#include "RBTree.hpp"
#include "RBNode.hpp"

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
class map {
public:
	typedef Key key_type;//	The first template parameter (Key)
	typedef T mapped_type;//	The second template parameter (T)
	typedef ft::pair<const key_type, mapped_type> value_type;//	pair<const key_type,mapped_type>
	typedef Compare key_compare;//	The third template parameter (Compare)	defaults to: less<key_type>
//	typedef  value_compare;//	Nested function class to compare elements	see value_comp
	typedef Alloc allocator_type;//	The fourth template parameter (Alloc)	defaults to: allocator<value_type>
	typedef typename allocator_type::reference reference;//	allocator_type::reference	for the default allocator: value_type&
	typedef typename allocator_type::const_reference const_reference;//	allocator_type::const_reference	for the default allocator: const value_type&
	typedef typename allocator_type::pointer pointer;//	allocator_type::pointer	for the default allocator: value_type*
	typedef typename allocator_type::const_pointer const_pointer;//	allocator_type::const_pointer	for the default allocator: const value_type*
//	typedef iterator;//	a bidirectional iterator to value_type	convertible to const_iterator
//	typedef const_iterator;//	a bidirectional iterator to const value_type
//	typedef reverse_iterator;//	reverse_iterator<iterator>
//	typedef const_reverse_iterator;//	reverse_iterator<const_iterator>
//	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;//	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
	typedef typename allocator_type::size_type size_type;//	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
private:
	RBTree<pointer, key_compare, allocator_type> arr;
	size_type len;
	size_type cap;
public:
	///*	Constructors	*/

	explicit map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) {}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());

	map (const map &x);
};


#endif
