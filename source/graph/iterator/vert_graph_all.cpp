#include <iostream>
#include <cassert>

#include <gr/container/vert.hpp>
#include <gr/vert/Vert.hpp> // gr/vert.hpp.in

#include <gr/iterator/vert/VertGraphAll.hpp> // gr/iterator/VertGraphAll.hpp.in

typedef gr::iterator::vert::VertGraphAll THIS;

THIS::VertGraphAll(gr::container::vert & container, THIS::iterator j):
	_M_container(container),
	_M_j(j)
{
	next();
}
THIS::VertGraphAll(gr::container::vert & container, THIS::iterator j, gr::VERT_FUNC func):
	_M_container(container),
	_M_j(j),
	_M_func(func)
{
	next();
}
THIS				THIS::operator=(THIS const & i)
{
	_M_container = i._M_container;
	_M_j = i._M_j;
	return *this;
}

void				THIS::next()
{
	while(true) {
		if(_M_j == _M_container.end()) break;
		
		gr::VERT_S const & v = *_M_j;

		assert(v);
		
		if(_M_func) {
			if(!_M_func(v)) {
				++_M_j;
				continue;
			}
		}

		break;
	}
}
THIS				THIS::operator++()
{
	++_M_j;
	next();
	return gr::iterator::vert::VertGraphAll(_M_container, _M_j);
}
THIS				THIS::operator++(int)
{
	gr::iterator::vert::VertGraphAll ret(_M_container, _M_j);
	operator++();
	return ret;
}

THIS::reference			THIS::operator*()
{
	return *_M_j;
}
THIS::value_type const *	THIS::operator->()
{
	return _M_j.operator->();
}

bool				THIS::operator==(THIS const & i)
{
	return (_M_j == i._M_j);
}
bool				THIS::operator!=(THIS const & i)
{
	return !(_M_j == i._M_j);
}








