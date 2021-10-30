#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"

namespace ft {
template<class T, class Alloc = std::allocator<T> >
class vector {
public:
	typedef T														value_type;				//	The first template parameter (T)
	typedef Alloc													allocator_type;			//	The second template parameter (Alloc) defaults to: allocator<value_type>
	typedef typename allocator_type::reference						reference;				//	for the default allocator: value_type&
	typedef typename allocator_type::const_reference				const_reference;		//	for the default allocator: const value_type&
	typedef typename allocator_type::pointer						pointer;				//	for the default allocator: value_type*
	typedef typename allocator_type::const_pointer					const_pointer;			//	for the default allocator: const value_type*
	typedef ft::vec_iterator<pointer>								iterator;				//	a random access iterator to value_type convertible to const_iterator
	typedef ft::vec_iterator<const_pointer>							const_iterator;			//	a random access iterator to const value_type
	typedef ft::reverse_iterator<iterator>						reverse_iterator;		//	reverse_iterator<iterator>
	typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;	//	reverse_iterator<const_iterator>
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;		//	a signed integral type, identical to: iterator_traits<iterator>::difference_type usually the same as ptrdiff_t
	typedef typename allocator_type::size_type						size_type;				//	an unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
private:
	allocator_type	A;
	size_type		len;
	size_type		cap;
	pointer			arr;
public:
	///*	Iterators	*/

	/*	Return iterator to beginning	*/
	iterator				begin() { return arr; }

	const_iterator			begin() const { return arr; }

	/*	Return iterator to end	*/
	iterator				end() { return arr + len; }

	const_iterator			end() const { return arr + len; }

	/*	Return reverse iterator to reverse beginning	*/
	reverse_iterator		rbegin() { return end() - 1; }

	const_reverse_iterator	rbegin() const { return end() - 1; }

	/*	Return reverse iterator to reverse end	*/
	reverse_iterator		rend() { return begin() - 1; }

	const_reverse_iterator	rend() const { return begin() - 1; }

	///*	Capacity	*/

	/*	Return size	*/
	size_type	size() const { return len; }

	/*	Return maximum size	*/
	size_type	max_size() const { return A.max_size(); }

