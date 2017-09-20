#include <iostream>
#include <gr/edge.hpp>
#include <gr/layer.hpp>
#include <gr/graph.hpp>

#include <gr/algo/bfs/SpanningTree.hpp> // gr/algo/bfs/SpanningTree.hpp_in

typedef gr::algo::bfs::SpanningTree THIS;

THIS::SpanningTree(
		gr::GRAPH_S const & g,
		gr::S_Vert const & root):
	gr::algo::bfs::BFS(g, root)
{
}
void			THIS::visit(
		gr::S_Vert const & v0,
		gr::S_Edge const & e,
		gr::S_Vert const & v1)
{
	static int i = 0;
	std::cout << "bfs spanning tree mark edge to keep " << (i++) << std::endl;
	std::cout << "    " << v0->name() << " -- " << v1->name() << std::endl;
	e->_M_layer.push_front(_M_layer2);
}
void			THIS::initialize()
{
	gr::algo::bfs::BFS::initialize();

	if(!_M_layer1)
		_M_layer1 = std::make_shared<gr::layer>();
	
	_M_layer2 = std::make_shared<gr::layer>();

	_M_layer1->_M_enabled.set(true);
	
	_M_layer2->_M_enabled.set(true);
	_M_layer2->_M_plot.set(true);

	for(auto it = _M_g->edge_begin(); it != _M_g->edge_end(); ++it)
		(*it)->_M_layer.push_front(_M_layer1);
}
void			THIS::finalize()
{
	_M_layer1->_M_enabled.set(false);
	_M_layer1->_M_plot.set(false);
}

