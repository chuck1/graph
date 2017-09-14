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

#include <gr/container/edge.hpp> // gr/container/edge.hpp.in
#include <gr/container/vert.hpp> // gr/container/vert.hpp.in
#include <gr/iterator/edge_graph.hpp> // gr/iterator/edge_graph.hpp_in
#include <gr/iterator/edge_vert.hpp> // gr/iterator/edge_vert.hpp_in
#include <gr/plot/vert.hpp>
#include <gr/io.hpp> // gr/vert.hpp_in
#include <gr/pair.hpp> // gr/pair.hpp.in
#include <gr/pair_comp.hpp> // gr/pair_comp.hpp.in
#include <gr/vert.hpp> // gr/vert.hpp_in
#include <gr/edge.hpp> // gr/edge.hpp_in
#include <gr/edge_virt.hpp> // gr/edge_virt.hpp_in
#include <gr/layer.hpp>
#include <gr/util.hpp> // gr/util.hpp_in

#include <gr/graph.hpp> // gr/graph.hpp_in

typedef gr::graph THIS;

THIS::graph()
{
}
void				THIS::clear()
{
	_M_verts.clear();
}
gr::EDGE_S			THIS::add_edge(gr::VERT_S v0, gr::VERT_S v1)
{
	auto e = std::make_shared<gr::edge>(v0, v1);
	// iter adds the vert to the graph's container if not already there
	(*iter(v0))->add_edge(e);
	(*iter(v1))->add_edge(e);
	return e;
}
gr::EDGE_S			THIS::add_virtual_edge(gr::VERT_S v0, gr::VERT_S v1, gr::VERT_S v)
{
	auto e = std::make_shared<gr::edge_virt>(v0, v1, v);
	// iter adds the vert to the graph's container if not already there
	(*iter(v0))->add_edge(e);
	(*iter(v1))->add_edge(e);
	return e;
}
void				THIS::add_edge(gr::EDGE_S e)
{
	// iter adds the vert to the graph's container if not already there
	(*iter(e->v0()))->add_edge(e);
	(*iter(e->v1()))->add_edge(e);
}
gr::iterator::vert_graph	THIS::iter(gr::VERT_S v)
{
	auto it = vert_find(v);

	if(it == vert_end())
	{
		CONT_VERT::value_type p(v);

		return gr::iterator::vert_graph(_M_verts, _M_verts.insert(_M_verts.begin(), p));
	}

	return it;
}
gr::iterator::vert_graph		THIS::vert_begin()
{
	return gr::iterator::vert_graph(_M_verts, _M_verts.begin());
}
gr::iterator::vert_graph		THIS::vert_end()
{
	return gr::iterator::vert_graph(_M_verts, _M_verts.end());
}
gr::iterator::vert_graph_all		THIS::vert_begin_all()
{
	return gr::iterator::vert_graph_all(_M_verts, _M_verts.begin());
}
gr::iterator::vert_graph_all		THIS::vert_end_all()
{
	return gr::iterator::vert_graph_all(_M_verts, _M_verts.end());
}
gr::iterator::vert_graph_all		THIS::vert_begin_all(gr::VERT_FUNC func)
{
	return gr::iterator::vert_graph_all(_M_verts, _M_verts.begin(), func);
}
gr::iterator::vert_graph_all		THIS::vert_end_all(gr::VERT_FUNC func)
{
	return gr::iterator::vert_graph_all(_M_verts, _M_verts.end(), func);
}


