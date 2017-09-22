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

void		test(int n)
{
	printf("test %2i\n", n);

	auto g = gr::complete(n);	

	g->dot();

	g->simplify_self();

	g->dot();

	auto l = std::make_shared<gr::layer>();
	g->longest_cycle_1(l);

	g->dot();
}
int main(int ac, char ** av)
{
	test(atoi(av[1]));

	return 0;
}

