#include <cassert>
#include <iostream>

#include <gr/container/vert.hpp> // gr/container/vert.hpp.in
#include <gr/container/edge.hpp> // gr/container/edge.hpp.in
#include <gr/vert.hpp> // gr/edge.hpp.in
#include <gr/edge.hpp> // gr/edge.hpp.in
#include <gr/edge_data.hpp> // gr/edge_data.hpp.in

#include <gr/iterator/edge_graph.hpp> // gr/iterator/edge_graph.hpp.in

typedef gr::iterator::edge_graph THIS;

THIS::edge_graph(gr::container::vert & container, THIS::iterator0 const & i):
	_M_container(container),
	_M_i(i)
{
	if(_M_i != _M_container.end()) {
		_M_j = (*_M_i)->_M_edges->begin();
		next();
	}
}
THIS::edge_graph(gr::container::vert & container, THIS::iterator0 const & i, THIS::iterator1 const & j):
	_M_container(container),
	_M_i(i),
	_M_j(j)
{
	next();
}

THIS				THIS::operator=(THIS const & i)
{
	_M_container = i._M_container;
	_M_i = i._M_i;
	_M_j = i._M_j;
	return *this;
}

void				THIS::next()
{
	while(true) {
		//std::cout << "iterator edge_graph i " << std::distance(_M_i, _M_container.end()) << std::endl;

		if(_M_i == _M_container.end()) break;

		gr::VERT_S const & pu = *_M_i;
		gr::vert & u = *pu;
	
		//std::cout << "iterator edge_graph j " << std::distance(_M_j, u._M_edges->end()) << std::endl;

		if(_M_j == u._M_edges->end()) {
			++_M_i;

			if(_M_i == _M_container.end()) break;

			_M_j = (*_M_i)->_M_edges->begin();

			continue;
		}

		gr::edge const & edge = *_M_j;
		
		if(!edge.enabled()) {
			++_M_j;
			continue;
		}

		gr::VERT_S const & v = _M_j->_M_v1.lock();
		
		assert(v);

		if(u < (*v)) {
			break;
		}

		++_M_j;
	}
}
gr::iterator::edge_graph	THIS::operator++()
{
	++_M_j;
	next();
	return THIS(_M_container, _M_i, _M_j);
	//return *this;
}
gr::iterator::edge_graph	THIS::operator++(int)
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

bool				THIS::operator==(gr::iterator::edge_graph const & i)
{
	if(_M_i == i._M_i) {
		if(_M_i == _M_container.end()) return true;

		return _M_j == i._M_j;
	} else {
		return false;
	}
}
bool				THIS::operator!=(gr::iterator::edge_graph const & i)
{
	return !(operator==(i));
}



