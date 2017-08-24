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
	printf("test n=%i\n", n);

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
		//g->add_edge(std::make_shared<gr::edge>(verts[i], verts[0]));
	}
	g->add_edge(std::make_shared<gr::edge>(verts[0], verts[n-1]));
	
	// attachment points for second cycle
	int i0 = 0;
	int i1 = n / 2 - 1;
	
	// number of vertices common to original cycle and new cycle
	int n0 = i1 - i0 + 1;

	// number of new vertices
	int n1 = n - n0 - 1;

	for(int i = 0; i < n1; ++i)
	{
		std::stringstream ss; ss << i + n;
		verts.push_back(std::make_shared<Vert>(g, ss.str()));
		if(i > 0) g->add_edge(std::make_shared<gr::edge>(verts[n+i-1], verts[n+i]));
	}
	g->add_edge(std::make_shared<gr::edge>(verts[i0], verts[n]));
	g->add_edge(std::make_shared<gr::edge>(verts[i1], verts[n+n1-1]));


	// cycles
	
	// test logging
	//gr::graph::_level_static = 0;
	/*

	auto cycles = g->cycles1();
	printf("cycles %lu\n", cycles.size());

	gr::filter_cycles(cycles);

	printf("cycles %lu\n", cycles.size());
	*/
	//for(auto it = cycles.begin(); it != cycles.end(); ++it) print_cycle(*it);
	

	auto cycles0 = g->cycles0();
	printf("cycles0 %lu\n", cycles0.size());
	
	auto cycles1 = g->cycles1();
	printf("cycles1 %lu\n", cycles1.size());

	gr::arrange_dot(cycles0);

	// dot
	g->dot();
	
	// paths
	//auto paths = g->paths();
	
	//printf("paths  %lu\n", paths.size());
	
	//for(auto it = paths.begin(); it != paths.end(); ++it) print_cycle(*it);

}
int main()
{
	/**
	 * the purpose of this test is to calculate the number of def 1 cycles
	 * and compare to known values
	 */
	
	//for(int i = 3; i < 7; ++i) test(i);
	test(8);

	return 0;
}

