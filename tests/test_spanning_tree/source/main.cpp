#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <gr/gr.hpp> // gr/gr.hpp_in
#include <gr/plot/vert.hpp>
#include <gr/algo/less_cycle.hpp>
#include <gr/construct.hpp>

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

int		factorial(int x) {
	return (x<=1 ? 1 : x * factorial(x-1));
}
int		combinations(int n, int k)
{
	return factorial(n) / factorial(k) / factorial(n-k);
}
typedef gr::plot::vert VERT;
typedef std::shared_ptr<VERT> VERT_S;

void	test_arrange_tree(int n)
{
	//auto g = gr::complete(n);
	//auto g = gr::flower(n);
	auto g = gr::random(n, n*(n-7)/2);

	g->dot();

	g->arrange2(*g->vert_begin());

	g->dot();
}
int main()
{
	test_arrange_tree(15);

	return 0;
}

