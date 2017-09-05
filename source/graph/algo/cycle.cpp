#include <gr/vert.hpp>
#include <gr/edge.hpp>

#include <gr/algo/cycle.hpp> // gr/algo/cycle.hpp_in

typedef gr::algo::cycle THIS;

/*
THIS::cycle()
{
}
*/
THIS::cycle(iterator b, iterator e, gr::VERT_S const & v):
	_M_edges(b, e),
	_M_v(v)
	
{
}
THIS::const_iterator	THIS::begin() const
{
	return _M_edges.begin();
}
THIS::iterator		THIS::begin()
{
	return _M_edges.begin();
}
THIS::const_iterator	THIS::end() const
{
	return _M_edges.end();
}
THIS::iterator		THIS::end()
{
	return _M_edges.end();
}
unsigned int		THIS::size() const
{
	return _M_edges.size();
}
void			THIS::shift()
{
	/**
	 * shift a cycle until the lowerest edge is at the front
	 */

	// find lowest edge
	auto it0 = _M_edges.begin();
	auto e0 = *it0;

	for(auto it = it0 + 1; it != _M_edges.end(); ++it)
	{
		auto e = *it;
		if((*e) < (*e0))
		{
			it0 = it;
			e0 = *it0;
		}
	}

	//int d = std::distance(it0, _M_edges.end());

	int s = _M_edges.size();

	// determine new starting vertex
	for(auto it = _M_edges.begin(); it != it0; ++it)
	{
		_M_v = (*it)->other(_M_v);
	}

	// shift
	std::deque<gr::EDGE_S> temp(it0, _M_edges.end());
	
	_M_edges.insert(_M_edges.begin(), temp.begin(), temp.end());

	_M_edges.resize(s);
}
THIS::CONT const &	THIS::container() const
{
	return _M_edges;
}
std::ostream &		THIS::print(std::ostream & os) const
{
	for(auto it = begin(); it != end(); ++it)
	{
		char buffer[128];
		auto e = (*it);
		sprintf(buffer, "(%s)%s(%s) - ", (*it)->v0()->name().c_str(), e->name().c_str(), (*it)->v1()->name().c_str());
		os << buffer;
	}
	return os;
}

std::ostream &	operator<<(std::ostream & os, gr::algo::cycle const & c)
{
	return c.print(os);
}

