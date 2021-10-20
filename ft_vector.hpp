#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <iostream>

//template<class T, class Category = std::random_access_iterator_tag>
//class iterator : public std::iterator<Category, T> {
//	typedef Category iterator_category;	//	the first template parameter (Category)
//	typedef T value_type;				//	the second template parameter (T)
//	typedef ptrdiff_t difference_type;	//	the third template parameter (Distance)	defaults to: ptrdiff_t
//	typedef T* pointer;					//	the fourth template parameter (Pointer)	defaults to: T*
//	typedef T& reference;				//	the fifth template parameter (Reference)	defaults to: T&
//};

template <class T, class Alloc = std::allocator<T> >
class vector {
public:
	typedef T value_type;												//	The first template parameter (T)
	typedef Alloc allocator_type;										//	The second template parameter (Alloc)	defaults to: allocator<value_type>
	typedef value_type& reference ;				//	for the default allocator: value_type&
	typedef const value_type& const_reference;	//	for the default allocator: const value_type&
	typedef value_type* pointer;					//	for the default allocator: value_type*
	typedef const value_type* const_pointer;		//	for the default allocator: const value_type*
	//typedef		iterator;//	a random access iterator to value_type	convertible to const_iterator
	//typedef 		const_iterator;//	a random access iterator to const value_type
	//typedef		reverse_iterator;//	reverse_iterator<iterator>
	//typedef		const_reverse_iterator;//	reverse_iterator<const_iterator>
	typedef ptrdiff_t difference_type;									//	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
	typedef size_t size_type;											//	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

	/* Iterators */

	//iterator begin();
	//const_iterator begin() const; //Return iterator to beginning (public member function )

	//iterator end();
	//const_iterator end() const; //Return iterator to end (public member function )

	//reverse_iterator rbegin();
	//const_reverse_iterator rbegin() const; //Return reverse iterator to reverse beginning (public member function )

	//reverse_iterator rend();
	//const_reverse_iterator rend() const; //Return reverse iterator to reverse end (public member function )

	/* Capacity */

//	size_type size() const {};//	Return size (public member function )
//	size_type max_size() const;//	Return maximum size (public member function )
//	void resize(size_type n, value_type val = value_type());//	Change size (public member function )
//	size_type capacity() const;//	Return size of allocated storage capacity (public member function )
//	bool empty() const;//	Test whether vector is empty (public member function )
//	void reserve(size_type n);//	Request a change in capacity (public member function )
//
//	/* Element access */
//
//	reference operator[](size_type n);
//	const_reference operator[](size_type n) const;//	Access element (public member function )
//
//	reference at(size_type n);
//	const_reference at(size_type n) const;//	Access element (public member function )
//
//	reference front();
//	const_reference front() const;//	Access first element (public member function )
//
//	reference back();
//	const_reference back() const;//	Access last element (public member function )
//
//	/* Modifiers */
//
//	template <class InputIterator>
//	void assign(InputIterator first, InputIterator last); //range (1)
//
//	void assign(size_type n, const value_type& val); //Assign vector content (public member function ) fill (2)
//
//	void push_back(const value_type& val);//	Add element at the end (public member function )
//	void pop_back();//	Delete last element (public member function )
//
//
//	iterator insert (iterator position, const value_type& val);// single element (1)
//	void insert (iterator position, size_type n, const value_type& val);// fill (2)
//	template <class InputIterator>
//	void insert (iterator position, InputIterator first, InputIterator last);// Insert elements (public member function ) range (3)
//
//	iterator erase (iterator position);
//	iterator erase (iterator first, iterator last); //Erase elements (public member function )
//
//	void swap(vector& x);//	Swap content (public member function )
//	void clear();//	Clear content (public member function )
//
//	/* Allocator */
//
//	allocator_type get_allocator() const;//	Get allocator (public member function )
//
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
		for (int i = 0; i < len; i++)
			A.construct(&arr[i], x.arr[i]);
	};

	/* Destructor */

	~vector() {
		for (int i = 0; i < len; i++)
			A.destroy(&arr[i]);
		A.deallocate(arr, len);
	}

	/* Non-member function overloads */

	/* relational operators */

//	friend bool operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
//
//	}//	(1)
//	friend bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
//
//	}//	(2)
//	friend bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
//
//	}//	(3)
//	friend bool operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
//
//	}//	(4)
//	friend bool operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
//
//	}//	(5)
//	friend bool operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
//
//	}// Relational operators for vector (function template ) (6)
value_type *arr;
private:
	allocator_type A;
	size_type len;
	size_type cap;
};

#endif
