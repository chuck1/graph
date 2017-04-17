#include <sstream>
#include <iostream>
#include <algorithm>

#include <gr/algo/less_cycle.hpp>
#include <gr/edge.hpp>
#include <gr/vert.hpp>

#include <gr/util.hpp> // gr/util.hpp_in

bool test_cycle(gr::algo::cycle const & c)
{
	for(auto it = c.begin(); it != c.end(); ++it)
	{
		auto e = *it;
		e->v0()->algo.counter = 0;
		e->v1()->algo.counter = 0;
	}
	for(auto it = c.begin(); it != c.end(); ++it)
	{
		auto e = *it;
		++e->v0()->algo.counter;
		++e->v1()->algo.counter;
		if(e->v0()->algo.counter > 2) return false;
		if(e->v1()->algo.counter > 2) return false;
	}
	return true;
}
void		gr::filter_cycles(gr::algo::SET_CYCLE & cycles)
{
	for(auto it = cycles.begin(); it != cycles.end();)
	{
		if(test_cycle(*it))
		{
			++it;
		}
		else
		{
			it = cycles.erase(it);
		}
	}
}
void		gr::arrange_dot(gr::algo::SET_CYCLE & cycles)
{
	filter_cycles(cycles);

	// get long cycle
	auto c = *(--cycles.end());

	std::for_each(c.begin(), c.end(), [](gr::EDGE_S const & e){  });
	
	unsigned int s = c.size();
	unsigned int i = 0;

	float r = s * 2.0 / 2.0 / M_PI;

	auto v0 = c._M_v;
	
	for(auto it = c.begin(); it != c.end(); ++it)
	{
		auto e = *it;

		e->_M_dot.color="red";
		
		float a = (float)i / (float)s * 2.0 * M_PI;
		float x = r * cos(a);
		float y = r * sin(a);
		std::cout << a << std::endl;
		
		std::stringstream ss; ss << x << "," << y << "!";
		v0->_M_dot.pos = ss.str();

		v0 = e->other(v0);

		++i;
	}
}

