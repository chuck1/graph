#include <gr/algo/stack.hpp>
#include <gr/graph/Graph.hpp>
#include <gr/vert/Vert.hpp>

#include <gr/algo/ftor_dfs/ftor_dfs.hpp> // gr/algo/ftor_dfs.hpp_in

typedef gr::algo::ftor_dfs::ftor_dfs_vert_cycle0 THIS;

void	THIS::yield(
		gr::VERT_S const & v0,
		gr::VERT_S const & v1,
		algo::stack & stack)
{
	auto g = v1->get_graph();
	auto algo_g = v1->get_graph()->_M_algo.graph;
	
	if(v1 < v0) {
		g->_M_algo.graph_stack.back()->_M_dot.color="magenta";
		return;
	}

	if(stack.counter(v1) > 2) {
		g->_M_algo.graph_stack.back()->_M_dot.color="orange";
		return;
	}

	if(v0 == v1) {
		gr::algo::cycle c(stack.begin(), stack.end(), v1);

		c.shift();

		auto ret = _M_cycles.insert(c);

		if(1) { // debugging
			// mark on algo graph
			if(ret.second) {
				g->_M_algo.graph_stack.back()->_M_dot.color="blue";
			} else {
				g->_M_algo.graph_stack.back()->_M_dot.color="red";
				++_M_count_insert_fail;
			}
		}
	} else {
		if(1) { // debugging
			g->_M_algo.graph_stack.back()->_M_dot.color="cyan";
		}
	}
}
bool	THIS::descend(
		gr::VERT_S const & v0,
		gr::VERT_S const & v1,
		algo::stack & stack)
{
	if(v1 < v0) return false;

	if(stack.counter(v1) > 2) return false;

	return true;
}



