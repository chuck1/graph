#include <gr/algo/stack.hpp>
#include <gr/graph/Graph.hpp>
#include <gr/vert/Vert.hpp>

#include <gr/algo/ftor_dfs/ftor_dfs.hpp> // gr/algo/ftor_dfs.hpp_in

typedef gr::algo::ftor_dfs::ftor_dfs_edge_cycle0 THIS;

#if 0
void	THIS::yield(
		gr::EDGE_S const & e0,
		gr::EDGE_S const & e1,
		algo::stack & stack)
{
	auto g = e0->v0()->get_graph();
	auto algo_g = g->_M_algo.graph;

	if(e1 < e0) return;

	if(e0->v0() == e1->v1()) {
		gr::algo::cycle c(stack.begin(), stack.end(), e1->v1());

		c.shift();

		auto ret = _M_cycles.insert(c);

		if(0) { // debugging
			// mark on algo graph
			if(ret.second) {
				g->_M_algo.graph_stack.back()->_M_dot.color="blue";
			} else {
				g->_M_algo.graph_stack.back()->_M_dot.color="red";
				++_M_count_insert_fail;
			}
		}
	} else {
		if(0) { // debugging
			g->_M_algo.graph_stack.back()->_M_dot.color="cyan";
		}
	}
}
#else
void	THIS::yield(
		gr::EDGE_S const & e0,
		gr::EDGE_S const & e1,
		algo::stack & stack)
{
	if(e1 < e0) return;

	if(e0->v0() == e1->v1())
	{
		gr::algo::cycle c(stack.begin(), stack.end(), e1->v1());

		c.shift();

		_M_cycles.insert(c);
	}
}
#endif
bool	THIS::check(
		gr::EDGE_S const & e0,
		gr::EDGE_S const & e1,
		algo::stack & stack)
{
	if(e1 < e0) return false;
	return true;
}
bool	THIS::descend(
		gr::EDGE_S const & e0,
		gr::EDGE_S const & e1,
		algo::stack & stack)
{
	return true;
}



