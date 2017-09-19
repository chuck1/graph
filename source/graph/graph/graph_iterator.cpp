#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <deque>
#include <set>
#include <map>

#include <gr/algo/stack.hpp> // gr/algo/stack.hpp_in
#include <gr/algo/cycle.hpp> // gr/algo/cycle.hpp_in

#include <gr/algo/ftor_dfs/ftor_dfs.hpp> // gr/algo/ftor_dfs.hpp_in
#include <gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree.hpp> // gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree.hpp_in
#include <gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree_arrange.hpp> // gr/algo/ftor_dfs/ftor_dfs_vert2_spanning_tree_arrange.hpp_in

#include <gr/container/edge.hpp> // gr/container/edge.hpp_in
#include <gr/container/vert.hpp> // gr/container/vert.hpp_in
#include <gr/iterator/edge/EdgeGraphConst.hpp> // gr/iterator/edge_graph.hpp_in
#include <gr/iterator/edge/EdgeGraph.hpp> // gr/iterator/edge_graph.hpp_in
#include <gr/iterator/edge_vert.hpp> // gr/iterator/edge_vert.hpp_in
#include <gr/iterator/vert/VertComp.hpp> // gr/iterator/vert/VertGraphConst.hpp_in
#include <gr/iterator/vert/VertGraphConst.hpp> // gr/iterator/vert/VertGraphConst.hpp_in
#include <gr/iterator/vert/VertGraphAll.hpp> // gr/iterator/vert/VertGraphAll.hpp_in
#include <gr/plot/vert.hpp>
#include <gr/io.hpp> // gr/vert.hpp_in
#include <gr/pair.hpp> // gr/pair.hpp.in
#include <gr/pair_comp.hpp> // gr/pair_comp.hpp.in
#include <gr/vert/Vert.hpp> // gr/vert.hpp_in
#include <gr/edge.hpp> // gr/edge.hpp_in
#include <gr/edge_virt.hpp> // gr/edge_virt.hpp_in
#include <gr/layer.hpp>
#include <gr/util.hpp> // gr/util.hpp_in

#include <gr/graph.hpp> // gr/graph.hpp_in

typedef gr::graph THIS;

gr::iterator::vert::VertGraphConst	THIS::vert_begin() const
{
	return gr::iterator::vert::VertGraphConst(_M_verts, _M_verts.cbegin());
}
gr::iterator::vert::VertGraphConst	THIS::vert_end() const
{
	return gr::iterator::vert::VertGraphConst(_M_verts, _M_verts.cend());
}
gr::iterator::vert::VertGraph		THIS::vert_begin()
{
	return gr::iterator::vert::VertGraph(_M_verts, _M_verts.begin());
}
gr::iterator::vert::VertGraph		THIS::vert_end()
{
	return gr::iterator::vert::VertGraph(_M_verts, _M_verts.end());
}

