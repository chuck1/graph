#include <iostream>
#include <cassert>

#include <gr/container/vert.hpp>
#include <gr/vert/Vert.hpp> // gr/vert.hpp.in
#include <gr/pair.hpp> // gr/pair.hpp.in

#include <gr/iterator/vert/VertGraphConst.hpp> // gr/iterator/vert/VertGraphConst.hpp_in

typedef gr::iterator::vert::VertGraphConst THIS;

THIS::VertGraphConst(gr::container::vert const & container, THIS::iterator j):
	_M_container(container),
	_M_j(j)
{
	next();
}
/*
THIS				THIS::operator=(THIS const & i)
{
	_M_container = i._M_container;
	_M_j = i._M_j;
	return *this;
}
*/
bool				THIS::check(gr::S_Vert const & v) const
{
	return v->enabled();
}
void				THIS::next()
{
	while(true)
	{
		if(_M_j == _M_container.cend()) break;
		
		gr::VERT_S const & v = *_M_j;

		assert(v);

		if(!check(v))
		{
			++_M_j;
			continue;
		}

		break;
	}
}
THIS				THIS::operator++()
{
	++_M_j;
	next();
	return THIS(_M_container, _M_j);
}
THIS				THIS::operator++(int)
{
	THIS ret(_M_container, _M_j);
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








