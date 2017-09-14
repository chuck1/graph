
#include <gr/algo/stack.hpp>

#include <gr/algo/ftor_dfs/ftor_dfs.hpp> // gr/algo/ftor_dfs.hpp_in

typedef gr::algo::ftor_dfs::ftor_dfs_path1 THIS;

void	THIS::yield(
		gr::VERT_S const & v0,
		gr::VERT_S const & v1,
		algo::stack & stack)
{
	if(stack.counter(v1) > 2) return;

	gr::QUEUE_EDGE c(stack.begin(), stack.end());

	auto ret = _M_paths.insert(c);
	
	if(!ret.second) ++_M_count_insert_fail;
}
bool	THIS::descend(
		gr::VERT_S const & v0,
		gr::VERT_S const & v1,
		algo::stack & stack)
{
	if(stack.counter(v1) > 2) return false;
	return true;
}



