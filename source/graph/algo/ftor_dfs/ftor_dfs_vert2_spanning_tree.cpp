#include <gr/vert/Vert.hpp> // gr/vert.hpp_in
#include <gr/graph.hpp>
#include <gr/layer.hpp> // gr/layer.hpp_in
#include <gr/iterator/edge/EdgeGraph.hpp>

#include <gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree.hpp> // gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree.hpp_in

typedef gr::algo::ftor_dfs::ftor_dfs_vert2_spanning_tree THIS;

void			THIS::initialize(
		gr::GRAPH_S g,
		gr::VERT_S const & v0
		)
{
	if(!_M_layer1) {
		_M_layer1 = std::make_shared<gr::layer>();
	}
	_M_layer2 = std::make_shared<gr::layer>();

	_M_layer1->_M_enabled.set(true);
	_M_layer2->_M_enabled.set(true);

	for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
		(*it)->dfs._M_visited = false;

	v0->dfs._M_visited = true;

	for(auto it = g->edge_begin(); it != g->edge_end(); ++it)
		(*it)->_M_layer.push_front(_M_layer1);
}
void			THIS::finalize(
		gr::GRAPH_S g,
		gr::VERT_S const & v0
		)
{
	_M_layer1->_M_enabled.set(false);
}
bool			THIS::check(
		gr::VERT_S const & v0,
		gr::VERT_S const & v1)
{
	if(v1->dfs._M_visited) return false;

	v1->dfs._M_visited = true;

	return true;
}
void			THIS::yield(
		gr::VERT_S const & v0,
		gr::VERT_S const & v,
		gr::VERT_S const & v1,
		gr::EDGE_S const & e
		)
{
	static int i = 0;
	std::cout << "ftor spanning tree mark edge to keep " << (i++) << std::endl;
	e->_M_layer.push_front(_M_layer2);
}
bool			THIS::descend(
		gr::VERT_S const & v0,
		gr::VERT_S const & v1)
{
	return true;
}

