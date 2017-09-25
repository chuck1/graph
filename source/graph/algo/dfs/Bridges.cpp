#include <gr/vert/Vert.hpp>

#include <gr/algo/dfs/Bridges.hpp> // gr/algo/dfs/Bridges.hpp_in

typedef gr::algo::dfs::Bridges THIS;

THIS::Bridges(gr::GRAPH_S const & g):
	gr::algo::dfs::DFS(g),
	_M_t(0)
{
}
void			THIS::visit(
		gr::S_Vert const & v0)
{
	v0->bridge._M_disc = v0->bridge._M_low = ++_M_t;
}
void			THIS::visit(
		gr::S_Vert const & v0,
		gr::S_Edge const &,
		gr::S_Vert const & v1)
{
	v1->bridge._M_parent = v0;

	visit(v0);
}
void			THIS::visit_post(
		gr::S_Vert const & v0,
		gr::S_Edge const & e,
		gr::S_Vert const & v1)
{
	v0->bridge._M_low = std::min(v0->bridge._M_low, v1->bridge._M_low);

	if(v1->bridge._M_low > v0->bridge._M_disc)
	{
		_M_edges.push_back(e);
	}
}
void			THIS::revisit(
		gr::S_Vert const & v0,
		gr::S_Edge const &,
		gr::S_Vert const & v1)
{
	if(v1 != v0->bridge._M_parent.lock())
	{
		v0->bridge._M_low = std::min(v0->bridge._M_low, v1->bridge._M_disc);
	}
}

/*

void				bridges_sub(gr::VERT_S const & n, int & t, std::vector<gr::EDGE_S> & ret)
{
	n->bridge._M_visited = true;

	n->bridge._M_disc = n->bridge._M_low = ++t;

	for(auto i = n->edge_begin(); i != n->edge_end(); ++i)
	{
		auto e = *i;
		gr::VERT_S const & v = e->other(n);

		assert(v);

		if(!v->bridge._M_visited)
		{
			v->bridge._M_parent = n;

			bridges_sub(v, t, ret);

			n->bridge._M_low = std::min(n->bridge._M_low, v->bridge._M_low);

			if(v->bridge._M_low > n->bridge._M_disc)
			{
				ret.push_back(e);
			}
		}
		else if(v != n->bridge._M_parent.lock())
		{
			n->bridge._M_low = std::min(n->bridge._M_low, v->bridge._M_disc);
		}
	}
}
std::vector<gr::EDGE_S>		bridges()
{
	std::vector<gr::EDGE_S> ret;

	int t = 0;

	// initialize
	for(auto i = _M_verts.begin(); i != _M_verts.end(); ++i)
	{
		(*i)->bridge._M_visited = false;
	}

	for(auto i = _M_verts.begin(); i != _M_verts.end(); ++i)
	{
		if((*i)->bridge._M_visited == false) {
			bridges_sub(*i, t, ret);
		}
	}

	std::cout << "bridges: " << ret.size() << std::endl;

	return ret;
}
*/

