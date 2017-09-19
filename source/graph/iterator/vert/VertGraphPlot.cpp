#include <gr/iterator/vert/VertGraphPlot.hpp> // gr/iterator/vert/VertGraphPlot.hpp_in

typedef gr::iterator::vert::VertGraphPlot THIS;

THIS::VertGraphPlot(gr::container::vert & c, iterator const & i):
	gr::iterator::vert_graph(c, i)
{
}
bool		THIS::check(gr::S_Vert const & v) const
{
	return v->_M_layer.plot();
}


