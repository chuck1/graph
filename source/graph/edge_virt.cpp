#include <gr/edge_virt.hpp> // gr/edge_virt.hpp_in

gr::edge_virt::edge_virt(gr::VERT_S const & v0, gr::VERT_S const & v1, gr::VERT_S const v):
	gr::edge(v0, v1),
	_M_v_replaced(v)
{
}

