#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <deque>

// gr/decl.hpp.in
#include <gr/container/edge.hpp> // gr/container/edge.hpp.in
#include <gr/container/vert.hpp> // gr/container/vert.hpp.in
#include <gr/iterator/edge_graph.hpp> // gr/iterator/edge_graph.hpp_in
#include <gr/iterator/edge_vert.hpp> // gr/iterator/edge_vert.hpp_in
#include <gr/pair.hpp> // gr/pair.hpp.in
#include <gr/pair_comp.hpp> // gr/pair_comp.hpp.in
#include <gr/vert.hpp> // gr/vert.hpp_in
#include <gr/edge.hpp> // gr/edge.hpp_in
#include <gr/edge_data.hpp>

#include <gr/graph.hpp> // gr/graph.hpp_in

typedef gr::graph THIS;

void				THIS::add_edge_util(gr::VERT_S v0, gr::VERT_S v1, std::shared_ptr<gr::edge_data> const & edge_data)
{
	auto i = iter(v0);
	
	(*i)->add_edge_util(v0, v1, edge_data);
	
	/*
	gr::container::EDGE_S const & edges = (*i)->_M_edges;
	
	assert(edges);

	gr::edge edge(v0, v1, edge_data);

	edges->insert(edge);
	*/
}
void				THIS::add_edge(gr::VERT_S v0, gr::VERT_S v1)
{
	auto data = std::make_shared<gr::edge_data>();
	
	add_edge_util(v0, v1, data);
	add_edge_util(v1, v0, data);
}
gr::iterator::vert_graph	THIS::iter(gr::VERT_S v)
{
	auto it = vert_find(v);

	if(it == vert_end()) {
		
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

	assert(w.expired());

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
void				THIS::depth_first_search_util(
		gr::VERT_S const & v,
		std::deque<gr::EDGE_S> & stack)
{
	v->dfs._M_visited = true;

	for(auto it = v->edge_begin(); it != v->edge_end(); ++it)
	{
		auto e = *it;
		if(!e->dfs._M_visited)
		{
			e->dfs._M_visited = true;
			stack.push_back(e);

			auto v1 = e->other(v);
			if(v->dfs._M_visited)
			{
				// cycle
			}
			else
			{

			}
		}
	}
}
void				THIS::depth_first_search(gr::VERT_S const & v)
{
	std::vector<std::vector<gr::EDGE_S>> cycles;
	std::deque<gr::EDGE_S> stack;
	
	for(auto it = vert_begin(); it != vert_end(); ++it)
	{
		(*it)->dfs._M_visited = false;
	}
	
	for(auto it = edge_begin(); it != edge_end(); ++it)
	{
		auto e = *it;
		e->dfs._M_visited = false;
	}
	
	depth_first_search_util(v, stack);
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
void				THIS::dot(std::string filename, gr::VERT_S const & v)
{
	distance(v);
	dot(filename);
}
void				THIS::dot(std::string filename)
{
	std::ofstream of;
	of.open(filename);

	of << "graph {" << std::endl;
	of << "overlap=false" << std::endl;
	of << "splines=true" << std::endl;

	for(auto i = edge_begin(); i != edge_end(); ++i)
	{
		auto e = *i;
		of << "node" << e->_M_v0.lock().get() << " -- node" << e->_M_v1.lock().get() << std::endl;
	}
	
	for(auto i = vert_begin(); i != vert_end(); ++i) {
		of << (*i)->dot() << std::endl;
	}

	of << "}" << std::endl;
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
		auto const & data = e->_M_data;
		assert(data);
		data->_M_enabled = true;
	}
}
void				THIS::vert_enable()
{
	for(auto i = vert_begin(); i != vert_end(); ++i) {
		(*i)->_M_enabled = true;
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















