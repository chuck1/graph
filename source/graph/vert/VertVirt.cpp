#include <gr/vert/VertVirt.hpp> // gr/vert/VertVirt.hpp_in

typedef gr::vert::VertVirt THIS;

THIS::VertVirt(
		gr::GRAPH_S g, 
		gr::VERT_S const & leaf, 
		gr::VERT_S const & other, 
		gr::S_Edge const & e):
	gr::vert::Vert(g),
	gr::plot::vert(g, "virt"),
	_M_leaf_replaced(leaf),
	_M_other_replaced(other),
	_M_edge_replaced(e)
{
}

