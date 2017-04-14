#include <cassert>
#include <iostream>
#include <sstream>

#include <gr/gr.hpp> // gr/gr.hpp_in
#include <gr/plot/vert.hpp>

bool test_cycle(gr::CYCLE const & c)
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
void filter_cycles(gr::CYCLES & cycles)
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

void test(int n)
{
	printf("\nn=%i\n\n", n);

	auto g = std::make_shared<gr::graph>();
	
	std::vector<std::shared_ptr<gr::plot::vert>> verts;
	
	for(int i = 0; i < n; ++i)
	{
		std::stringstream ss; ss << i;
		verts.push_back(std::make_shared<gr::plot::vert>(g, ss.str()));
	}

	int c = 0;
	for(int i = 0; i < n; ++i)
	{
		if(i > 0) g->add_edge(std::make_shared<gr::edge>(verts[i-1], verts[i]));
		g->add_edge(std::make_shared<gr::edge>(verts[i], verts[0]));
	}

	gr::CYCLES cycles = g->depth_first_search(verts[0]);

	printf("cycles %lu\n", cycles.size());

	filter_cycles(cycles);

	printf("cycles %lu\n", cycles.size());
}
int main()
{
	test(4);

	return 0;
}

