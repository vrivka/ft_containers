#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "ft_vector.hpp"

namespace ft {
template<class T, class Container = ft::vector<T> >
class stack {
public:
	typedef T											value_type;		//	The first template parameter (T). Type of the elements
	typedef Container									container_type;	//	The second template parameter (Container). Type of the underlying container
	typedef typename container_type::size_type			size_type;		//	an unsigned integral type, usually the same as size_t
	typedef typename container_type::reference			reference;		//	for the default allocator: value_type&
	typedef typename container_type::const_reference	const_reference;//	for the default allocator: const value_type&
protected:
	container_type c;
public:
	///*	Member functions	*/

	/*	Test whether container is empty	*/
	bool			empty() const { return c.empty(); }

	/*	Return size	*/
	size_type		size() const { return c.size(); }

	/*	Access next element	*/
	reference		top() { return c.back(); }

	const_reference	top() const { return c.back(); }

	/*	Insert element	*/
	void			push(const value_type &val) { c.push_back(val); }

	/*	Remove top element	*/
	void			pop() { c.pop_back(); }

	///*	Constructor	*/

	/*	Default constructor	*/
	explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}

	/*	Copy constructor	*/
	stack(const stack &other) : c(other.c) {}

	///*	Destructor	*/

	~stack() {}

	///*	Assign overload	*/

	stack &operator=(const stack &other) {
		if (this == &other)
			return *this;
		this->c = other.c;
		return *this;
	}

	///*	Non-member function overloads	*/

	friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c == rhs.c; }

	friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c != rhs.c; }

	friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c < rhs.c; }

	friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c <= rhs.c; }

	friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c > rhs.c; }

	friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c >= rhs.c; }

};
}
#endif
