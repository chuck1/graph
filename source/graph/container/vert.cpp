#include <cassert>
#include <iostream>

// gr/decl.hpp.in
#include <gr/iterator/vert_graph.hpp>
#include <gr/vert.hpp>


#include <gr/container/vert.hpp> // gr/container/vert.hpp_in

typedef gr::container::vert THIS;

THIS::iterator		THIS::begin()
{
	return _M_container.begin();
}
THIS::iterator		THIS::end()
{
	return _M_container.end();
}
THIS::iterator		THIS::find(gr::VERT_S const & v)
{
	return _M_container.find(v);
}
THIS::iterator		THIS::erase(THIS::iterator & i)
{
	gr::VERT_W w = *i;

	assert(!w.expired());
	
	auto ret = _M_container.erase(i);
	
	assert(w.expired());
	
	return ret;
}
unsigned int			THIS::size() const
{
	//auto s1 = _M_container.size();
	//auto s2 = std::distance(begin(), end());
	return _M_container.size();
}
gr::CONT_VERT::iterator		THIS::insert(
	CONT_VERT::iterator const & i, CONT_VERT::value_type & v)
{
	return _M_container.insert(i, v);
}


