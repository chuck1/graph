#include <iostream>
#include <cassert>

#include <gr/container/vert.hpp>
#include <gr/vert.hpp> // gr/vert.hpp.in
#include <gr/pair.hpp> // gr/pair.hpp.in

#include <gr/iterator/vert_graph.hpp> // gr/iterator/vert_graph.hpp_in

typedef gr::iterator::vert_graph THIS;

THIS::vert_graph(gr::container::vert & container, THIS::iterator j):
	_M_container(container),
	_M_j(j)
{
	next();
}
THIS				THIS::operator=(THIS const & i)
{
	_M_container = i._M_container;
	_M_j = i._M_j;
	return *this;
}
bool				THIS::check(gr::S_Vert const & v) const
{
	return v->enabled();
}
void				THIS::next()
{
	while(true)
	{
		if(_M_j == _M_container.end()) break;
		
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
gr::iterator::vert_graph		THIS::operator++()
{
	++_M_j;
	next();
	return gr::iterator::vert_graph(_M_container, _M_j);
}
gr::iterator::vert_graph		THIS::operator++(int)
{
	gr::iterator::vert_graph ret(_M_container, _M_j);
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

bool				THIS::operator==(gr::iterator::vert_graph const & i)
{
	return (_M_j == i._M_j);
}
bool				THIS::operator!=(gr::iterator::vert_graph const & i)
{
	return !(_M_j == i._M_j);
}








