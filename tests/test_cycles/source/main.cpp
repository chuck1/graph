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
void construct(gr::GRAPH_S g, int n)
{
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
}
int calc_cycles1(int n)
{
	int c = 0;
	for(int k = 3; k < n+1; ++k)
	{
		int m = Factorial(n) / Factorial(n-k) / k;
		printf("N=%i k=%i res=%i\n",n,k,m);
		c += m;
	}
	return c;
}
void test(int n)
{
	printf("test n=%i\n", n);

	auto g = std::make_shared<gr::graph>();
	
	construct(g, n);	

	g->dot();

	// cycles0

	auto cycles0 = g->cycles0();

	printf("cycles0 %lu\n", cycles0.size());

	// cycles1

	// analytical solution
	unsigned int c = calc_cycles1(n);

	printf("c = %i\n", c);

	auto cycles1 = g->cycles1();

	printf("cycles1 %lu\n", cycles1.size());

	assert(cycles1.size() == c);
}
void test1(int n)
{
	auto g = std::make_shared<gr::graph>();

	int i = 0;

	auto v0 = std::make_shared<Vert>(g, std::to_string(i));
	++i;

	for(int j = 0; j < n; ++j) {
		auto v1 = std::make_shared<Vert>(g, std::to_string(i));
		++i;
		auto v2 = std::make_shared<Vert>(g, std::to_string(i));
		++i;
		
		g->add_edge(v0, v1);
		g->add_edge(v1, v2);
		g->add_edge(v2, v0);
	}

	g->dot();

	auto cycles0 = g->cycles0();

	printf("cycles0 %lu\n", cycles0.size());

}
int main()
{
	/**
	 * the purpose of this test is to calculate the number of def 1 cycles
	 * and compare to known values
	 */
	
	//for(int i = 2; i < 6; ++i) test1(i);
	
	//return 0;

	for(int i = 3; i < 6; ++i) test(i);

	return 0;
}