gr::iterator::vert::VertGraphAll		THIS::vert_begin_all()
{
	return gr::iterator::vert::VertGraphAll(_M_verts, _M_verts.begin());
}
gr::iterator::vert::VertGraphAll		THIS::vert_end_all()
{
	return gr::iterator::vert::VertGraphAll(_M_verts, _M_verts.end());
}
gr::iterator::vert::VertGraphAll		THIS::vert_begin_all(gr::VERT_FUNC func)
{
	return gr::iterator::vert::VertGraphAll(_M_verts, _M_verts.begin(), func);
}
gr::iterator::vert::VertGraphAll		THIS::vert_end_all(gr::VERT_FUNC func)
{
	return gr::iterator::vert::VertGraphAll(_M_verts, _M_verts.end(), func);
}
gr::iterator::vert::VertGraph		THIS::vert_erase(gr::iterator::vert::VertGraph & i)
{
	gr::VERT_W w = *i;
	assert(!w.expired());

	auto ret = _M_verts.erase(i._M_j);

	// is this really necessary?
	//assert(w.expired());

	edge_erase();

	return gr::iterator::vert::VertGraph(_M_verts, ret);
}
gr::iterator::vert::VertGraph		THIS::vert_find(gr::VERT_S v)
{
	return gr::iterator::vert::VertGraph(_M_verts, _M_verts.find(v));
}
void					THIS::edge_erase()
{
	//std::cout << "edge erase" << std::endl;
	//for(auto j = vert_begin(); j != vert_end(); ++j)
	for(auto j = vert_begin_all(); j != vert_end_all(); ++j)
	{
		assert(*j);
		(*j)->edge_erase_disconnected();
	}
}
gr::iterator::edge::EdgeGraphPlot	THIS::edge_begin_plot()
{
	return gr::iterator::edge::EdgeGraphPlot(_M_verts, _M_verts.begin());
}
gr::iterator::edge::EdgeGraphPlot	THIS::edge_end_plot()
{
	return gr::iterator::edge::EdgeGraphPlot(_M_verts, _M_verts.end());
}
gr::iterator::vert::VertGraphPlot	THIS::vert_begin_plot()
{
	return gr::iterator::vert::VertGraphPlot(_M_verts, _M_verts.begin());
}
gr::iterator::vert::VertGraphPlot	THIS::vert_end_plot()
{
	return gr::iterator::vert::VertGraphPlot(_M_verts, _M_verts.end());
}
gr::iterator::edge::EdgeGraphConst	THIS::edge_begin() const
{
	return gr::iterator::edge::EdgeGraphConst(_M_verts, _M_verts.cbegin());
}
gr::iterator::edge::EdgeGraphConst	THIS::edge_end() const
{
	return gr::iterator::edge::EdgeGraphConst(_M_verts, _M_verts.cend());
}
gr::iterator::edge::EdgeGraph		THIS::edge_begin()
{
	return gr::iterator::edge::EdgeGraph(_M_verts, _M_verts.begin());
}
gr::iterator::edge::EdgeGraph		THIS::edge_end()
{
	return gr::iterator::edge::EdgeGraph(_M_verts, _M_verts.end());
}
gr::iterator::vert::VertComp		THIS::comp_vert_begin(int c)
{
	return gr::iterator::vert::VertComp(_M_verts, _M_verts.begin(), c);
}
gr::iterator::vert::VertComp		THIS::comp_vert_end(int c)
{
	return gr::iterator::vert::VertComp(_M_verts, _M_verts.end(), c);
}
void					THIS::edge_erase_util(gr::VERT_S & v0, gr::VERT_S & v1)
{
	auto i = vert_find(v0);

	if(i == vert_end()) throw std::exception();

	(*i)->edge_erase_util(v0, v1);

	/*
	gr::container::EDGE_S const & edges = (*i)->_M_edges;

	auto j = edges->find(v1);
	//auto j = std::find(edges.begin(), edges.end(), v1);

	if(j == edges->end()) throw std::exception();

	edges->erase(j);
	*/
	//for(auto j = edges.begin(); j != edges.end(); ++j) {
	//	gr::VERT_S w = j->first.lock();
	//}
}
void					THIS::edge_erase(gr::VERT_S & v0, gr::VERT_S & v1)
{
	edge_erase_util(v0, v1);
	edge_erase_util(v1, v0);
}
gr::iterator::edge::EdgeGraph		THIS::edge_erase(gr::iterator::edge::EdgeGraph i)
{
	gr::iterator::edge::EdgeGraph ret(i);

	gr::container::edge & container = *((*i._M_i)->_M_edges);

	ret._M_j = container.erase(i._M_j);

	ret.next();

	return ret;
}
unsigned int			THIS::vert_size()
{
	auto s2 = std::distance(vert_begin(), vert_end());
	return s2;
}
unsigned int			THIS::comp_vert_size(int c)
{
	auto s2 = std::distance(comp_vert_begin(c), comp_vert_end(c));
	return s2;
}
unsigned int			THIS::edge_size()
{
	auto s = std::distance(edge_begin(), edge_end());
	return s;
}

