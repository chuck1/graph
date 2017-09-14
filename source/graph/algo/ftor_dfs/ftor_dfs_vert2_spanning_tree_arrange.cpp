#include <gr/vert.hpp> // gr/vert.hpp_in
#include <gr/graph.hpp>
#include <gr/layer.hpp> // gr/layer.hpp_in
#include <gr/edge_algo_data.hpp> // gr/edge.hpp_in
#include <gr/edge.hpp> // gr/edge.hpp_in
#include <gr/iterator/edge_graph.hpp>

#include <gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree_arrange.hpp> // gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree.hpp_in

typedef gr::algo::ftor_dfs::ftor_dfs_vert2_spanning_tree_arrange THIS;







void			THIS::initialize(
		gr::GRAPH_S g,
		gr::VERT_S const & v0
		)
{
	for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
		(*it)->dfs._M_visited = false;

	v0->dfs._M_visited = true;
}
void			THIS::finalize(
		gr::GRAPH_S g,
		gr::VERT_S const & v0
		)
{
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
	v1->tree_arrange1.i  = v->tree_arrange2.i;
	v1->tree_arrange1.a1 = v->tree_arrange2.a1;
	v1->tree_arrange1.a1 = v->tree_arrange2.a2;
}
bool			THIS::descend(
		gr::VERT_S const & v0,
		gr::VERT_S const & v1)
{
	return true;
}







