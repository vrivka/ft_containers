#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <iostream>
#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"

template <class T, class Alloc = std::allocator<T> >
class vector {
public:
	typedef T											value_type;				//	The first template parameter (T)
	typedef Alloc										allocator_type;			//	The second template parameter (Alloc)	defaults to: allocator<value_type>
	typedef typename allocator_type::reference			reference ;				//	for the default allocator: value_type&
	typedef typename allocator_type::const_reference 	const_reference;		//	for the default allocator: const value_type&
	typedef typename allocator_type::pointer			pointer;				//	for the default allocator: value_type*
	typedef typename allocator_type::const_pointer		const_pointer;			//	for the default allocator: const value_type*
	typedef ft::iterator<pointer>						iterator;				//	a random access iterator to value_type	convertible to const_iterator
	typedef ft::iterator<const_pointer>					const_iterator;			//	a random access iterator to const value_type
	typedef ft::reverse_iterator<iterator>				reverse_iterator;		//	reverse_iterator<iterator>
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;	//	reverse_iterator<const_iterator>
	typedef ptrdiff_t									difference_type;		//	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
	typedef size_t										size_type;				//	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
private:
	allocator_type A;
	size_type len;
	size_type cap;
	pointer arr;
public:
	/* Iterators */

	iterator begin() { return arr; };
	const_iterator begin() const { return arr; }; //Return iterator to beginning (public member function )

	iterator end() { return arr + len; };
	const_iterator end() const { return arr + len; }; //Return iterator to end (public member function )

	reverse_iterator rbegin() { return end() - 1; };
	const_reverse_iterator rbegin() const { return end() - 1; }; //Return reverse iterator to reverse beginning (public member function )

	reverse_iterator rend() { return begin() - 1; };
	const_reverse_iterator rend() const { return begin() - 1; }; //Return reverse iterator to reverse end (public member function )

	/* Capacity */

	size_type size() const { return len; };									//	Return size (public member function )
	size_type max_size() const { return A.max_size(); };			//	Return maximum size (public member function )
	void resize(size_type n, value_type const &val = value_type()) {
		if (n < len) {
			for (size_type i = n; i < len; i++)
				A.destroy(arr + i);
		}
		else if (n > len) {
			if (n > cap)
				cap = n > cap * 2 ? n : cap * 2;
			pointer new_arr = A.allocate(cap);
			for (size_type i = 0; i < len; i++)
				A.construct(new_arr + i, arr[i]);
			for (size_type i = len; i < n; i++)
				A.construct(new_arr + i, val);
			for (size_type i = 0; i < len; i++)
				A.destroy(arr + i);
			A.deallocate(arr, cap);
			arr = new_arr;
		}
		else
			return ;
		len = n;
	};	//	Change size (public member function )
	size_type capacity() const { return cap; };								//	Return size of allocated storage capacity (public member function )
	bool empty() const { return len == 0; };								//	Test whether vector is empty (public member function )
	void reserve(size_type n) {
		if (n > cap)
			cap = n;
		else
			return ;
		pointer new_arr = A.allocate(cap);
		for (size_type i = 0; i < len; i++)
			A.construct(new_arr + i, arr[i]);
		for (size_type i = 0; i < len; i++)
			A.destroy(arr + i);
		A.deallocate(arr, cap);
		arr = new_arr;
	};										//	Request a change in capacity (public member function )

	/* Element access */

	reference operator[](size_type n) { return arr[n]; };
	const_reference operator[](size_type n) const { return arr[n]; };		//	Access element (public member function )

	reference at(size_type n) {
		if (n >= len)
			throw std::out_of_range("vector");
		return arr[n];
	};
	const_reference at(size_type n) const {
		if (n >= len)
			throw std::out_of_range("vector");
		return arr[n];
	};							//	Access element (public member function )

	reference front() { return arr[0]; };
	const_reference front() const { return arr[0]; };						//	Access first element (public member function )

	reference back() { return arr[len - 1]; };
	const_reference back() const { return arr[len - 1]; };					//	Access last element (public member function )

