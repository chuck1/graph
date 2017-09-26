#include <gr/graph.hpp>

#include <gr/algo/dfs/DFS.hpp> // gr/algo/dfs/DFS.hpp_in

typedef gr::algo::dfs::DFS THIS;

THIS::DFS(
		gr::GRAPH_S const & g):
	_M_g(g)
{
}
THIS::DFS(
		gr::GRAPH_S const & g,
		gr::S_Vert const & root):
	_M_g(g),
	_M_root(root)
{
}
void			THIS::initialize()
{
	if(_M_root)
		assert(_M_g->vert_find(_M_root) != _M_g->vert_end());

	for(auto it = _M_g->vert_begin(); it != _M_g->vert_end(); ++it)
	{
		(*it)->_M_visited = false;
	}
}
void			THIS::finalize()
{
}
void			THIS::run()
{
	initialize();

	if(_M_root)
	{
		_M_root->_M_visited = true;

		visit(_M_root);
		
		run(_M_root);
	}
	else
	{
		for(auto v : _M_g->vert_range())
		{
			if(v->_M_visited) continue;

			v->_M_visited = true;

			visit(v);

			run(v);
		}
	}

	finalize();
}
void			THIS::run(
		gr::S_Vert const & v)
{
	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it;
		auto v1 = e->other(v);

		if(v1->_M_visited)
		{
			revisit(v, e, v1);
		}
		else
		{
			v1->_M_visited = true;

			visit(v, e, v1);

			run(v1);

			visit_post(v, e, v1);
		}
	}
}
void			THIS::visit(gr::S_Vert const & v)
{
}
void			THIS::visit_post(
		gr::S_Vert const &,
		gr::S_Edge const &,
		gr::S_Vert const &)
{
}
void			THIS::revisit(
		gr::S_Vert const &,
		gr::S_Edge const &,
		gr::S_Vert const &)
{
}


