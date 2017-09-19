#include <gr/vert.hpp>

#include <gr/iterator/edge/EdgeGraphPlot.hpp> // gr/iterator/edge/EdgeGraphPlot.hpp_in

typedef gr::iterator::edge::EdgeGraphPlot THIS;

THIS::EdgeGraphPlot(gr::container::vert & c, iterator0 const & i):
	gr::iterator::edge_graph(c, i)
{
}
THIS::EdgeGraphPlot(gr::container::vert & c, iterator0 const & i, iterator1 const & j):
	gr::iterator::edge_graph(c, i, j)
{
}
bool		THIS::check(gr::S_Edge const & e)
{
	if(!e->valid()) return false;
	
	if(!e->v0()->_M_layer.plot()) return false;
	if(!e->v1()->_M_layer.plot()) return false;

	return e->_M_layer.plot();
}


