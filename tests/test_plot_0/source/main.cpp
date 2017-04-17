#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <gr/gr.hpp> // gr/gr.hpp_in
#include <gr/plot/vert.hpp>

#include <test.hpp>

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
void filter_cycles(gr::algo::SET_CYCLE & cycles)
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
template<typename T>
void print_cycle(T cycle)
{
	//std::cout << cycle.front()->v0()->name();
	for(auto it = cycle.begin(); it != cycle.end(); ++it)
	{
		char buffer[128];
		auto e = (*it);
		sprintf(buffer, "(%s)%s(%s) - ", (*it)->v0()->name().c_str(), e->name().c_str(), (*it)->v1()->name().c_str());
		std::cout << buffer;
	}
	std::cout << std::endl;
}

void test(int n)
{
	printf("\nn=%i\n\n", n);

	auto g = std::make_shared<gr::graph>();
	
	// construct
	std::vector<std::shared_ptr<gr::plot::vert>> verts;
	
	for(int i = 0; i < n; ++i)
	{
		std::stringstream ss; ss << i;
		verts.push_back(std::make_shared<Vert>(g, ss.str()));
	}

	for(int i = 0; i < n; ++i)
	{
		if(i > 0) g->add_edge(std::make_shared<gr::edge>(verts[i-1], verts[i]));
		g->add_edge(std::make_shared<gr::edge>(verts[i], verts[0]));
	}

	// cycles
	auto cycles = g->cycles();

	printf("cycles %lu\n", cycles.size());

	filter_cycles(cycles);

	printf("cycles %lu\n", cycles.size());
	
	for(auto it = cycles.begin(); it != cycles.end(); ++it) print_cycle(*it);
	
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

	// dot
	g->dot();
	
	// paths
	auto paths = g->paths();
	
	printf("paths  %lu\n", paths.size());
	
	for(auto it = paths.begin(); it != paths.end(); ++it) print_cycle(*it);

}
int main()
{
	test(6);

	return 0;
}

