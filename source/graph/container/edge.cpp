#include <gr/vert.hpp>
#include <gr/edge.hpp> // gr/edge.hpp.in

#include <gr/container/edge.hpp> // gr/container/edge.hpp.in

typedef gr::container::edge THIS;

typename gr::CONT_EDGE::iterator	THIS::begin() const
{
	return _M_container.begin();
}
typename gr::CONT_EDGE::iterator	THIS::end() const
{
	return _M_container.end();
}

typename gr::CONT_EDGE::iterator	THIS::erase(gr::CONT_EDGE::iterator const & it)
{
	return _M_container.erase(it);
}

typename gr::CONT_EDGE::iterator	THIS::find(gr::VERT_S const & u) const
{
	for(auto it = begin(); it != end(); ++it) {
		gr::edge const & edge = *it;
		gr::VERT_S v = edge._M_v1.lock();
		if((*v) == (*u)) return it;
	}
	return end();
}

std::pair<typename gr::CONT_EDGE::iterator, bool>	THIS::insert(gr::edge const & e)
{
	return _M_container.insert(e);
}

typename gr::CONT_EDGE::size_type			THIS::size() const
{
	return _M_container.size();
}




