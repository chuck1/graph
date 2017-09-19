#include <iostream>
#include <algorithm>
#include <cassert>

#include <gr/vert/Vert.hpp> // gr/vert.hpp.in

#include <gr/vert_comp.hpp> // gr/vert_comp.hpp.in

bool			gr::vert_comp::operator()(VERT_S const & np0, VERT_S const & np1)
{
	return (*np0) < (*np1);
}

