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

int		calc_cycles1(int n)
{
	int c = 0;
	for(int k = 3; k < n+1; ++k)
	{
		int m = factorial(n) / factorial(n-k) / k;
		printf("N=%i k=%i res=%i\n",n,k,m);
		c += m;
	}
	return c;
}
int		calc_flower(int n)
{
	int c = 0;
	for(int k = 1; k <= n; ++k)
	{
		c += combinations(n, k) * (1 << k) * factorial(k - 1);
	}
	return c;
}
void		test_flower(int n)
{
	auto g = gr::flower(n);
	
	g->dot();

	unsigned int c = calc_flower(n);

	auto cycles0 = g->cycles0();
	auto cycles1 = g->cycles1();

	printf("test flower n=%i\n", n);
	printf("c = %i\n", c);
	printf("cycles0 %lu\n", cycles0.size());
	printf("cycles1 %lu\n", cycles1.size());
}
void		test(int n)
{
	auto g = gr::complete(n);	

	g->dot();

	auto cycles0 = g->cycles0();
	auto cycles1 = g->cycles1();

	unsigned int c = calc_cycles1(n);

	printf("test n=%i\n", n);
	printf("c = %i\n", c);
	printf("cycles0 %lu\n", cycles0.size());
	printf("cycles1 %lu\n", cycles1.size());

	//assert(cycles1.size() == c);
}
void		test1(int n)
{
	printf("test n=%i\n", n);

	unsigned int c = calc_cycles1(n);

	printf("c = %i\n", c);

	auto g = gr::complete(n);	

	g->dot();

	auto cycles1 = g->cycles1();


	printf("cycles1 %lu\n", cycles1.size());

	//assert(cycles1.size() == c);
}
void test2(int n)
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
void	test_arrange_tree(int n)
{
	//auto g = complete(n);
	auto g = gr::flower(n);

	g->dot();

	g->arrange2(*g->vert_begin());

	g->dot();
}
int main()
{
	/**
	 * the purpose of this test is to calculate the number of def 1 cycles
	 * and compare to known values
	 */
	
	//for(int i = 2; i < 6; ++i) test1(i);
	
	//return 0;

	//for(int i = 3; i < 6; ++i) test(i);
	//for(int i = 3; i < 8; ++i) test1(i);
	//for(int i = 2; i < 6; ++i) test_flower(i);
	
	test_arrange_tree(6);

	return 0;
}