	/* Modifiers */

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last) {
		size_type n = 0;
		for (; first + n != last; n++);
		cap = n > cap ? n : cap;
		for (size_type i = 0; i < len; i++)
			A.destroy(arr + i);
		A.deallocate(arr, cap);
		len = cap;
		arr = A.allocate(cap);
		for (size_type i = 0; first + i != last; i++)
			A.construct(arr + i, *(first + i));
	};
	void assign(size_type n, const value_type& val) {
		cap = n > cap ? n : cap;
		for (size_type i = 0; i < len; i++)
			A.destroy(arr + i);
		A.deallocate(arr, cap);
		len = cap;
		arr = A.allocate(cap);
		for (size_type i = 0; i < len; i++)
			A.construct(arr + i, val);
	};					//	Assign vector content (public member function )

	void push_back(const value_type& val) {
		if (cap == 0) {
			A.deallocate(arr, cap);
			cap = 1;
			arr = A.allocate(cap);
		}
		if (cap == len) {
			pointer new_arr;
			size_type old_cap = cap;

			cap *= 2;
			new_arr = A.allocate(cap);
			for (size_type i = 0; i < len; i++)
				A.construct(new_arr + i, arr[i]);
			A.construct(&new_arr[len], val);
			for (size_type i = 0; i < len; i++)
				A.destroy(arr + i);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else
			A.construct(&arr[len], val);
		len += 1;
	};							//	Add element at the end (public member function )
	void pop_back() {
		A.destroy(arr + (len - 1));
		len -= 1;
	};													//	Delete last element (public member function )

	iterator insert(iterator position, const value_type& val) {
		if (cap == 0) {
			typename iterator::difference_type t = position - begin();

			A.deallocate(arr, cap);
			cap = 1;
			arr = A.allocate(cap);
			A.construct(arr + t, val);
		}
		else if (cap == len) {
			size_type old_cap = cap;
			cap *= 2;
			pointer new_arr = A.allocate(cap);

			for (size_type i = 0; arr + i != position; i++)
				A.construct(new_arr + i, arr[i]);
			A.construct(new_arr + (position - begin()), val);
			for (size_type i = position - begin(); i < len; i++)
				A.construct(new_arr + i + 1, arr[i]);
			for (size_type i = 0; i < len; i++)
				A.destroy(arr + i);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else if (position == end())
			A.construct(arr + len, val);
		else {
			size_type i = len - 1;

			A.construct(arr + len, arr[i]);
			for (; arr + i != position; i--)
				arr[i] = arr[i - 1];
			arr[i] = val;
		}
		len++;
		return arr + (position - begin());
	}; // single element (1)

	void insert (iterator position, size_type n, const value_type& val) {
		typename iterator::difference_type t = position - begin();
		if (cap == 0) {
			std::cout << t << std::endl;
			A.deallocate(arr, cap);
			cap = n;
			arr = A.allocate(cap);
			for (size_type i = 0; i < n; i++)
				A.construct(arr + t + i, val);
		}
		else if (cap == len || len + n > cap) {
			size_type old_cap = cap;
			cap = len + n > cap * 2 ? len + n : cap * 2;
			pointer new_arr = A.allocate(cap);
			size_type i = 0;
			size_type ii = 0;

			for (; arr + i != position; i++, ii++)
				A.construct(new_arr + ii, arr[i]);
			for (size_type k = 0; k < n; ii++, k++)
				A.construct(new_arr + ii, val);
			for (; i < len; ii++, i++)
				A.construct(new_arr + ii, arr[i]);
			for (i = 0; i < len; i++)
				A.destroy(arr + i);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else if (position == end())
			for (size_type i = 0; i < n; i++)
				A.construct(arr + len + i, val);
		else {
			size_type i = len - 1;

			for (size_type k = n; k > 0; k--, i--)
				A.construct(arr + len + k - 1, arr[i]);
			for (i++; i != t; i--)
				arr[i + n - 1] = arr[i - 1];
			for (size_type k = n; k > 0; k--)
				arr[i + k - 1] = val;
		}
		len += n;
	};// fill (2)

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last) {

	};// Insert elements (public member function ) range (3)

	iterator erase (iterator position) {

	};

	iterator erase (iterator first, iterator last) {

	}; //Erase elements (public member function )

	void swap(vector &x) {
		pointer tmp_arr = arr;

		arr = x.arr;
		x.arr = tmp_arr;

		size_type tmp_len = len;

		len = x.len;
		x.len = tmp_len;

		size_type tmp_cap = cap;

		cap = x.cap;
		x.cap = tmp_cap;
	};												//	Swap content (public member function )
	void clear() {
		for (size_type i = 0; i < len; i++)
			A.destroy(arr + i);
		len = 0;
	};														//	Clear content (public member function )

	/* Allocator */

	allocator_type get_allocator() const { return A; };								//	Get allocator (public member function )

	/* Constructors */

	explicit vector(const allocator_type& alloc = allocator_type()) : A(alloc), len(0), cap(0) {
		arr = A.allocate(0);
	};
	explicit vector(size_type n, const value_type &val = value_type(), const allocator_type& alloc = allocator_type()) : A(alloc), len(n), cap(n) {
		arr = A.allocate(cap);
		for (size_type i = 0; i < len; i++)
			A.construct(arr + i, val);
	};
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : A(alloc), len(0), cap(0) {
		for (; first + len != last; ++cap, ++len);
		arr = A.allocate(cap);
		for (size_type i = 0; first + i != last; ++i)
			A.construct(&arr[i], *(first + i));
	};
	vector(const vector& x) : A(x.A), len(x.len), cap(x.cap) {
		arr = A.allocate(cap);
		for (size_type i = 0; i < len; i++)
			A.construct(&arr[i], x.arr[i]);
	};

	/* Destructor */

	~vector() {
		for (size_type i = 0; i < len; i++)
			A.destroy(&arr[i]);
		A.deallocate(arr, cap);
	}

	/* Non-member function overloads */

	template <class V, class alloc>
	friend void swap(vector<V,alloc> &x, vector<V,alloc> &y) { x.swap(y); };

	/* relational operators */

	friend bool operator==(	const vector<T,Alloc> &lhs,	const vector<T,Alloc> &rhs) {
		if (lhs.len == rhs.len) {
			for (size_type i = 0; i < lhs.len; i++) {
				if (lhs.arr[i] != rhs.arr[i])
					return false;
			}
			return true;
		}
		return false;
	}
	friend bool operator!=(	const vector<T,Alloc> &lhs,	const vector<T,Alloc> &rhs) { return !(lhs == rhs); }
	friend bool operator<(	const vector<T,Alloc> &lhs,	const vector<T,Alloc> &rhs) {
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
	friend bool operator<=(	const vector<T,Alloc> &lhs,	const vector<T,Alloc> &rhs) { return !(rhs < lhs); }
	friend bool operator>(	const vector<T,Alloc> &lhs,	const vector<T,Alloc> &rhs) { return rhs < lhs; }
	friend bool operator>=(	const vector<T,Alloc> &lhs,	const vector<T,Alloc> &rhs) { return !(lhs < rhs); } // Relational operators for vector (function template )
};

#endif
