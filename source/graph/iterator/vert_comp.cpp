#include <iostream>
#include <cassert>

#include <gr/container/vert.hpp>
#include <gr/vert.hpp> // gr/vert.hpp.in
#include <gr/pair.hpp> // gr/pair.hpp.in

#include <gr/iterator/vert_comp.hpp> // gr/iterator/vert_comp.hpp.in

typedef gr::iterator::vert_comp THIS;

THIS::vert_comp(gr::container::vert & container, THIS::iterator j, int c):
	_M_container(container),
	_M_j(j),
	_M_c(c)
{
	next();
}
void				THIS::next()
{
	while(true) {
		if(_M_j == _M_container.end()) break;
		
		gr::VERT_S const & v = *_M_j;

		assert(v);

		if(!v->enabled()) {
			++_M_j;
			continue;
		}

		if(v->comp._M_c == _M_c) break;

		//std::cout << "next " << v->comp._M_visited << " " << v->comp._M_c << " != " << _M_c << std::endl;

		++_M_j;
	}
}
gr::iterator::vert_comp		THIS::operator++()
{
	++_M_j;
	next();
	return gr::iterator::vert_comp(_M_container, _M_j, _M_c);
}
gr::iterator::vert_comp		THIS::operator++(int)
{
	gr::iterator::vert_comp ret(_M_container, _M_j, _M_c);
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

bool				THIS::operator==(gr::iterator::vert_comp const & i)
{
	return (_M_j == i._M_j);
}
bool				THIS::operator!=(gr::iterator::vert_comp const & i)
{
	return !(_M_j == i._M_j);
}








