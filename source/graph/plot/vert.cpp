
#include <gr/plot/vert.hpp> // gr/plot/vert.hpp_in

typedef gr::plot::vert THIS;

THIS::vert(gr::graph::S_Graph g, std::string name): 
	gr::vert::Vert(g),
	_M_name(name)
{
}
std::string	THIS::name()
{
	return _M_name;
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

