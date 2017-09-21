#include <gr/vert/VertVirt.hpp> // gr/vert/VertVirt.hpp_in

typedef gr::vert::VertVirt THIS;

THIS::VertVirt(
		gr::GRAPH_S g, 
		gr::VERT_S const & v0, 
		gr::VERT_S const & v1):
	gr::vert::Vert(g),
	gr::plot::vert(g, "virt"),
	_M_v0(v0),
	_M_v1(v1)
{
}

