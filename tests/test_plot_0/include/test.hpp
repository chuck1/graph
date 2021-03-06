#include <cassert>
#include <iostream>

#include <gr/gr.hpp> // gr/gr.hpp.in
#include <gr/plot/vert.hpp> // gr/plot/vert.hpp.in

class Vert: public gr::plot::vert
{
public:
	Vert(gr::GRAPH_S g, std::string nid): gr::plot::vert(g, nid)
	{
	}
	virtual std::string	name()
	{
		return _M_name;
	}
	/*
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
	*/
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



