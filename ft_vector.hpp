#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "ft_vec_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_utilities.hpp"

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
	typedef vec_iterator<const_pointer>									const_iterator;			//	a random access iterator to const value_type
	typedef vec_iterator<pointer>											iterator;				//	a random access iterator to value_type convertible to const_iterator
	typedef reverse_iterator<const_iterator>						const_reverse_iterator;	//	reverse_iterator<const_iterator>
	typedef reverse_iterator<iterator>								reverse_iterator;		//	reverse_iterator<iterator>
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;		//	a signed integral type, identical to: iterator_traits<iterator>::difference_type usually the same as ptrdiff_t
	typedef typename allocator_type::size_type						size_type;				//	an unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t
private:
	allocator_type	_allocator;
	size_type		_size;
	size_type		_capacity;
	pointer			_pointer;

public:
	/**	Iterators	**/

	/*	Return iterator to beginning	*/
	iterator				begin() { return _pointer; }

	const_iterator			begin() const { return _pointer; }

	/*	Return iterator to end	*/
	iterator				end() { return _pointer + _size; }

	const_iterator			end() const { return _pointer + _size; }

	/*	Return reverse iterator to reverse beginning	*/
	reverse_iterator		rbegin() { return end(); }

	const_reverse_iterator	rbegin() const { return end(); }

	/*	Return reverse iterator to reverse end	*/
	reverse_iterator		rend() { return begin(); }

	const_reverse_iterator	rend() const { return begin(); }

	/**	Capacity	**/

	/*	Return size	*/
	size_type	size() const { return _size; }

	/*	Return maximum size	*/
	size_type	max_size() const { return _allocator.max_size(); }

	/*	Change size	*/
	void		resize(size_type num) {
		size_type index;

		if (num < _size) {
			for (index = _size; index > num; --index)
				_allocator.destroy(_pointer + index - 1);
		}
		else if (num > _size) {
			size_type old_capacity = _capacity;

			if (num > _capacity)
				_capacity = num > _capacity * 2 ? num : _capacity * 2;
			pointer new_arr = _allocator.allocate(_capacity);
			for (index = _size; index < num; ++index)
				_allocator.construct(new_arr + index);
			for (index = _size; index > 0; --index)
				_allocator.construct(new_arr + index - 1, _pointer[index - 1]);
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_arr;
		}
		else
			return;
		_size = num;
	}

	void		resize(size_type num, const value_type &value) {
		size_type index;

		if (num < _size) {
			for (index = _size; index > num; --index)
				_allocator.destroy(_pointer + index - 1);
		}
		else if (num > _size) {
			size_type old_capacity = _capacity;
			if (num > _capacity)
				_capacity = num > _capacity * 2 ? num : _capacity * 2;
			pointer new_arr = _allocator.allocate(_capacity);
			for (index = _size; index < num; ++index)
				_allocator.construct(new_arr + index, value);
			for (index = _size; index > 0; --index)
				_allocator.construct(new_arr + index - 1, _pointer[index - 1]);
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_arr;
		}
		else
			return;
		_size = num;
	}

	/*	Return size of allocated storage capacity	*/
	size_type	capacity() const { return _capacity; }

	/*	Test whether vector is empty	*/
	bool		empty() const { return _size == 0; }

	/*	Request a change in capacity	*/
	void		reserve(size_type num) {
		if (num < _capacity)
			return;
		pointer new_pointer = _allocator.allocate(num);
		size_type old_capacity = _capacity, index;

		_capacity = num;
		for (index = _size; index > 0; --index)
			_allocator.construct(new_pointer + index - 1, _pointer[index - 1]);
		for (index = _size; index > 0; --index)
			_allocator.destroy(_pointer + index - 1);
		_allocator.deallocate(_pointer, old_capacity);
		_pointer = new_pointer;
	}

	/**	Element access	**/

	/*	Access element	*/
	reference		operator[](size_type num) { return _pointer[num]; }

	const_reference	operator[](size_type num) const { return _pointer[num]; }

	/*	Access element	*/
	reference		at(size_type num) { return num >= _size ? throw std::out_of_range("vector") : _pointer[num]; }

	const_reference	at(size_type num) const { return num >= _size ? throw std::out_of_range("vector") : _pointer[num]; }

	/*	Access first element	*/
	reference		front() { return _pointer[0]; }

	const_reference	front() const { return _pointer[0]; }

	/*	Access last element	*/
	reference		back() { return _pointer[_size - 1]; }

	const_reference	back() const { return _pointer[_size - 1]; }

	/*	Access data	*/
	pointer data() { return _pointer; }

	const_pointer data() const { return _pointer; }

	/**	Modifiers	**/

	/*	Assign vector content	*/
	template<class InputIterator>
	typename enable_if< not is_integral<InputIterator>::value >::type
	assign(InputIterator first, InputIterator last) {
		size_type num = std::distance(first, last), index;

		if (_capacity >= num) {
			for (index = 0; index < num; ++index)
				_pointer[index] = *(first++);
			for (index = _size; index > num; --index)
				_allocator.destroy(_pointer + index - 1);
		}
		else {
			pointer new_pointer = _allocator.allocate(num);
			size_type old_capacity = _capacity;

			_capacity = num;
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			for (index = 0; index < num; ++index)
				_allocator.construct(new_pointer + index, *(first++));
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_pointer;
		}
		_size = num;
	}

	void assign(size_type num, const value_type &value) {
		size_type index;

		if (_capacity >= num) {
			for (index = 0; index < num; ++index)
				_pointer[index] = value;
			for (index = _size; index > num; --index)
				_allocator.destroy(_pointer + index - 1);
		}
		else {
			pointer new_pointer = _allocator.allocate(num);
			size_type old_capacity = _capacity;

			_capacity = num;
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			for (index = 0; index < num; ++index)
				_allocator.construct(new_pointer + index, value);
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_pointer;
		}
		_size = num;
	}

	/*	Add element at the end	*/
	void push_back(const value_type &value) {
		if (_capacity == 0) {
			_allocator.deallocate(_pointer, _capacity);
			_capacity = 1;
			_pointer = _allocator.allocate(_capacity);
			_allocator.construct(_pointer + _size, value);
		}
		else if (_capacity == _size) {
			pointer new_pointer = _allocator.allocate(_capacity * 2);
			size_type old_capacity = _capacity, index;

			_capacity *= 2;
			_allocator.construct(new_pointer + _size, value);
			for (index = _size; index > 0; --index)
				_allocator.construct(new_pointer + index - 1, _pointer[index - 1]);
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_pointer;
		}
		else
			_allocator.construct(_pointer + _size, value);
		_size++;
	}

	/*	Delete last element	*/
	void pop_back() { _allocator.destroy(_pointer + _size - 1); --_size; }

	/*	Insert elements	*/
	iterator insert(iterator position, const value_type &value) {
		size_type pos_index = position - begin();

		if (_capacity == 0) {
			_allocator.deallocate(_pointer, _capacity);
			_capacity = 1;
			_pointer = _allocator.allocate(_capacity);
			_allocator.construct(_pointer + pos_index, value);
		}
		else if (_capacity == _size) {
			pointer new_pointer = _allocator.allocate(_capacity * 2);
			size_type old_capacity = _capacity, index;

			_capacity *= 2;
			_allocator.construct(new_pointer + pos_index, value);
			for (index = pos_index; index > 0; --index)
				_allocator.construct(new_pointer + index - 1, _pointer[index - 1]);
			for (index = pos_index; index < _size; ++index)
				_allocator.construct(new_pointer + index + 1, _pointer[index]);
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_pointer;
		}
		else if (pos_index == _size)
			_allocator.construct(_pointer + _size, value);
		else {
			size_type index = _size - 1;

			_allocator.construct(_pointer + _size, _pointer[index]);
			for (; index != pos_index; --index)
				_pointer[index] = _pointer[index - 1];
			_pointer[index] = value;
		}
		_size++;
		return _pointer + pos_index;
	}					// single element

	void insert(iterator position, size_type num, const value_type &value) {
		size_type pos_index = position - begin(), index;

		if (_capacity == 0) {
			_allocator.deallocate(_pointer, _capacity);
			_capacity = num;
			_pointer = _allocator.allocate(_capacity);
			for (index = 0; index < num; ++index)
				_allocator.construct(_pointer + pos_index + index, value);
		}
		else if (_capacity == _size or _size + num > _capacity) {
			size_type old_capacity = _capacity, pos_last_index = pos_index + num;

			_capacity = _size + num > _capacity * 2 ? _size + num : _capacity * 2;

			pointer new_pointer = _allocator.allocate(_capacity);
			for (index = pos_index; index < pos_last_index; ++index)
				_allocator.construct(new_pointer + index, value);
			for (index = pos_index; index > 0; --index)
				_allocator.construct(new_pointer + index - 1, _pointer[index - 1]);
			for (index = pos_index; index < _size; ++index)
				_allocator.construct(new_pointer + index + num, _pointer[index]);
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_pointer;
		}
		else if (pos_index == _size)
			for (index = 0; index < num; ++index)
				_allocator.construct(_pointer + _size + index, value);
		else {
			size_type idx;
			index = _size - 1;

			for (idx = num; idx > 0; --idx, --index)
				_allocator.construct(_pointer + _size + idx - 1, _pointer[index]);
			for (++index; index != pos_index; --index)
				_pointer[index + num - 1] = _pointer[index - 1];
			for (idx = num; idx > 0; --idx)
				_pointer[index + idx - 1] = value;
		}
		_size += num;
	}		// fill

	template<class InputIterator>
	typename enable_if< not is_integral<InputIterator>::value >::type insert(iterator position, InputIterator first, InputIterator last) {
		size_type pos_index = position - begin(), num = std::distance(first, last), index;

		if (_capacity == 0) {
			_allocator.deallocate(_pointer, _capacity);
			_pointer = _allocator.allocate(num);
			--last;
			for (index = num; index > 0; --index, ++_size, --last)
				_allocator.construct(_pointer + pos_index + index - 1, *last);
			_capacity = num;
			return ;
		}
		else if (_capacity == _size or _size + num > _capacity) {
			size_type old_capacity = _capacity, pos_last_index = pos_index + num;

			_capacity = _size + num > _capacity * 2 ? _size + num : _capacity * 2;

			pointer new_pointer = _allocator.allocate(_capacity);
			--last;
			for (index = pos_index; index < pos_last_index; ++index)
				_allocator.construct(new_pointer + index, *(first++));
			for (index = pos_index; index > 0; --index)
				_allocator.construct(new_pointer + index - 1, _pointer[index - 1]);
			for (index = pos_index; index < _size; ++index)
				_allocator.construct(new_pointer + index + num, _pointer[index]);
			for (index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			_allocator.deallocate(_pointer, old_capacity);
			_pointer = new_pointer;
		}
		else if (pos_index == _size)
			for (index = 0; index < num; ++index)
				_allocator.construct(_pointer + _size + index, *(first++));
		else {
			index = _size - 1;
			size_type temp_index;

			for (temp_index = num; temp_index > 0; --temp_index, --index)
				_allocator.construct(_pointer + _size + temp_index - 1, _pointer[index]);
			for (index++; index != pos_index; --index)
				_pointer[index + num - 1] = _pointer[index - 1];
			for (temp_index = num; temp_index > 0; --temp_index)
				_pointer[index + temp_index - 1] = *(first++);
		}
		_size += num;
	}	// range

	/*	Erase elements	*/
	iterator erase(iterator position) {
		for (size_type pos_index = position - begin(); pos_index < _size - 1; ++pos_index)
			_pointer[pos_index] = _pointer[pos_index + 1];
		_allocator.destroy(_pointer + _size - 1);
		_size--;
		return position;
	}

	iterator erase(iterator first, iterator last) {
		size_type range_size = last - first, last_index = last - begin() - 1, first_index = first - begin();

		for (; last_index < _size - 1; ++last_index, ++first_index)
			_pointer[first_index] = _pointer[last_index + 1];
		for (size_type index = 0; index < range_size; ++index)
			_allocator.destroy(_pointer + _size - index - 1);
		_size -= range_size;
		return first;
	}

	/*	Swap content	*/
	void swap(vector &x) {
		std::swap(_pointer, x._pointer);
		std::swap(_size, x._size);
		std::swap(_capacity, x._capacity);
	}

	/*	Clear content	*/
	void clear() {
		for (size_type index = _size; index > 0; --index)
			_allocator.destroy(_pointer + index - 1);
		_size = 0;
	}

	/**	Allocator	**/

	/*	Get allocator	*/
	allocator_type get_allocator() const { return _allocator; }

	/**	Constructors	**/

	/*	Default constructor	*/
	explicit vector(const allocator_type &alloc = allocator_type()) : _allocator(alloc), _size(0), _capacity(0) { _pointer = _allocator.allocate(0); }

	/*	Size fill constructor	*/
	explicit vector(size_type num, const value_type &value, const allocator_type &alloc = allocator_type()) : _allocator(alloc), _size(num), _capacity(num) {
		_pointer = _allocator.allocate(_capacity);
		for (size_type index = 0; index < _size; ++index)
			_allocator.construct(_pointer + index, value);
	}

	/*	Size constructor	*/
	explicit vector(size_type num, const allocator_type &alloc = allocator_type()) : _allocator(alloc), _size(num), _capacity(num) {
		_pointer = _allocator.allocate(_capacity);
		for (size_type index = 0; index < _size; index++)
			_allocator.construct(_pointer + index);
	}

	/*	Iterator constructor	*/
	template<class InputIterator>
	vector(InputIterator first, typename enable_if< !is_integral<InputIterator>::value, InputIterator >::type last, const allocator_type &alloc = allocator_type()) : _allocator(alloc) {
		size_type num = std::distance(first, last), index;
		_capacity = num;
		_size = num;
		_pointer = _allocator.allocate(_capacity);
		for (index = 0; first != last; ++index) {
			_allocator.construct(_pointer + index, *(first++));
		}
	}

	/*	Copy constructor	*/
	vector(const vector &other) : _allocator(other._allocator), _size(other._size), _capacity(other._capacity) {
		_pointer = _allocator.allocate(_capacity);
		for (size_type index = 0; index < _size; index++)
			_allocator.construct(_pointer + index, other._pointer[index]);
	}

	/**	Destructor	**/

	~vector() {
		for (size_type index = _size; index > 0; --index)
			_allocator.destroy(_pointer + index - 1);
		_allocator.deallocate(_pointer, _capacity);
	}

	/**	Assign overload	**/

	vector &operator=(const vector &other) {
		if (this == &other)
			return *this;
		if (_size >= other._size) {
			for (size_type index = 0; index < other._size; ++index)
				_pointer[index] = other._pointer[index];
			for (size_type index = _size; index > other._size; --index)
				_allocator.destroy(_pointer + index - 1);
			_size = other._size;
		}
		else {
			for (size_type index = _size; index > 0; --index)
				_allocator.destroy(_pointer + index - 1);
			_allocator.deallocate(_pointer, _capacity);
			_capacity = other._capacity;
			_size = other._size;
			_pointer = _allocator.allocate(_capacity);
			for (size_type index = 0; index < _size; ++index)
				_allocator.construct(_pointer + index, other._pointer[index]);
		}
		return *this;
	}

	/**	Non-member function overloads	**/

	/*	Relational operators	*/
	friend bool operator==(const vector &left, const vector &right) {
		if (left._size == right._size)
			return ft::equal(left.begin(), left.end(), right.begin());
		else
			return false;
	}

	friend bool operator!=(const vector &left, const vector &right) { return !(left == right); }

	friend bool operator<(const vector &left, const vector &right) { return ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()); }

	friend bool operator<=(const vector &left, const vector &right) { return !(right < left); }

	friend bool operator>(const vector &left, const vector &right) { return right < left; }

	friend bool operator>=(const vector &left, const vector &right) { return !(left < right); }
};


}

namespace std {
template<class T, class Alloc>
void swap(ft::vector<T,Alloc> &left, ft::vector<T,Alloc> &right) { left.swap(right); }
}


#endif
