#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "ft_vector.hpp"

namespace ft {
template<class T, class Container = vector<T> >
class stack {
public:
	typedef T											value_type;		//	The first template parameter (T)
	typedef Container									container_type;	//	The second template parameter (Container)
	typedef typename container_type::size_type			size_type;		//	An unsigned integral type, usually the same as size_t
private:
	typedef typename container_type::reference			reference;		//	value_type&
	typedef typename container_type::const_reference	const_reference;//	const value_type&
protected:
	container_type _underlying_container;
public:
	/**	Member functions	**/

	bool			empty() const { return _underlying_container.empty(); }

	size_type		size() const { return _underlying_container.size(); }

	reference		top() { return _underlying_container.back(); }

	const_reference	top() const { return _underlying_container.back(); }

	void			push(const value_type &value) { _underlying_container.push_back(value); }

	void			pop() { _underlying_container.pop_back(); }

	/**	Constructor	**/

	explicit stack(const container_type &container = container_type()) : _underlying_container(container) {}

	stack(const stack &other) : _underlying_container(other._underlying_container) {}

	/**	Destructor	**/

	~stack() {}

	/**	Assign overload	**/

	stack &operator=(const stack &other) {
		if (this == &other)
			return *this;
		_underlying_container = other._underlying_container;
		return *this;
	}

	/**	Non-member function overloads	**/

	friend bool operator==(const stack &left, const stack &right)	{ return left._underlying_container == right._underlying_container; }

	friend bool operator!=(const stack &left, const stack &right)	{ return left._underlying_container != right._underlying_container; }

	friend bool operator<(const stack &left, const stack &right)	{ return left._underlying_container < right._underlying_container; }

	friend bool operator<=(const stack &left, const stack &right)	{ return left._underlying_container <= right._underlying_container; }

	friend bool operator>(const stack &left, const stack &right)	{ return left._underlying_container > right._underlying_container; }

	friend bool operator>=(const stack &left, const stack &right)	{ return left._underlying_container >= right._underlying_container; }

};
}
#endif
