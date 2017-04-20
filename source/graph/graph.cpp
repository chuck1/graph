#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <deque>
#include <set>
#include <map>

#include <gr/algo/stack.hpp> // gr/algo/stack.hpp_in
#include <gr/algo/cycle.hpp> // gr/algo/cycle.hpp_in
#include <gr/algo/ftor_dfs.hpp> // gr/algo/ftor_dfs.hpp_in
#include <gr/container/edge.hpp> // gr/container/edge.hpp.in
#include <gr/container/vert.hpp> // gr/container/vert.hpp.in
#include <gr/iterator/edge_graph.hpp> // gr/iterator/edge_graph.hpp_in
#include <gr/iterator/edge_vert.hpp> // gr/iterator/edge_vert.hpp_in
#include <gr/io.hpp> // gr/vert.hpp_in
#include <gr/pair.hpp> // gr/pair.hpp.in
#include <gr/pair_comp.hpp> // gr/pair_comp.hpp.in
#include <gr/vert.hpp> // gr/vert.hpp_in
#include <gr/edge.hpp> // gr/edge.hpp_in
#include <gr/layer.hpp>
#include <gr/util.hpp>

#include <gr/graph.hpp> // gr/graph.hpp_in

typedef gr::graph THIS;

THIS::graph()
{
}
gr::EDGE_S			THIS::add_edge(gr::VERT_S v0, gr::VERT_S v1)
{
	auto e = std::make_shared<gr::edge>(v0, v1);
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
gr::iterator::edge_graph	THIS::edge_end()
{
	return gr::iterator::edge_graph(_M_verts, _M_verts.end());
}






gr::iterator::vert_comp		THIS::comp_vert_begin(int c)
{
	return gr::iterator::vert_comp(_M_verts, _M_verts.begin(), c);
}
gr::iterator::vert_comp		THIS::comp_vert_end(int c)
{
	return gr::iterator::vert_comp(_M_verts, _M_verts.end(), c);
}






void				THIS::edge_erase_util(gr::VERT_S & v0, gr::VERT_S & v1)
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


bool		gr::algo::less_queue_edge::operator()(QUEUE_EDGE const & c0, QUEUE_EDGE const & c1)
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

	int d = std::distance(it0, c.end());

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
void				THIS::depth_first_search_util(
		gr::VERT_S const & v,
		algo::stack & stack,
		algo::ftor_dfs * ftor)
{
	/**
	 * for this algorithm, prove that when we find an edge that
	 * connects to a visited vertex, the associated cycle is a subset
	 * of the edges in the stack.
	 */
	
	log<0>() << "depth_first_search_util " << v->name() << " stack size=" << stack.size() << std::endl;
	
	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it;
		if(!contains(stack, e))
		{
			// orient
			if(*e->v0() != *v)
			{
				assert(*e->v1() == *v);
				e->swap();
			}
			assert(*e->v0() == *v);

			auto v1 = e->other(v);

			assert(e);
			stack.push_back(e);

			// debug graph
			auto algo_v = v1->copy(_M_algo.graph);
			_M_algo.graph_stack.push_back(_M_algo.graph->add_edge(_M_algo.graph_head, algo_v));
			_M_algo.graph_head = algo_v;
			
			//std::cout << "algo graph stack " << _M_algo.graph_stack << std::endl;

			//log<0>() << "stack = " << print_cycle(stack);
			//log<0>() << "stack = " << stack << std::endl;

			ftor->operator()(v1, stack);

			depth_first_search_util(v1, stack, ftor);

			stack.pop_back();

			_M_algo.graph_head = _M_algo.graph_stack.back()->other(_M_algo.graph_head);
			_M_algo.graph_stack.pop_back();
		}
	}
}
void				THIS::depth_first_search(gr::VERT_S const & v, algo::ftor_dfs * ftor)
{
	gr::algo::stack stack;
	
	// debugging graph
	_M_algo.graph.reset(new gr::digraph());
	_M_algo.graph_stack.clear();
	_M_algo.graph_head = *_M_algo.graph->iter(v->copy(_M_algo.graph));

	depth_first_search_util(v, stack, ftor);

	_M_algo.graph->dot();
}
gr::algo::SET_CYCLE		THIS::cycles()
{
	auto v = *_M_verts.begin();

	return cycles(v);
}
gr::algo::SET_CYCLE		THIS::cycles2()
{
	gr::algo::ftor_dfs_cycle2 ftor;
	
	for(auto it = vert_begin(); it != vert_end(); ++it)
	{	
		depth_first_search(*it, &ftor);
	}

	printf("fail inserts = %i\n", ftor._M_count_insert_fail);

	return ftor._M_cycles;

}
gr::algo::SET_CYCLE		THIS::cycles(gr::VERT_S const & v)
{
	gr::algo::ftor_dfs_cycle ftor;

	depth_first_search(v, &ftor);

	printf("fail inserts = %i\n", ftor._M_count_insert_fail);

	return ftor._M_cycles;
}
gr::algo::SET_QUEUE_EDGE	THIS::paths()
{
	gr::algo::ftor_dfs_path ftor;
	
	auto v = *_M_verts.begin();

	depth_first_search(v, &ftor);

	return ftor._M_paths;
}
void				THIS::vert_erase_layer(unsigned int l)
{
	if(l > _M_layers.size()) throw std::exception();

	auto const & layer = _M_layers[l];

	for(auto i = vert_begin(); i != vert_end();) {

		if(!(*i)->_M_layer.expired()) {
			if((*i)->_M_layer.lock() == layer) {
				i = vert_erase(i);
				continue;
			}
		}

		++i;
	}
}
void				THIS::bridges_sub(gr::VERT_S const & n, int & t, std::vector<gr::edge> & ret)
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
				ret.push_back(*e);
			}
		}
		else if(v != n->bridge._M_parent.lock())
		{
			n->bridge._M_low = std::min(n->bridge._M_low, v->bridge._M_disc);
		}
	}
}
std::vector<gr::edge>		THIS::bridges()
{
	std::vector<gr::edge> ret;

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
void				THIS::dot(std::string filename, gr::VERT_S const & v)
{
	distance(v);
	
	//auto c = cycles(v);
	//gr::arrange_dot(c);

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
	of << "overlap=false" << std::endl;
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
		unsigned int d = std::distance(i, u->edge_end());
		assert(d!=0);

		gr::VERT_S const & v = e->other(u);

		//assert(u == i->_M_v0.lock());
		assert(v != u);

		if(!v) throw std::exception();

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
/*
void				THIS::vert_enable()
{
	for(auto i = vert_begin(); i != vert_end(); ++i) {
		(*i)->_M_enabled = true;
	}
}
*/
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
	//auto s1 = _M_verts.size();
	auto s2 = std::distance(vert_begin(), vert_end());
	//assert(s1 == s2);
	return s2;
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

gr::algo::ftor_dfs_cycle2::ftor_dfs_cycle2():
	_M_count_insert_fail(0)
{
}
void	gr::algo::ftor_dfs_cycle2::operator()(
		gr::VERT_S const & v1,
		algo::stack & stack)
{
	auto g = v1->get_graph();
	auto algo_g = v1->get_graph()->_M_algo.graph;

	assert(stack._M_counter[v1] > 0);

	auto e = stack.front();

	if(*v1 == *e->v0())
	{
		// if we are looking for def1 cycles, no repeated vertices
		if(stack._M_count_gt_2 == 0)
		{
			gr::algo::cycle c(stack.begin(), stack.end(), v1);

			c.shift();

			auto ret = _M_cycles.insert(c);

			// mark on algo graph
			auto algo_e = algo_g->add_edge(g->_M_algo.graph_stack.front()->v0(), g->_M_algo.graph_stack.back()->v1());
			if(ret.second) {
				algo_e->_M_dot.color = "blue";
			} else {
				algo_e->_M_dot.color = "red";

				++_M_count_insert_fail;
			}
		}
	}
}
gr::algo::ftor_dfs_cycle::ftor_dfs_cycle():
	_M_count_insert_fail(0)
{
}
void	gr::algo::ftor_dfs_cycle::operator()(
		gr::VERT_S const & v1,
		algo::stack & stack)
{
	auto g = v1->get_graph();
	auto algo_g = v1->get_graph()->_M_algo.graph;

	// copy the stack
	algo::stack stack_copy(stack);

	// copy the debug stack
	std::deque<gr::EDGE_S> algo_stack_copy(g->_M_algo.graph_stack);

	assert(stack._M_counter[v1] > 0);

	// pop front until we reach v1
	while((!stack_copy.empty()) && (stack_copy._M_counter[v1] > 1))
	{
		auto e = stack_copy.front();

		if(*v1 == *e->v0())
		{
			// if we are looking for def1 cycles
			if(stack_copy._M_count_gt_2 == 0)
			{
				gr::algo::cycle c(stack_copy.begin(), stack_copy.end(), v1);

				c.shift();

				auto ret = _M_cycles.insert(c);

				// mark on algo graph
				auto algo_e = algo_g->add_edge(algo_stack_copy.front()->v0(), algo_stack_copy.back()->v1());
				if(ret.second) {
					algo_e->_M_dot.color = "blue";
				} else {
					algo_e->_M_dot.color = "red";

					++_M_count_insert_fail;
				}
			}
		}

		stack_copy.pop_front();
		algo_stack_copy.pop_front();
	}
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

void	gr::algo::ftor_dfs_path::operator()(
		gr::VERT_S const & v1,
		algo::stack & stack)
{
	// copy the stack
	algo::stack stack_copy(stack);

	// pop front until we reach v1
	while(!stack_copy.empty())
	{
		auto e = stack_copy.front();

		gr::QUEUE_EDGE c(stack_copy.begin(), stack_copy.end());
		//print_cycle(c);
		if(check_path(c)) _M_paths.insert(c);

		stack_copy.pop_front();
	}
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
void		THIS::simplify()
{
	std::cout << "graph::simplify" << std::endl;

	unsigned int s = vert_size();
	while(true)
	{
		for(auto it = vert_begin(); it != vert_end();)
		{
			auto v = *it;
			if(v->edge_size() == 1)
			{
				it = vert_erase(it);
				continue;
			}

			++it;
		}
		unsigned int s1 = vert_size();
		if(s==s1) break;
		s=s1;
	}

	// step 2

	for(auto it = vert_begin(); it != vert_end();)
	{
		auto v = *it;
		if(v->edge_size() == 2)
		{
			std::cout << "eliminate vert with two edges" << std::endl;

			auto it1 = v->edge_begin();
			auto e0 = *it1;
			++it1;
			auto e1 = *it1;

			auto v0 = e0->other(v);
			auto v1 = e1->other(v);

			/*
			   if((*v0)==(*v1))
			   {
			   ++it;
			   continue;
			   }
			   */

			add_edge(v0, v1);

			it = vert_erase(it);
			continue;
		}

		++it;
	}

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







