#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>

#include <gr/decl.hpp> // gr/decl.hpp_in
#include <gr/container/edge.hpp> // gr/container/edge.hpp.in
#include <gr/iterator/edge_vert.hpp> // gr/iterator/edge_vert.hpp_in
#include <gr/pair.hpp> // gr/pair.hpp.in
#include <gr/edge.hpp> // gr/edge.hpp.in
#include <gr/graph.hpp> // gr/vert.hpp.in
#include <gr/layer.hpp>

#include <gr/vert/Vert.hpp> // gr/vert/Vert.hpp_in

typedef gr::vert::Vert THIS;

THIS::Vert(gr::GRAPH_S g):
	dist{0},
	_M_graph(g),
	_M_edges(new gr::container::edge)
{
}
THIS::~Vert()
{
//	std::cout << "vert destroyed" << std::endl;
}
bool				THIS::operator==(THIS const & v)
{
	return this == &v;
}
bool				THIS::operator<(THIS const & v)
{
	return this < &v;
}
bool				THIS::operator!=(THIS const & v)
{
	return !operator==(v);
}
bool				THIS::enabled() const
{
	if(!_M_layer.enabled()) return false;

	return true;
}
gr::GRAPH_S			THIS::get_graph() const
{
	auto ret = _M_graph.lock();
	assert(ret);
	return ret;
}
gr::iterator::edge_vert		THIS::edge_begin()
{
	return gr::iterator::edge_vert(*_M_edges, _M_edges->begin());
}
gr::iterator::edge_vert		THIS::edge_end()
{
	return gr::iterator::edge_vert(*_M_edges, _M_edges->end());
}
gr::iterator::edge_vert		THIS::edge_erase(gr::iterator::edge_vert & i)
{
	auto j = _M_edges->erase(i._M_i);

	return gr::iterator::edge_vert(*_M_edges, j);
}
gr::Range<gr::iterator::edge_vert>	THIS::edge_range()
{
	return gr::Range<gr::iterator::edge_vert>(edge_begin(), edge_end());
}
void				THIS::edge_erase_disconnected()
{
	//for(auto it = edge_begin(); it != edge_end();)
	for(auto it = _M_edges->begin(); it != _M_edges->end();)
	{
		auto e = *it;
		if(e->_M_v0.expired()) throw std::exception();

		if(e->_M_v1.expired())
		{
			//it = edge_erase(it);
			it = _M_edges->erase(it);
			continue;
		}
		
		++it;
	}
}
unsigned int			THIS::edge_size()
{
	return std::distance(edge_begin(), edge_end());
}
void				THIS::add_edge(gr::EDGE_S e)
{
	assert(_M_edges);

	_M_edges->insert(e);
}
void				THIS::edge_erase_util(gr::VERT_S & v0, gr::VERT_S & v1)
{
	//gr::container::EDGE_S const & edges = (*i)->_M_edges;

	auto j = _M_edges->find(v1);
	//auto j = std::find(edges.begin(), edges.end(), v1);

	if(j == _M_edges->end()) throw std::exception();

	_M_edges->erase(j);

	//for(auto j = edges.begin(); j != edges.end(); ++j) {
	//	gr::VERT_S w = j->first.lock();
	//}
}
std::string			THIS::dot()
{
	std::string c = _M_layer.plot_color();

	std::stringstream ss;
	ss << "node" << this;
	ss << "[";
	ss << "label=\"" << name() <<"\",";
	ss << "pos=\"" << _M_dot.pos <<"\"";
	ss << "shape=\"" << _M_dot.shape <<"\"";
	if(!c.empty()) ss << "color=\"" << c <<"\"";
	ss << "]";
	return ss.str();
}
std::string			THIS::name()
{
	char buffer[64];
	sprintf(buffer, "%p", this);
	return buffer;
}
gr::VERT_S			THIS::copy(GRAPH_S g) const
{
	return std::make_shared<THIS>(g);
}
gr::VERT_S			THIS::virt()
{
	auto v = _M_virt.lock();
	if(v)
	{
		auto w = v->virt();
		if(w) return w;
	}
	return v;
}
void				THIS::set_pos()
{
	std::stringstream ss;
	ss << _M_dot.p[0] << "," << _M_dot.p[1] << "!";
	_M_dot.pos = ss.str();
}
void				THIS::shortest_path(gr::PATH & path)
{
	if(_M_shortest_path.e)
	{
		path.push_back(_M_shortest_path.e);
		_M_shortest_path.e->other(shared_from_this())->shortest_path(path);
	}
}










