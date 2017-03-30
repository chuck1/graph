#include <cassert>
#include <iostream>

#include <gr/gr.hpp> // gr/gr.hpp.in
#include <gr/vert.hpp> // gr/vert.hpp.in

class Vert: public gr::vert
{
public:
	Vert(gr::GRAPH_S g, int i): gr::vert(g), _M_index(i)
	{
	}
	virtual bool		operator==(gr::vert const & v)
	{
		Vert const & v2 = static_cast<Vert const &>(v);
		bool ret(_M_index == v2._M_index);
		//std::cout << _M_index << "==" << v2._M_index << " " << ret << std::endl;
		return ret;
	}
	virtual bool		operator<(gr::vert const & v)
	{
		Vert const & v2 = static_cast<Vert const &>(v);
		bool ret(_M_index < v2._M_index);
		//std::cout << _M_index << "<" << v2._M_index << " " << ret << std::endl;
		return ret;
	}
	
	int			_M_index;
};

void		verts(gr::GRAPH_S const & g)
{
	for(auto i = g->vert_begin(); i != g->vert_end(); ++i) {
		gr::VERT_S const & u = *i;

		std::cout << u << " " << u->_M_edges->size() << std::endl;

		for(auto j = u->edge_begin(); j != u->edge_end(); ++j) {
			std::cout << "  " << j->_M_v0.lock() << " " << j->_M_v1.lock() << std::endl;
		}
	}
}
int main()
{

	auto g = std::make_shared<gr::graph>();
	
	auto n0 = std::make_shared<Vert>(g, 0);
	auto n1 = std::make_shared<Vert>(g, 1);
	auto n2 = std::make_shared<Vert>(g, 2);
	auto n3 = std::make_shared<Vert>(g, 3);
	auto n4 = std::make_shared<Vert>(g, 4);
	auto n5 = std::make_shared<Vert>(g, 5);
	auto n6 = std::make_shared<Vert>(g, 6);
	
	g->add_edge(n0, n1);
	g->add_edge(n1, n2);
	g->add_edge(n2, n0);
	g->add_edge(n3, n4);
	g->add_edge(n4, n5);
	g->add_edge(n5, n3);
	g->add_edge(n0, n3);
	g->add_edge(n1, n6);

	verts(g);
	
	auto i = g->vert_find(n0);

	assert(i != g->vert_end());

	auto bridges = g->bridges();
	std::cout << "bridges" << std::endl;
	

	g->add_edge(n5, n6);

	std::cout << "check" << std::endl;
	g->bridges();
}

