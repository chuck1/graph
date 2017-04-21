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
	virtual std::string	name()
	{
		char buffer[16];
		sprintf(buffer, "%i", _M_index);
		return buffer;
	}
	virtual bool		operator!=(gr::vert const & v)
	{
		return !operator==(v);
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
class Edge: public gr::edge
{
public:
	Edge(gr::VERT_S v0, gr::VERT_S v1, int index):
		gr::edge(v0, v1),
		_M_index(index)
	{
	}
	virtual bool		operator<(gr::edge const & e) const
	{
		//printf("Edge::operator<\n");
		Edge const & e2 = static_cast<Edge const &>(e);
		bool ret(_M_index < e2._M_index);
		return ret;
	}
	virtual std::string	name() const
	{
		char buffer[16];
		sprintf(buffer, "%i", _M_index);
		return buffer;
	}
	int			_M_index;
};

void		print_verts(gr::GRAPH_S const & g)
{
	for(auto i = g->vert_begin(); i != g->vert_end(); ++i)
	{
		gr::VERT_S const & u = *i;

		std::cout << u << " " << u->_M_edges->size() << std::endl;

		for(auto j = u->edge_begin(); j != u->edge_end(); ++j)
	       	{
			auto e = *j;
			std::cout << "  " << e->v0()->name() << " " << e->v1()->name() << std::endl;
		}
	}
}
void test(int n)
{
	printf("\nn=%i\n\n", n);

	auto g = std::make_shared<gr::graph>();
	
	std::vector<std::shared_ptr<Vert>> verts;
	
	for(int i = 0; i < n; ++i)
	{
		verts.push_back(std::make_shared<Vert>(g, i));
	}

	int c = 0;
	for(int i = 0; i < n; ++i)
	{
		if(i > 0) g->add_edge(std::make_shared<Edge>(verts[i-1], verts[i], c++));
		g->add_edge(std::make_shared<Edge>(verts[i], verts[0], c++));
	}

	print_verts(g);

	g->cycles1();

}
int main()
{
	test(1);
	test(2);
	test(3);

	return 0;
	/*
	
	auto i = g->vert_find(n0);

	assert(i != g->vert_end());

	auto bridges = g->bridges();
	std::cout << "bridges" << std::endl;
	
	g->add_edge(n5, n6);

	std::cout << "check" << std::endl;
	g->bridges();
	*/
	//g->depth_first_search(n0);
	//g->depth_first_search(n1);
}

