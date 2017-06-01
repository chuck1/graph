#include <gr/container/edge.hpp>
#include <gr/decl.hpp> // gr/decl.hpp.in
#include <gr/vert.hpp> // gr/vert.hpp.in

#include <gr/pair.hpp> // gr/pair.hpp.in

#if 0
typedef gr::pair THIS;

THIS::pair()
{
}
THIS::pair(gr::VERT_S const & v):
	_M_p(v, std::make_shared<gr::container::edge>())
{
}

bool		THIS::operator==(gr::VERT_S const & v) const
{
	return (*_M_p.first) == (*v);
}
bool		THIS::operator<(gr::VERT_S const & v)
{
	return (*_M_p.first) < (*v);
}

bool		THIS::operator==(gr::pair const & p) const
{
	gr::VERT_S const & v = p._M_p.first;
	return operator==(v);
}
bool		THIS::operator<(gr::pair const & p)
{
	return operator<(p._M_p.first);
}
#endif


