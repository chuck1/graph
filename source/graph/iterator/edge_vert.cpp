#include <gr/container/edge.hpp>
#include <gr/edge_data.hpp>

#include <gr/iterator/edge_vert.hpp> // gr/iterator/edge_vert.hpp_in

typedef gr::iterator::edge_vert THIS;

THIS::edge_vert(gr::container::edge & c, THIS::iterator i):
	_M_container(c),
	_M_i(i)
{
	next();
}
THIS &				THIS::operator=(THIS const & i)
{
	_M_container = i._M_container;
	_M_i = i._M_i;
	return *this;
}

void				THIS::next()
{
	while(true) {
		if(_M_i == _M_container.end()) break;

		auto e = *_M_i;

		if(!e->enabled()) {
			++_M_i;
			continue;
		}

		break;
	}
}
gr::iterator::edge_vert		THIS::operator++()
{
	++_M_i;
	next();
	return THIS(_M_container, _M_i);
}
gr::iterator::edge_vert		THIS::operator++(int)
{
	THIS ret(_M_container, _M_i);
	operator++();
	return ret;
}

THIS::reference			THIS::operator*()
{
	return *_M_i;
}
THIS::value_type const *	THIS::operator->()
{
	return _M_i.operator->();
}

bool				THIS::operator==(gr::iterator::edge_vert const & i)
{
	return _M_i == i._M_i;
}
bool				THIS::operator!=(gr::iterator::edge_vert const & i)
{
	return !operator==(i);
}


