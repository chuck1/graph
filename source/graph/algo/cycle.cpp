
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

