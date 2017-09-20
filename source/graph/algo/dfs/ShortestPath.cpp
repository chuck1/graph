#include <cfloat>
#include <iostream>
#include <gr/edge.hpp>
#include <gr/vert/Vert.hpp> // gr/vert/Vert.hpp_in
#include <gr/layer.hpp>
#include <gr/graph.hpp>
#include <gr/util.hpp>

#include <gr/algo/dfs/ShortestPath.hpp> // gr/algo/dfs/ShortestPath.hpp_in

typedef gr::algo::dfs::ShortestPath THIS;

THIS::ShortestPath(
		gr::GRAPH_S const & g,
		gr::S_Vert const & root):
	gr::algo::dfs::DFS(g, root)
{
}
void			THIS::run_pre(
		gr::S_Vert const & v0)
{
	auto d0 = v0->_M_shortest_path.d;

	float w = 1;

	for(auto e : gr::range(v0->edge_begin(), v0->edge_end()))
	{
		auto v1 = e->other(v0);
		//if(v1->_M_visited) continue;

		auto & d1 = v1->_M_shortest_path.d;

		if((d0 + w) < d1)
		{
			d1 = d0 + w;
			v1->_M_shortest_path.e = e;
		}
	}
}
void			THIS::visit(
		gr::S_Vert const & v0,
		gr::S_Edge const & e,
		gr::S_Vert const & v1)
{

}
void			THIS::initialize()
{
	gr::algo::dfs::DFS::initialize();
	
	for(auto v : gr::range(_M_g->vert_begin(), _M_g->vert_end()))
	{
		v->_M_shortest_path.d = FLT_MAX;
	}

	_M_root->_M_shortest_path.d = 0;
}
void			THIS::finalize()
{
	
}


