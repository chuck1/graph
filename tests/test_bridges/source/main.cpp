#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <gr/gr.hpp> // gr/gr.hpp_in
#include <gr/plot/vert.hpp>
#include <gr/algo/less_cycle.hpp>
#include <gr/construct.hpp>

void			btree(
		gr::graph::S_Graph const & g,
		gr::S_Vert const & v0,
		int n,
		int & i)
{
	if(n == 0) return;
	
	for(int j = 0; j < 2; ++j)
	{
		auto v1 = std::make_shared<gr::plot::vert>(g, std::to_string(i++));

		g->add_edge(v0, v1);

		btree(g, v1, n-1, i);
	}
}
gr::graph::S_Graph		btree(int n)
{
	auto g = std::make_shared<gr::graph::Graph>();
	
	int i = 0;

        auto v = std::make_shared<gr::plot::vert>(g, std::to_string(i++));

	btree(g, v, n, i);
	
	return g;
}
void		test(int n)
{
	printf("test %2i\n", n);

	auto g = btree(n);	

	g->dot();

	auto l = std::make_shared<gr::layer>();
	
	g->bridges();

	std::cout << (pow(2, n+1) - 2) << std::endl;
	
	gr::algo::dfs::Bridges a(g);
	a.run();
	std::cout << "algo " << a._M_edges.size() << std::endl;

	g->dot();
}
int main()
{
	for(int i = 3; i < 10; ++i) test(i);

	return 0;
}

