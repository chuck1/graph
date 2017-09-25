#include <gr/graph.hpp>
#include <gr/layer.hpp>

#include <gr/algo/dfs/Components.hpp> // gr/algo/dfs/Components.hpp_in

typedef gr::algo::dfs::Components THIS;

THIS::Components(
		gr::GRAPH_S const & g):
	gr::algo::dfs::DFS(g)
{
}
void			THIS::visit(
		gr::S_Vert const & v0)
{
	_M_layer_current = std::make_shared<gr::layer>();
	_M_layers.push_back(_M_layer_current);

	v0->_M_layer.push_front(_M_layer_current);
}
void			THIS::visit(
		gr::S_Vert const & v0,
		gr::S_Edge const & e,
		gr::S_Vert const & v1
		)
{
	assert(_M_layer_current);
	v0->_M_layer.push_front(_M_layer_current);
}



