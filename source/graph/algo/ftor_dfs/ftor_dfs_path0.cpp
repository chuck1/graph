
#include <gr/algo/stack.hpp>

#include <gr/algo/ftor_dfs/ftor_dfs.hpp> // gr/algo/ftor_dfs.hpp_in

void	gr::algo::ftor_dfs::ftor_dfs_path0::yield(
		gr::EDGE_S const & v0,
		gr::EDGE_S const & v1,
		algo::stack & stack)
{
	gr::QUEUE_EDGE c(stack.begin(), stack.end());

	auto ret = _M_paths.insert(c);
	
	if(!ret.second) ++_M_count_insert_fail;
}
bool	gr::algo::ftor_dfs::ftor_dfs_path0::descend(
		gr::EDGE_S const & v0,
		gr::EDGE_S const & v1,
		algo::stack & stack)
{
	return true;
}




