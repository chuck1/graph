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

int Factorial(int x) {
	return (x<=1 ? 1 : x * Factorial(x-1));
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
		for(int j = i+1; j < n; ++j)
		{
			g->add_edge(std::make_shared<gr::edge>(verts[i], verts[j]));
		}
	}

	// cycles
	
	// test logging

	g->dot();

	// analytical
	int c = 0;
	for(int k = 3; k < n+1; ++k)
	{
		int m = Factorial(n) / Factorial(n-k) / k;
		printf("N=%i k=%i res=%i\n",n,k,m);
		c += m;
	}

	//gr::graph::_level_static = 0;
	auto cycles = g->cycles();
	//gr::graph::_level_static = 1;

	printf("cycles %lu\n", cycles.size());
	gr::filter_cycles(cycles);
	printf("cycles %lu\n", cycles.size());

	

	assert(cycles.size() == c);
}
int main()
{
	/**
	 * the purpose of this test is to calculate the number of def 1 cycles
	 * and compare to known values
	 */

	for(int i = 3; i < 6; ++i) test(i);

	return 0;
}

