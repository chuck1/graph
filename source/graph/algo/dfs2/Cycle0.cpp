#include <gr/edge.hpp>
#include <gr/algo/cycle.hpp>

#include <gr/algo/dfs2/Cycle0.hpp> // gr/algo/dfs2/Cycle0.hpp_in

typedef gr::algo::dfs2::Cycle0 THIS;

THIS::Cycle0(
		gr::GRAPH_S const & g):
	gr::algo::dfs2::DFS(g)
{
}
void			THIS::run1(
		gr::S_Edge const & e
		)
{
	_M_stack.push_back(e);
	_M_e0 = e;
	run2(e);
	_M_stack.pop_back();

	e->swap();

	_M_stack.push_back(e);
	_M_e0 = e;
	run2(e);
	_M_stack.pop_back();
}
bool	THIS::check2(
		gr::S_Edge const & e0,
		gr::S_Edge const & e1
		)
{
	if(e1 < _M_e0) return false;

	if(_M_stack.contains(e1)) return false;

	_M_stack.push_back(e1);

	e1->orient_start(e0->v1());

	if(_M_e0->v0() == e1->v1())
	{
		gr::algo::cycle c(_M_stack.begin(), _M_stack.end(), e1->v1());

		c.shift();

		_M_cycles.insert(c);
	}

	return true;
}
void			THIS::post2(
		gr::S_Edge const & e1
		)
{
	_M_stack.pop_back();
}

