#include <gr/graph.hpp>

#include <gr/algo/for_each_leaf/ForEachLeaf.hpp> // gr/algo/for_each_leaf/ForEachLeaf.hpp_in

typedef gr::algo::for_each_leaf::ForEachLeaf THIS;

THIS::ForEachLeaf(gr::GRAPH_S const & g):
	_M_g(g),
	_M_count(0)
{
}
void			THIS::run()
{
	for(auto v : _M_g->vert_range())
	{
		if(v->edge_size() == 1)
		{
			do_leaf(v, *v->edge_begin());
			++_M_count;
		}
	}
}
void			THIS::run_recursive()
{
	unsigned int c = _M_count;
	run();
	while(_M_count > c)
	{
		c = _M_count;
		run();
	}
}

