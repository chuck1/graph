#include <gr/graph.hpp>

#include <gr/algo/dfs/DFS.hpp> // gr/algo/dfs/DFS.hpp_in

typedef gr::algo::dfs::DFS THIS;

THIS::DFS(gr::GRAPH_S const & g,
		gr::S_Vert const & root):
	_M_g(g),
	_M_root(root)
{
}
void		THIS::initialize()
{
	assert(_M_g->vert_find(_M_root) != _M_g->vert_end());

	for(auto it = _M_g->vert_begin(); it != _M_g->vert_end(); ++it)
	{
		(*it)->_M_visited = false;
	}
}
void		THIS::finalize()
{
}
void		THIS::run()
{
	initialize();
	_M_root->_M_visited = true;
	run(_M_root);
	finalize();
}
void		THIS::run(gr::S_Vert const & v)
{
	run_pre(v);
	
	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it;
		auto v1 = e->other(v);
		if(v1->_M_visited) continue;

		v1->_M_visited = true;

		visit(v, e, v1);

		run(v1);
	}
}
void		THIS::run_pre(gr::S_Vert const & v)
{
}



