#include <cassert>
#include <iostream>

#include <gr/decl.hpp> // gr/decl.hpp_in
#include <gr/container/vert.hpp> // gr/container/vert.hpp.in
#include <gr/container/edge.hpp> // gr/container/edge.hpp.in
#include <gr/vert/Vert.hpp> // gr/edge.hpp.in
#include <gr/edge.hpp> // gr/edge.hpp.in
#include <gr/edge_data.hpp> // gr/edge_data.hpp.in

#include <gr/iterator/edge/EdgeGraphConst.hpp> // gr/iterator/edge/EdgeGraphConst.hpp_in

typedef gr::iterator::edge::EdgeGraphConst THIS;

THIS::EdgeGraphConst(
		gr::container::vert const & container, 
		THIS::iterator0 const & i):
	_M_container(container),
	_M_i(i)
{
	if(_M_i != _M_container.cend())
	{
		_M_j = (*_M_i)->_M_edges->begin();
		next();
	}
}
THIS::EdgeGraphConst(
		gr::container::vert const & container, 
		THIS::iterator0 const & i, 
		THIS::iterator1 const & j):
	_M_container(container),
	_M_i(i),
	_M_j(j)
{
	next();
}
/*
THIS				THIS::operator=(THIS const & i)
{
	_M_container = i._M_container;
	_M_i = i._M_i;
	_M_j = i._M_j;
	return *this;
}*/
bool				THIS::check(gr::S_Edge const & e)
{
	return e->enabled();
}
void				THIS::next()
{
	while(true)
	{
		if(_M_i == _M_container.cend()) break;

		gr::VERT_S const & u = *_M_i;

		if(_M_j == u->_M_edges->end())
		{
			++_M_i;

			if(_M_i == _M_container.cend()) break;

			_M_j = (*_M_i)->_M_edges->begin();

			*_M_j;

			continue;
		}

		auto e = *_M_j;
		
		if(e->_M_v0.expired()) { ++_M_j; continue; }
		if(e->_M_v1.expired()) { ++_M_j; continue; }

		if(!check(e))
		{
			++_M_j;
			continue;
		}

		gr::VERT_S const & v = e->other(u);

		if((*u) < (*v)) break;
		
		// handle loop edges
		if((*u) == (*v))
		{
			auto it = _M_edges.find(e);
			if(it == _M_edges.end())
			{
				_M_edges.insert(e);
				break;
			}
		}

		++_M_j;
	}
}
THIS				THIS::operator++()
{
	++_M_j;
	next();
	return THIS(_M_container, _M_i, _M_j);
	//return *this;
}
THIS				THIS::operator++(int)
{
	THIS ret(_M_container, _M_i, _M_j);
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
	//_M_value = *_M_j;
	//return &_M_value;
}

bool				THIS::operator==(THIS const & i)
{
	if(_M_i == i._M_i)
	{
		if(_M_i == _M_container.cend()) return true;

		return _M_j == i._M_j;
	}
		
	return false;
}
bool				THIS::operator!=(THIS const & i)
{
	return !(operator==(i));
}



