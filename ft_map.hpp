#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "ft_pair.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_tree_iterator.hpp"
#include "RBTree.hpp"
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
		friend class map;
	protected:
		key_compare comp;
		value_compare(key_compare c) : comp(c) {}
	public:
		bool operator()(const value_type &x, const value_type &y) const {
			return comp(x.first, y.first);
		}
	};														//	Nested function class to compare elements
	typedef Alloc												allocator_type;			//	The fourth template parameter (Alloc)
private:
	typedef RBTree<value_type , value_compare, allocator_type>	tree_type;				//	Red-Black tree type
	typedef typename tree_type::node_allocator_type				node_allocator_type;	//	Red-Black tree node typer
public:
	typedef value_type&											reference;				//	allocator_type::reference for the default allocator
	typedef const value_type&									const_reference;		//	allocator_type::const_reference	for the default allocator
	typedef typename allocator_type::pointer					pointer;				//	allocator_type::pointer	for the default allocator
	typedef typename allocator_type::const_pointer				const_pointer;			//	allocator_type::const_pointer for the default allocator
	typedef typename tree_type::const_iterator					const_iterator;			//	A bidirectional iterator to const value_type
	typedef typename tree_type::iterator						iterator;				//	A bidirectional iterator to value_type convertible to const_iterator
	typedef reverse_iterator<const_iterator>					const_reverse_iterator;	//	Constant reverse iterator
	typedef reverse_iterator<iterator>							reverse_iterator;		//	Reverse iterator
	typedef typename iterator_traits<iterator>::difference_type	difference_type;		//	A signed integral type, identical to: iterator_traits<iterator>::difference_type usually the same as ptrdiff_t
	typedef typename allocator_type::size_type					size_type;				//	an unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
private:
	allocator_type A;
	value_compare comp;
	tree_type tree;
	size_type len;
public:
	void print() { tree.print(); }

	///*	Iterators	*/
	iterator begin() { return tree.begin(); }

	const_iterator begin() const { return tree.begin(); }

	iterator end() { return tree.end(); }

	const_iterator end() const { return tree.end(); }

	reverse_iterator rbegin() { return tree.rbegin(); }

	const_reverse_iterator rbegin() const { return tree.rbegin(); }

	reverse_iterator rend() { return tree.rend(); }

	const_reverse_iterator rend() const { return tree.rend(); }

	///*	Capacity	*/

	bool empty() const { return len == 0; }

	size_type size() const { return len; }

	size_type max_size() const { return node_allocator_type().max_size(); }

	///*	Element access	*/

	mapped_type &operator[](const key_type &k) {
		iterator it = find(k);
		if (it != end())
			return it->second;
		else {
			pair<iterator, bool> added = tree.insert(make_pair(k,mapped_type()));
			return added.first->second;
		}
	}

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

	/**	Operations **/
	iterator find (const key_type &k) {
		return tree.search(pair<key_type, mapped_type>(k, mapped_type()));
	};
	const_iterator find (const key_type& k) const {
		return tree.search(k);
	};	//	Get iterator to element (public member function )
//	Count elements with a specific key (public member function )
//	Return iterator to lower bound (public member function )
//	Return iterator to upper bound (public member function )
//	Get range of equal elements (public member function )

	///*	Constructors	*/

	/*	Default constructor	*/
	explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), comp(comp), tree(), len(0) {
		tree.comp = &this->comp;
	}

	/*	Range iterator constructor	*/
	template<class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : A(alloc), comp(comp), tree(), len(0) {
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
		return *this;
	};
};

}

#endif
