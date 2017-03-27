#include <iostream>

#include <gr/pair.hpp> // gr/pair.hpp.in
#include <gr/vert.hpp> // gr/vert.hpp.in

#include <gr/pair_comp.hpp> // gr/pair_comp.hpp.in

#if 0
typedef gr::pair_comp THIS;

bool		THIS::operator()(gr::pair const & p0, gr::pair const & p1)
{
	gr::VERT_S const & v0 = p0._M_p.first;
	gr::VERT_S const & v1 = p1._M_p.first;
	bool ret((*v0) < (*v1));
	//std::cout << "pair_comp " << v0 << " < " << v1 << " = " << ret << std::endl;
	return ret;
}
#endif


