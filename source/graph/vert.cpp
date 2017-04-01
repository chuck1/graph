#include <iostream>
#include <algorithm>
#include <cassert>

#include <gr/container/edge.hpp> // gr/container/edge.hpp.in
#include <gr/iterator/edge_vert.hpp> // gr/iterator/edge_vert.hpp.in
#include <gr/pair.hpp> // gr/pair.hpp.in
#include <gr/edge.hpp> // gr/edge.hpp.in
#include <gr/graph.hpp> // gr/vert.hpp.in
#include <gr/layer.hpp>

#include <gr/vert.hpp> // gr/vert.hpp_in

typedef gr::vert THIS;

THIS::vert(gr::GRAPH_S g):
	_M_enabled(true),
	_M_graph(g),
	_M_edges(new gr::container::edge)
{
}
THIS::~vert()
{
//	std::cout << "vert destroyed" << std::endl;
}
bool				THIS::enabled() const
{
	if(!_M_enabled) return false;

	if(!_M_layer.expired()) {
		if(!_M_layer.lock()->_M_enabled) return false;
	}

	return true;
}
gr::GRAPH_S			THIS::get_graph()
{
	auto ret = _M_graph.lock();
	assert(ret);
	return ret;
}
gr::iterator::edge_vert		THIS::edge_begin()
{
	return gr::iterator::edge_vert(*_M_edges, _M_edges->begin());
}
gr::iterator::edge_vert		THIS::edge_end()
{
	return gr::iterator::edge_vert(*_M_edges, _M_edges->end());
}
gr::iterator::edge_vert		THIS::edge_erase(gr::iterator::edge_vert & i)
{
	auto j = _M_edges->erase(i._M_i);

	return gr::iterator::edge_vert(*_M_edges, j);
}

void				THIS::edge_erase_disconnected()
{
	for(auto i = edge_begin(); i != edge_end();) {

		if(i->_M_v0.expired()) throw std::exception();

		if(i->_M_v1.expired()) {
			//std::cout << "gr::vert erase edge" << std::endl;
			i = edge_erase(i);
		} else {
			++i;
		}
	}
}
unsigned int			THIS::edge_size()
{
	return std::distance(edge_begin(), edge_end());
}
void				THIS::add_edge_util(
		gr::VERT_S v0, 
		gr::VERT_S v1, 
		std::shared_ptr<gr::edge_data> const & edge_data)
{
	assert(_M_edges);

	gr::edge edge(v0, v1, edge_data);

	_M_edges->insert(edge);
}
void				THIS::edge_erase_util(gr::VERT_S & v0, gr::VERT_S & v1)
{
	//gr::container::EDGE_S const & edges = (*i)->_M_edges;

	auto j = _M_edges->find(v1);
	//auto j = std::find(edges.begin(), edges.end(), v1);

	if(j == _M_edges->end()) throw std::exception();

	_M_edges->erase(j);

	//for(auto j = edges.begin(); j != edges.end(); ++j) {
	//	gr::VERT_S w = j->first.lock();
	//}
}
std::string			THIS::dot()
{
	return std::string();
}



