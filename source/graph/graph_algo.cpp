#include <cassert>

#include <gr/algo/ftor_dfs/ftor_dfs_vert2.hpp> // gr/algo/ftor_dfs/ftor_dfs_vert2.hpp_in

#include <gr/graph.hpp> // gr/graph.hpp_in

typedef gr::graph THIS;

void				THIS::depth_first_search3(
		gr::VERT_S const & v0,
		gr::VERT_S const & v,
		//STACK_VERT & stack,
		algo::ftor_dfs::ftor_dfs_vert2 * ftor)
{
	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it; assert(e);

		auto v1 = e->other(v);
		
		if(!ftor->check(v0, v1)) continue;

		ftor->yield(v0, v, v1, e);

		if(ftor->descend(v0, v1))
			depth_first_search3(v0, v1, ftor);
	}
}
void				THIS::depth_first_search3(
		gr::algo::ftor_dfs::ftor_dfs_vert2 * ftor, 
		gr::VERT_S const & v)
{
	depth_first_search3(v, v, ftor);
}
void				THIS::depth_first_search3(
		gr::algo::ftor_dfs::ftor_dfs_vert2 * ftor)
{
	for(auto it = vert_begin(); it != vert_end(); ++it)
		depth_first_search3(ftor, *it);
}



