#include <gr/container/edge.hpp>
#include <gr/edge_data.hpp>

#include <gr/iterator/edge/EdgeVert.hpp> // gr/iterator/edge_vert.hpp_in

typedef gr::iterator::edge::EdgeVert THIS;

THIS::EdgeVert(gr::container::edge & c, THIS::iterator i):
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
bool				THIS::check(gr::S_Edge const & e)
{
	return e->enabled();
}
void				THIS::next()
{
	while(true)
	{
		if(_M_i == _M_container.end()) break;

		auto e = *_M_i;

		if(!check(e))
		{
			++_M_i;
			continue;
		}

		break;
	}
}
gr::iterator::edge::EdgeVert		THIS::operator++()
{
	++_M_i;
	next();
	return THIS(_M_container, _M_i);
}
gr::iterator::edge::EdgeVert		THIS::operator++(int)
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

bool				THIS::operator==(gr::iterator::edge::EdgeVert const & i)
{
	return _M_i == i._M_i;
}
bool				THIS::operator!=(gr::iterator::edge::EdgeVert const & i)
{
	return !operator==(i);
}


