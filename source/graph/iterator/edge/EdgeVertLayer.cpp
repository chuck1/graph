#include <gr/iterator/edge/EdgeVertLayer.hpp> // gr/iterator/edge/EdgeVertLayer.hpp_in

typedef gr::iterator::edge::EdgeVertLayer THIS;

THIS::EdgeVertLayer(gr::container::edge & e, iterator i):
	gr::iterator::edge::EdgeVert(e, i)
{
}
bool			THIS::check(gr::S_Edge const & e)
{
	if(!e->enabled()) return false;
	
	if(!e->_M_layer.contains(_M_layer)) return false;

	return true;
}


