
#include <gr/edge.hpp>
#include <gr/vert.hpp>

#include <gr/io.hpp> // gr/io.hpp_in

std::ostream & operator<<(std::ostream & os, std::deque<gr::EDGE_S> const & c)
{
	for(auto it = c.begin(); it != c.end(); ++it)
	{
		char buffer[128];
		auto e = (*it);
		sprintf(buffer, "(%s)%s(%s) - ", (*it)->v0()->name().c_str(), e->name().c_str(), (*it)->v1()->name().c_str());
		os << buffer;
	}
	return os;
}


