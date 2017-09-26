#include <gr/graph.hpp>

#include <gr/algo/dfs2/DFS.hpp> // gr/algo/dfs2/DFS.hpp_in

typedef gr::algo::dfs2::DFS THIS;

THIS::DFS(
		gr::GRAPH_S const & g):
	_M_g(g)
{
}
void			THIS::initialize()
{
}
void			THIS::finalize()
{
}
void			THIS::run()
{
	initialize();

	for(auto e : _M_g->edge_range())
	{
		run1(e);		

	}

	finalize();
}
void			THIS::run2(
		gr::S_Edge const & e0)
{
	auto v = e0->v1();

	for(auto e1 : v->edge_range())
	{
		auto v1 = e1->other(v);
		
		if(!check2(e0, e1)) continue;

		run2(e1);

		post2(e1);
	}
}

