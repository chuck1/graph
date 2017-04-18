
#include <gr/plot/vert.hpp> // gr/plot/vert.hpp_in

typedef gr::plot::vert THIS;

THIS::vert(gr::GRAPH_S g, std::string nid): gr::vert(g), id(nid)
{
}
/*
bool	THIS::operator==(gr::vert const & v)
{
	auto v1 = static_cast<gr::plot::vert const *>(&v);
	return id == v1->id;
}
bool	THIS::operator<(gr::vert const & v)
{
	auto v1 = static_cast<gr::plot::vert const *>(&v);
	return id < v1->id;
}
*/

