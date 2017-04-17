#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <gr/gr.hpp> // gr/gr.hpp_in
#include <gr/plot/vert.hpp>

#include <test.hpp>

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
	
	// test logging
	gr::graph::_level_static = 0;

	auto cycles = g->cycles();

	printf("cycles %lu\n", cycles.size());

	gr::filter_cycles(cycles);

	printf("cycles %lu\n", cycles.size());
	
	for(auto it = cycles.begin(); it != cycles.end(); ++it) print_cycle(*it);
	
	gr::arrange_dot(cycles);

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