	/*	Change size	*/
	void		resize(size_type n) {
		size_type i;

		if (n < len) {
			for (i = len; i > n; i--)
				A.destroy(arr + i - 1);
		}
		else if (n > len) {
			size_type old_cap = cap;
			if (n > cap)
				cap = n > cap * 2 ? n : cap * 2;
			pointer new_arr = A.allocate(cap);
			for (i = len; i < n; i++)
				A.construct(new_arr + i);
			for (i = len; i > 0; i--)
				A.construct(new_arr + i - 1, arr[i - 1]);
			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else
			return;
		len = n;
	}

	void		resize(size_type n, value_type const &val) {
		size_type i;

		if (n < len) {
			for (i = len; i > n; i--)
				A.destroy(arr + i - 1);
		}
		else if (n > len) {
			size_type old_cap = cap;
			if (n > cap)
				cap = n > cap * 2 ? n : cap * 2;
			pointer new_arr = A.allocate(cap);
			for (i = len; i < n; i++)
				A.construct(new_arr + i, val);
			for (i = len; i > 0; i--)
				A.construct(new_arr + i - 1, arr[i - 1]);
			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else
			return;
		len = n;
	}

	/*	Return size of allocated storage capacity	*/
	size_type	capacity() const { return cap; }

	/*	Test whether vector is empty	*/
	bool		empty() const { return len == 0; }

	/*	Request a change in capacity	*/
	void		reserve(size_type n) {
		if (n < cap)
			return;
		size_type old_cap = cap, i;
		cap = n;
		pointer new_arr = A.allocate(cap);
		for (i = len; i > 0; i--)
			A.construct(new_arr + i - 1, arr[i - 1]);
		for (i = len; i > 0; i--)
			A.destroy(arr + i - 1);
		A.deallocate(arr, old_cap);
		arr = new_arr;
	}

	///*	Element access	*/

	/*	Access element	*/
	reference		operator[](size_type n) { return arr[n]; }

	const_reference	operator[](size_type n) const { return arr[n]; }

	/*	Access element	*/
	reference		at(size_type n) { return n >= len ? throw std::out_of_range("vector") : arr[n]; }

	const_reference	at(size_type n) const { return n >= len ? throw std::out_of_range("vector") : arr[n]; }

	/*	Access first element	*/
	reference		front() { return arr[0]; }

	const_reference	front() const { return arr[0]; }

	/*	Access last element	*/
	reference		back() { return arr[len - 1]; }

	const_reference	back() const { return arr[len - 1]; }

	///*	Modifiers	*/

	/*	Assign vector content	*/
	template<class InputIterator>
	void assign(InputIterator first, InputIterator last) {
		size_type n = last - first, i;

		if (cap >= n) {
			for (i = 0; i < n; i++)
				arr[i] = *(first + i);
			for (i = len; i > n; i--)
				A.destroy(arr + i - 1);
		}
		else {
			size_type old_cap = cap;
			cap = n;
			pointer new_arr = A.allocate(cap);

			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			for (i = 0; i < n; i++)
				A.construct(new_arr + i, *(first + i));
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		len = n;
	}

	void assign(size_type n, const value_type &val) {
		size_type i;
		if (cap >= n) {
			for (i = 0; i < n; i++)
				arr[i] = val;
			for (i = len; i > n; i--)
				A.destroy(arr + i - 1);
		}
		else {
			size_type old_cap = cap;
			cap = n;
			pointer new_arr = A.allocate(cap);

			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			for (i = 0; i < n; i++)
				A.construct(new_arr + i, val);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		len = n;
	}

	/*	Add element at the end	*/
	void push_back(const value_type &val) {
		if (cap == 0) {
			A.deallocate(arr, cap);
			cap = 1;
			arr = A.allocate(cap);
			A.construct(arr + len, val);
		}
		else if (cap == len) {
			size_type old_cap = cap, i;
			cap *= 2;
			pointer new_arr = A.allocate(cap);
			A.construct(new_arr + len, val);
			for (i = len; i > 0; i--)
				A.construct(new_arr + i - 1, arr[i - 1]);
			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else
			A.construct(arr + len, val);
		len++;
	}

	/*	Delete last element	*/
	void pop_back() { A.destroy(arr + len - 1); len--; }

	/*	Insert elements	*/
	iterator insert(iterator position, const value_type &val) {
		size_type t = position - begin();

		if (cap == 0) {
			A.deallocate(arr, cap);
			cap = 1;
			arr = A.allocate(cap);
			A.construct(arr + t, val);
		}
		else if (cap == len) {
			size_type old_cap = cap, i;
			cap *= 2;
			pointer new_arr = A.allocate(cap);
			A.construct(new_arr + t, val);
			for (i = t; i > 0; i--)
				A.construct(new_arr + i - 1, arr[i - 1]);
			for (i = t; i < len; i++)
				A.construct(new_arr + i + 1, arr[i]);
			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else if (t == len)
			A.construct(arr + len, val);
		else {
			size_type i = len - 1;

			A.construct(arr + len, arr[i]);
			for (; i != t; i--)
				arr[i] = arr[i - 1];
			arr[i] = val;
		}
		len++;
		return arr + t;
	}					// single element

	void insert(iterator position, size_type n, const value_type &val) {
		size_type t = position - begin();

		if (cap == 0) {
			A.deallocate(arr, cap);
			cap = n;
			arr = A.allocate(cap);
			for (size_type i = 0; i < n; i++)
				A.construct(arr + t + i, val);
		}
		else if (cap == len || len + n > cap) {
			size_type old_cap = cap, i, k = t + n;
			cap = len + n > cap * 2 ? len + n : cap * 2;
			pointer new_arr = A.allocate(cap);
			for (i = t; i < k; i++)
				A.construct(new_arr + i, val);
			for (i = t; i > 0; i--)
				A.construct(new_arr + i - 1, arr[i - 1]);
			for (i = t; i < len; i++)
				A.construct(new_arr + i + n, arr[i]);
			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else if (t == len)
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
	}		// fill

	template<class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last) {
		size_type t = position - begin(), n = last - first;

		if (cap == 0) {
			A.deallocate(arr, cap);
			cap = n;
			arr = A.allocate(cap);
			for (size_type i = 0; i < n; i++)
				A.construct(arr + t + i, first[i]);
		}
		else if (cap == len || len + n > cap) {
			size_type old_cap = cap, i, ii = 0, k = t + n;
			cap = len + n > cap * 2 ? len + n : cap * 2;
			pointer new_arr = A.allocate(cap);

			for (i = t; i < k; i++, ii++)
				A.construct(new_arr + i, first[ii]);
			for (i = t; i > 0; i--)
				A.construct(new_arr + i - 1, arr[i - 1]);
			for (i = t; i < len; i++)
				A.construct(new_arr + i + n, arr[i]);
			for (i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			A.deallocate(arr, old_cap);
			arr = new_arr;
		}
		else if (t == len)
			for (size_type i = 0; i < n; i++)
				A.construct(arr + len + i, first[i]);
		else {
			size_type i = len - 1;
			size_type ii = 0;

			for (size_type k = n; k > 0; k--, i--)
				A.construct(arr + len + k - 1, arr[i]);
			for (i++; i != t; i--)
				arr[i + n - 1] = arr[i - 1];
			for (size_type k = n; k > 0; k--, ii++)
				arr[i + k - 1] = first[ii];
		}
		len += n;
	}	// range

	/*	Erase elements	*/
	iterator erase(iterator position) {
		for (size_type t = position - begin(); t < len - 1; t++)
			arr[t] = arr[t + 1];
		A.destroy(arr + len - 1);
		len--;
		return position;
	}

	iterator erase(iterator first, iterator last) {
		size_type i = last - first, t = last - begin() - 1, k = first - begin();

		for (; t < len - 1; t++, k++)
			arr[k] = arr[t + 1];
		for (size_type d = 0; d < i; d++)
			A.destroy(arr + len - 1 - d);
		len -= i;
		return last;
	}

	/*	Swap content	*/
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
	}

	/*	Clear content	*/
	void clear() {
		for (size_type i = len; i > 0; i--)
			A.destroy(arr + i - 1);
		len = 0;
	}

	///*	Allocator	*/

	/*	Get allocator	*/
	allocator_type get_allocator() const { return A; }

	///*	Constructors	*/

	/*	Default constructor	*/
	explicit vector(const allocator_type &alloc = allocator_type()) : A(alloc), len(0), cap(0) { arr = A.allocate(0); }

	/*	Size fill constructor	*/
	explicit vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type()) : A(alloc), len(n), cap(n) {
		arr = A.allocate(cap);
		for (size_type i = 0; i < len; i++)
			A.construct(arr + i, val);
	}

	/*	Size constructor	*/
	explicit vector(size_type n, const allocator_type &alloc = allocator_type()) : A(alloc), len(n), cap(n) {
		arr = A.allocate(cap);
		for (size_type i = 0; i < len; i++)
			A.construct(arr + i);
	}

	/*	Iterator constructor	*/
	template<class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : A(alloc) {
		size_type n = last - first, i;
		cap = n;
		len = n;
		arr = A.allocate(cap);
		for (i = 0; first + i != last; ++i)
			A.construct(arr + i, *(first + i));
	}

	/*	Copy constructor	*/
	vector(const vector &x) : A(x.A), len(x.len), cap(x.cap) {
		arr = A.allocate(cap);
		for (size_type i = 0; i < len; i++)
			A.construct(&arr[i], x.arr[i]);
	}

	///*	Destructor	*/

	~vector() {
		for (size_type i = len; i > 0; i--)
			A.destroy(arr + i - 1);
		A.deallocate(arr, cap);
	}

	///*	Assign overload	*/

	vector &operator=(const vector &other) {
		if (this == &other)
			return *this;
		if (len >= other.len) {
			for (size_type i = 0; i < other.len; i++)
				arr[i] = other.arr[i];
			for (size_type i = len; i > other.len; i--)
				A.destroy(arr + i - 1);
			len = other.len;
		}
		else {
			for (size_type i = len; i > 0; i--)
				A.destroy(arr + i - 1);
			A.deallocate(arr, cap);
			cap = other.cap;
			len = other.len;
			arr = A.allocate(cap);
			for (size_type i = 0; i < len; i++)
				A.construct(arr + i, other.arr[i]);
		}
		return *this;
	}

	///*	Non-member function overloads	*/

	template<class V, class alloc>
	friend void swap(vector<V, alloc> &x, vector<V, alloc> &y) { x.swap(y); }

	/*	Relational operators	*/
	friend bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		if (lhs.len == rhs.len) {
			for (size_type i = 0; i < lhs.len; i++) {
				if (lhs.arr[i] != rhs.arr[i])
					return false;
			}
			return true;
		}
		return false;
	}

	friend bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }

	friend bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
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

	friend bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(rhs < lhs); }

	friend bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return rhs < lhs; }

	friend bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs); }
};

}

#endif