gr::iterator::vert_graph		THIS::vert_erase(gr::iterator::vert_graph & i)
{
	gr::VERT_W w = *i;
	assert(!w.expired());

	auto ret = _M_verts.erase(i._M_j);

	// is this really necessary?
	//assert(w.expired());

	edge_erase();

	return gr::iterator::vert_graph(_M_verts, ret);
}
gr::iterator::vert_graph		THIS::vert_find(gr::VERT_S v)
{
	return gr::iterator::vert_graph(_M_verts, _M_verts.find(v));
}
void					THIS::edge_erase()
{
	//std::cout << "edge erase" << std::endl;
	for(auto j = vert_begin(); j != vert_end(); ++j) {
		assert(*j);
		(*j)->edge_erase_disconnected();
	}
}
gr::iterator::edge_graph		THIS::edge_begin()
{
	return gr::iterator::edge_graph(_M_verts, _M_verts.begin());
}
gr::iterator::edge_graph		THIS::edge_end()
{
	return gr::iterator::edge_graph(_M_verts, _M_verts.end());
}
gr::iterator::vert_comp			THIS::comp_vert_begin(int c)
{
	return gr::iterator::vert_comp(_M_verts, _M_verts.begin(), c);
}
gr::iterator::vert_comp			THIS::comp_vert_end(int c)
{
	return gr::iterator::vert_comp(_M_verts, _M_verts.end(), c);
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
void				THIS::edge_erase(gr::VERT_S & v0, gr::VERT_S & v1)
{
	edge_erase_util(v0, v1);
	edge_erase_util(v1, v0);
}
gr::iterator::edge_graph	THIS::edge_erase(gr::iterator::edge_graph i)
{
	gr::iterator::edge_graph ret(i);

	gr::container::edge & container = *((*i._M_i)->_M_edges);

	ret._M_j = container.erase(i._M_j);

	ret.next();

	return ret;
}
void				THIS::distance_util(gr::VERT_S u)
{
	int d = u->dist._M_distance + 1.0f;

	for(auto it = u->edge_begin(); it != u->edge_end();)
	{	
		auto e = *it;
		gr::VERT_S const & v = e->other(u);

		if(!v)
		{
			// clean up
			it = u->edge_erase(it);
		}
		else
		{
			if((v->dist._M_distance < 0) || (v->dist._M_distance > d))
			{
				v->dist._M_distance = d;

				distance_util(v);
			}
			++it;
		}
	}
}
void				THIS::distance(gr::VERT_S const & v0)
{
	for(auto it = vert_begin(); it != vert_end(); ++it)
	{
		(*it)->dist._M_distance = -1.0;
	}

	auto it = vert_find(v0);

	if(it == vert_end()) {
		std::cout << "graph::distance v0 not found" << std::endl;
		return;
	}

	gr::VERT_S const & v = *it;

	v->dist._M_distance = 0.0;

	distance_util(v);
}
/*
std::ostream & operator<<(std::ostream & os, gr::algo::cycle const & cycle)
{
	for(auto it = cycle.begin(); it != cycle.end(); ++it)
	{
		char buffer[128];
		auto e = (*it);
		sprintf(buffer, "(%s)%s(%s) - ", (*it)->v0()->name().c_str(), e->name().c_str(), (*it)->v1()->name().c_str());
		std::cout << buffer;
	}
	std::cout << std::endl;
}
*/
template<typename T>
void print_cycle(T cycle)
{
	//std::cout << cycle.front()->v0()->name();
	for(auto it = cycle.begin(); it != cycle.end(); ++it)
	{
		char buffer[128];
		auto e = (*it);
		sprintf(buffer, "(%s)%s(%s) - ", (*it)->v0()->name().c_str(), e->name().c_str(), (*it)->v1()->name().c_str());
		std::cout << buffer;
	}
	std::cout << std::endl;
}
template<typename T>
void	print_vert_container(T & t)
{
	for(auto it = t.begin(); it != t.end(); ++it)
	{
		std::cout << (*it)->name() << " ";
	}
	std::cout << std::endl;
}


bool		gr::algo::ftor_dfs::less_queue_edge::operator()(QUEUE_EDGE const & c0, QUEUE_EDGE const & c1)
{
	if(c0.size() == c1.size())
	{
		auto it1 = c1.begin();
		auto it0 = c0.begin();
		for(; it0 != c0.end(); ++it0, ++it1)
		{
			gr::edge & e0 = *(*it0);
			gr::edge & e1 = *(*it1);
			if(e0 != e1) return e0 < e1;
		}
		return false;
	}

	return c0.size() < c1.size();
}
void		rotate_cycle(gr::QUEUE_EDGE & c)
{
	/**
	 * shift a cycle until the lowerest edge is at the front
	 */

	// find lowerest edge
	auto it0 = c.begin();
	auto e0 = *it0;

	for(auto it = it0 + 1; it != c.end(); ++it)
	{
		auto e = *it;
		if((*e) < (*e0))
		{
			it0 = it;
			e0 = *it0;
		}
	}

	//int d = std::distance(it0, c.end());

	int s = c.size();

	//printf("rotate d=%i s=%i\n", d, s);

	// shift
	//
	std::deque<gr::EDGE_S> temp(it0, c.end());
	//
	c.insert(c.begin(), temp.begin(), temp.end());

	c.resize(s);
}
template<typename C>
bool contains_vert(C & c, gr::VERT_S const & v)
{
	for(auto e : c)
	{
		if(e->contains(v)) return true;
	}
	return false;
}
	template<typename C, typename T>
bool contains(C c, T const & t)
{
	return !(std::find(c.begin(), c.end(), t) == c.end());
}
void				THIS::depth_first_search(
		gr::EDGE_S const & e0,
		gr::EDGE_S const & e,
		algo::stack & stack,
		algo::ftor_dfs::ftor_dfs_edge * ftor)
{
	auto v = e->v1();

	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e1 = *it; assert(e1);

		auto v1 = e1->other(v); assert(v1);

		if(contains(stack, e1)) continue;

		if(!ftor->check(e0, e1, stack)) continue;

		stack.push_back(e1);

		e1->orient_start(v);

		ftor->yield(e0, e1, stack);

		if(ftor->descend(e0, e1, stack))
			depth_first_search(e0, e1, stack, ftor);

		stack.pop_back();
	}
}
void				THIS::depth_first_search(
		algo::ftor_dfs::ftor_dfs_edge * ftor,
		gr::EDGE_S const & e)
{
	gr::algo::stack stack;

	stack.push_back(e);

	depth_first_search(e, e, stack, ftor);
}
void				THIS::depth_first_search(
		algo::ftor_dfs::ftor_dfs_edge * ftor)
{
	for(auto it = edge_begin(); it != edge_end(); ++it)
	{
		auto e = *it;
		depth_first_search(ftor, e);
		e->swap();
		depth_first_search(ftor, e);
	}
}
void				THIS::depth_first_search2(
		gr::EDGE_S const & e0,
		gr::EDGE_S const & e,
		algo::stack & stack,
		STACK_VERT & stack_vert,
		algo::ftor_dfs::ftor_dfs_edge * ftor)
{
	auto v = e->v1();

	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e1 = *it; assert(e1);

		if(contains(stack, e1)) continue;

		if(contains(stack_vert, v)) continue;

		if(ftor->check(e0, e1, stack))
		{
			stack.push_back(e1);
			stack_vert.push_back(v);

			//print_vert_container(stack_vert);

			e1->orient_start(v);

			ftor->yield(e0, e1, stack);

			if(ftor->descend(e0, e1, stack))
				depth_first_search2(e0, e1, stack, stack_vert, ftor);

			stack_vert.pop_back();
			stack.pop_back();
		}
	}
}
void				THIS::depth_first_search2(
		algo::ftor_dfs::ftor_dfs_edge * ftor,
		gr::EDGE_S const & e)
{
	gr::algo::stack stack;
	STACK_VERT stack_vert;

	stack.push_back(e);
	stack_vert.push_back(e->v0());

	depth_first_search2(e, e, stack, stack_vert, ftor);
}
void				THIS::depth_first_search2(
		algo::ftor_dfs::ftor_dfs_edge * ftor)
{
	for(auto it = edge_begin(); it != edge_end(); ++it)
	{
		auto e = *it;
		depth_first_search2(ftor, e);
		e->swap();
		depth_first_search2(ftor, e);
	}
}
void				THIS::depth_first_search(
		gr::VERT_S const & v0,
		gr::VERT_S const & v,
		algo::stack & stack,
		algo::ftor_dfs::ftor_dfs_vert * ftor)
{
	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it;
		assert(e);

		auto v1 = e->other(v);

		// debug graph
		auto algo_v = std::make_shared<gr::plot::vert>(_M_algo.graph, v1->name() + "\ne=" + std::to_string(v1->edge_size())); //v1->copy(_M_algo.graph);
		auto algo_e = _M_algo.graph->add_edge(_M_algo.graph_head, algo_v);
		_M_algo.graph_stack.push_back(algo_e);
		_M_algo.graph_head = algo_v;

		if(!contains(stack, e))
		{
			stack.push_back(e);

			e->orient_start(v);

			ftor->yield(v0, v1, stack);

			if(ftor->descend(v0, v1, stack))
				depth_first_search(v0, v1, stack, ftor);

			stack.pop_back();
		}
		else
		{
			// debugging
			algo_e->_M_dot.color = "green";
		}

		_M_algo.graph_head = _M_algo.graph_stack.back()->other(_M_algo.graph_head);
		_M_algo.graph_stack.pop_back();
	}
}
void				THIS::depth_first_search(
		gr::algo::ftor_dfs::ftor_dfs_vert * ftor, 
		gr::VERT_S const & v)
{
	gr::algo::stack stack;

	if(1) { // debugging graph
		_M_algo.graph.reset(new gr::digraph());
		_M_algo.graph_stack.clear();
		_M_algo.graph_head = *_M_algo.graph->iter(std::make_shared<gr::plot::vert>(_M_algo.graph, v->name()));
	}

	depth_first_search(v, v, stack, ftor);

	//_M_algo.graph->dot();
}
void				THIS::depth_first_search(
		algo::ftor_dfs::ftor_dfs_vert * ftor)
{
	for(auto it = vert_begin(); it != vert_end(); ++it)
	{
		depth_first_search(ftor, *it);

		//ftor->_M_verts_completed.insert(*it);
	}
}
void				THIS::mark_leaves_recursive(gr::LAYER_S layer)
{
	unsigned int C = 0;
	while(true)
	{
		unsigned int c = 0;

		auto f = [&](gr::VERT_S const & v, gr::EDGE_S const &)
		{
			v->_M_layer = layer;
			++c;
		};

		for_each_leaf(f);

		C += c;
		if(c == 0) break;
	}
	log<0>() << "mark leaves " << C << std::endl;
}
gr::algo::SET_CYCLE		THIS::cycles0()
{
	std::cout << "cycles0 e: " << edge_size() << " v: " << vert_size() << std::endl;

	// preliminary
	auto layer = create_layer(false);
	mark_leaves_recursive(layer);

	mark_bridges(layer);

	int nc = components();
	for(int c = 0; c < nc; ++c)
		std::cout << "    component " << c << " v: " << comp_vert_size(c) << std::endl;

	std::cout << "cycles0 e: " << edge_size() << " v: " << vert_size() << std::endl;

	// actual algorithm

	gr::algo::ftor_dfs::ftor_dfs_edge_cycle0 ftor;

	depth_first_search(&ftor);

	printf("fail inserts = %i\n", ftor._M_count_insert_fail);

	// cleanup
	layer->_M_enabled = true;

	return ftor._M_cycles;
}
gr::algo::SET_CYCLE		THIS::cycles1()
{
	std::cout << "cycles1 e: " << edge_size() << " v: " << vert_size() << std::endl;

	// preliminary
	auto layer = create_layer(false);
	mark_leaves_recursive(layer);

	mark_bridges(layer);

	int nc = components();
	for(int c = 0; c < nc; ++c)
		std::cout << "    component " << c << " v: " << comp_vert_size(c) << std::endl;

	std::cout << "cycles1 e: " << edge_size() << " v: " << vert_size() << std::endl;

	// actual algorithm

	gr::algo::ftor_dfs::ftor_dfs_edge_cycle0 ftor;

	depth_first_search2(&ftor);

	printf("fail inserts = %i\n", ftor._M_count_insert_fail);

	// cleanup
	layer->_M_enabled = true;

	return ftor._M_cycles;
}
gr::algo::SET_CYCLE		THIS::cycles0_vert()
{
	gr::algo::ftor_dfs::ftor_dfs_vert_cycle0 ftor;

	depth_first_search(&ftor);

	printf("fail inserts = %i\n", ftor._M_count_insert_fail);

	return ftor._M_cycles;
}
gr::algo::ftor_dfs::SET_QUEUE_EDGE	THIS::paths0()
{
	gr::algo::ftor_dfs::ftor_dfs_path0 ftor;

	depth_first_search(&ftor);

	printf("fail inserts = %i\n", ftor._M_count_insert_fail);

	return ftor._M_paths;
}
gr::algo::ftor_dfs::SET_QUEUE_EDGE	THIS::paths1()
{
	gr::algo::ftor_dfs::ftor_dfs_path1 ftor;

	depth_first_search(&ftor);

	printf("fail inserts = %i\n", ftor._M_count_insert_fail);

	return ftor._M_paths;
}
void				THIS::vert_erase_layer(unsigned int l)
{
	if(l > _M_layers.size()) throw std::exception();

	auto const & layer = _M_layers[l];

	for(auto i = vert_begin(); i != vert_end();)
	{
		auto v = *i;
		if(!v->_M_layer.expired())
		{
			if(v->_M_layer.lock() == layer)
			{
				i = vert_erase(i);
				continue;
			}
		}

		++i;
	}
}
void				THIS::bridges_sub(gr::VERT_S const & n, int & t, std::vector<gr::EDGE_S> & ret)
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
void				THIS::mark_bridges(gr::LAYER_S layer)
{
	auto l = bridges();
	for(auto e : l)
	{
		e->_M_layer = layer;
	}
}
std::vector<gr::EDGE_S>		THIS::bridges()
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
std::string	next_graph_filename()
{
	static int a = 0;

	char buf[128];
	sprintf(buf, "build/dot/graph_%04i.dot", a);
	++a;
	return buf;
}
void				THIS::dot()
{
	dot(next_graph_filename());
}
void				THIS::dot(gr::VERT_S const & v)
{
	distance(v);

	dot(next_graph_filename());
}
void				THIS::dot(std::string filename, gr::VERT_S const & v)
{
	distance(v);

	dot(filename);
}
void				THIS::dot_sub1(std::ostream & of)
{
	for(auto i = edge_begin(); i != edge_end(); ++i)
	{
		auto e = *i;
		of << e->dot() << std::endl;
	}

	for(auto i = vert_begin(); i != vert_end(); ++i) {
		of << (*i)->dot() << std::endl;
	}
}
void				THIS::dot_sub0(std::ostream & of)
{
	of << "#neato" << std::endl;
	of << "graph {" << std::endl;

	// overlap=false overrides manual node positions
	//of << "overlap=false" << std::endl;

	of << "splines=false" << std::endl;

	dot_sub1(of);

	of << "}" << std::endl;
}
void				THIS::dot(std::string filename)
{
	std::ofstream of;
	of.open(filename);

	dot_sub0(of);
}
void				THIS::components_util(gr::VERT_S const & u, int c)
{
	assert(u);

	u->comp._M_visited = true;
	u->comp._M_c = c;

	for(auto i = u->edge_begin(); i != u->edge_end(); ++i)
	{
		auto e = *i;

		// what?
		unsigned int d = std::distance(i, u->edge_end()); assert(d!=0);

		gr::VERT_S const & v = e->other(u);

		// why?
		//assert(v != u);

		assert(v);

		if(!(v->comp._M_visited))
		{
			components_util(v, c);
		}
	}
}
int				THIS::components()
{
	edge_erase();

	// initialize
	for(auto i = vert_begin(); i != vert_end(); ++i) {
		(*i)->comp._M_visited = false;
		(*i)->comp._M_c = -1;
	}

	int c = 0;

	for(auto i = vert_begin(); i != vert_end(); ++i) {
		gr::VERT_S const & u = *i;

		assert(u);

		if(!(u->comp._M_visited)) {
			components_util(u, c);
			++c;
		}
	}

	if(0) {
		std::cout << "verts" << std::endl;
		for(auto i = vert_begin(); i != vert_end(); ++i) {
			std::cout << "  " << (*i)->comp._M_c << " " << (*i)->comp._M_c << std::endl;
		}
		std::cout << "comps" << std::endl;
		for(int i = 0; i < c; ++i) {
			auto s = std::distance(comp_vert_begin(i), comp_vert_end(i));
			std::cout << "  " << i << " " << s << std::endl;
		}
	}
	return c;
}
void				THIS::component(int c)
{
	for(auto it = vert_begin(); it != vert_end();) {

		gr::VERT_S const & u = *it;

		assert(u);

		if(u->comp._M_c == c) {
			++it;
		} else {
			it = vert_erase(it);
		}
	}
}
void				THIS::edge_enable()
{
	edge_erase();

	for(auto i = edge_begin(); i != edge_end(); ++i) 
	{
		auto e = *i;
		e->_M_layer.reset();
	}
}
void				THIS::layer_move(unsigned int i0, unsigned int i1)
{
	// move all verts in i0 to i1

	if(i0 < _M_layers.size()) throw std::exception();
	if(i1 < _M_layers.size()) throw std::exception();

	auto const & l0 = _M_layers[i0];
	auto const & l1 = _M_layers[i1];

	assert(l0);
	assert(l1);

	for(auto i = vert_begin_all(); i != vert_end_all(); ++i) {
		auto const & u = *i;

		if(!u->_M_layer.expired()) {
			if(u->_M_layer.lock() == l0) {
				u->_M_layer = l1;
			}
		}
	}
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
void				THIS::for_each_leaf(std::function<void(gr::VERT_S const &, gr::EDGE_S const &)> func)
{
	for(auto i = vert_begin(); i != vert_end(); ++i)
	{
		gr::VERT_S const & v = *i;
		if(v->edge_size() == 1)
		{
			func(v, *v->edge_begin());
		}
	}
}
gr::LAYER_S			THIS::create_layer(bool e)
{
	auto layer = std::make_shared<gr::layer>();
	layer->_M_enabled = e;
	_M_layers.push_back(layer);
	return layer;
}

bool check_path(std::deque<gr::EDGE_S> & stack)
{
	for(auto it = stack.begin(); it != stack.end(); ++it)
	{
		auto e = *it;
		e->v0()->algo.counter = 0;
		e->v1()->algo.counter = 0;
	}

	for(auto it = stack.begin(); it != stack.end(); ++it)
	{
		auto e = *it;
		int & c0 = e->v0()->algo.counter;
		int & c1 = e->v1()->algo.counter;
		++c0;
		++c1;
		if(c0 > 2) return false;
		if(c1 > 2) return false;
	}

	auto e = stack.front();
	if(e->v0()->algo.counter > 1) return false;

	e = stack.back();
	if(e->v1()->algo.counter > 1) return false;

	return true;
}
gr::GRAPH_S	THIS::copy()
{
	auto g = std::make_shared<gr::graph>();

	std::map<gr::VERT_S, gr::VERT_S> m;

	for(auto it = vert_begin(); it != vert_end(); ++it)
	{
		m[*it] = std::make_shared<gr::vert>(g);
	}

	for(auto it = edge_begin(); it != edge_end(); ++it)
	{
		g->add_edge(m[(*it)->v0()], m[(*it)->v1()]);
	}

	return g;
}
bool		THIS::add_virtual_edges(gr::LAYER_S layer)
{
	bool b = false;

	for(auto it = vert_begin(); it != vert_end(); ++it)
	{
		auto v = *it;
		if(v->edge_size() == 2)
		{
			auto it1 = v->edge_begin();
			auto e0 = *it1;
			++it1;
			auto e1 = *it1;

			auto v0 = e0->other(v);
			auto v1 = e1->other(v);

			add_virtual_edge(v0, v1, v);

			// remove middle vertex
			v->_M_layer = layer;

			b = true;
		}
	}

	return b;
}
void		THIS::simplify()
{
	std::cout << "graph::simplify" << std::endl;

	auto layer = create_layer(false);

	// remove leaves	
	mark_leaves_recursive(layer);

	// virtual edges
	while(add_virtual_edges(layer));

	// bridges
	mark_bridges(layer);

	int nc = components();
	for(int c = 0; c < nc; ++c)
		std::cout << "    component " << c << " v: " << comp_vert_size(c) << std::endl;

}
std::string			THIS::dot_edge_symbol() { return " -- "; }


void				gr::digraph::dot_sub0(std::ostream & of)
{
	of << "#dot" << std::endl;
	of << "digraph {" << std::endl;
	of << "overlap=false" << std::endl;
	of << "splines=false" << std::endl;

	dot_sub1(of);

	of << "}" << std::endl;
}
std::string			gr::digraph::dot_edge_symbol() { return " -> "; }

bool	cycle_exists_(gr::VERT_S const & v0, gr::VERT_S const & v)
{
	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it;

		if(e->_M_visited) continue;
		e->_M_visited = true;

		auto v1 = e->other(v);
		if(*v1 == *v0) return true;
		cycle_exists_(v0, v1);
	}

	return false;
}
bool				THIS::cycle_exists(gr::EDGE_S const & e)
{
	// initialize
	for(auto it = edge_begin(); it != edge_end(); ++it)
	{
		(*it)->_M_visited = false;
	}

	auto v0 = e->v0();
	auto v1 = e->v1();

	e->_M_visited = true;

	return cycle_exists_(v0, v1);
}
void				THIS::arrange()
{
	auto c = cycles0();
	gr::arrange_dot(c);
}
void				arrange_radially(
		gr::VERT_S v, 
		Eigen::Vector2f o, 
		int i, int n, float a1, float a2, float r)
{
	float da = (a2 - a1) / (float)n;

	float a = a1 + da * ((float)i + 0.5);
	
	printf("arrange radially %i %i %f %f a = %f\n", i, n, a1, a2, a);

	Eigen::Vector2f d(cos(a), sin(a));
	d *= r;
	
	Eigen::Vector2f p = d + o;

	printf("    o %f %f\n", o[0], o[1]);
	printf("    d %f %f\n", d[0], d[1]);
	printf("    p %f %f\n", p[0], p[1]);
	
	v->_M_dot.p = p;

	std::stringstream ss;
	ss << v->_M_dot.p[0] << "," << v->_M_dot.p[1] << "!";
	v->_M_dot.pos = ss.str();
}
void				arrange_tree(
		gr::VERT_S prev,
		gr::VERT_S v,
		float a1,
		float a2
		)
{
	unsigned int n;
	if(*v == *prev)
	       	n = v->edge_size();
	else
	       	n = v->edge_size() - 1;

	unsigned int i = 0;

	float da = (a2 - a1) / (float)n;

	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it;
		auto v1 = e->other(v);
		if(*v1 == *prev) continue;

		arrange_radially(v1, v->_M_dot.p, i, n, a1, a2, 1);

		arrange_tree(v, v1, a1 + i * da, a1 + (i+1) * da);

		++i;
	}
}
void				THIS::arrange2(gr::VERT_S root)
{
	//auto g = copy();
	auto g = shared_from_this();

	// g->spanning_tree();
	auto layer = std::make_shared<gr::layer>(true);
	{
		auto f = new gr::algo::ftor_dfs::ftor_dfs_vert2_spanning_tree;
		
		f->_M_layer1 = layer;

		f->initialize(g, root);

		g->depth_first_search3(f, root);

		f->finalize(g, root);
	}

	g->dot();
	
	arrange_tree(root, root, 0, 6.28);

	layer->_M_enabled = true;

	g->dot();

	gr::repel(g);
}
void				THIS::spanning_tree(gr::VERT_S v)
{
	auto f = new gr::algo::ftor_dfs::ftor_dfs_vert2_spanning_tree;

	f->initialize(shared_from_this(), v);

	depth_first_search3(f, v);

	f->finalize(shared_from_this(), v);
}






