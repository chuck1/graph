#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <gr/algo/less_cycle.hpp>
#include <gr/edge.hpp> // gr/edge.hpp_in
#include <gr/graph.hpp>
#include <gr/io.hpp> // gr/io.hpp_in
#include <gr/vert.hpp> // gr/vert.hpp_in
#include <gr/iterator/edge_graph.hpp>

#include <gr/util.hpp> // gr/util.hpp_in

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
void		gr::filter_cycles(gr::algo::SET_CYCLE & cycles)
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
void		gr::arrange_dot(gr::algo::SET_CYCLE & cycles)
{
	if(cycles.empty()) return;

	auto g = (*(*cycles.begin()).begin())->v0()->get_graph();

	g->log<0>() << "cycles " << cycles.size() << std::endl;
	
	filter_cycles(cycles);

	g->log<0>() << "cycles " << cycles.size() << std::endl;

	if(cycles.empty()) return;

	// get long cycle
	auto c = *(--cycles.end());

	std::for_each(c.begin(), c.end(), [](gr::EDGE_S const & e){  });
	
	unsigned int s = c.size();
	unsigned int i = 0;

	float r = s * 2.0 / 2.0 / M_PI;

	auto v0 = c._M_v;
	
	g->log<0>() << "cycle = " << c.container() << std::endl;

	for(auto it = c.begin(); it != c.end(); ++it)
	{
		g->log<0>() << "v0 = " << v0->name() << std::endl;

		auto e = *it;

		e->_M_dot.color="red";
		
		float a = (float)i / (float)s * 2.0 * M_PI;
		float x = r * cos(a);
		float y = r * sin(a);
	
		v0->_M_dot.x = x;
		v0->_M_dot.y = y;

		std::stringstream ss; ss << x << "," << y << "!";
		v0->_M_dot.pos = ss.str();

		v0 = e->other(v0);

		++i;
	}

	// repel
	gr::repel(g);
}
void		gr::zero_force(gr::GRAPH_S & g)
{
	for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
	{
		auto v1 = *it;
		v1->_M_dot.f_x = 0;
		v1->_M_dot.f_y = 0;
	}
}
void		apply_force(gr::VERT_S & v0, gr::VERT_S & v1, float d0, float k)
{
	float d_x = v1->_M_dot.x - v0->_M_dot.x;
	float d_y = v1->_M_dot.y - v0->_M_dot.y;

	float d = sqrt(d_x*d_x + d_y*d_y);
	
	if(d < 0.0001) return;
	
	float f_x = d_x / d * (d - d0) * k;
	float f_y = d_y / d * (d - d0) * k;

	printf("d  =%f\n", d);
	printf("d_x=%f\n", d_x);
	printf("d_y=%f\n", d_y);
	printf("f_x=%f\n", f_x);
	printf("f_y=%f\n", f_y);

	v0->_M_dot.f_x += f_x;
	v0->_M_dot.f_y += f_y;

	v1->_M_dot.f_x -= f_x;
	v1->_M_dot.f_y -= f_y;
}
void		gr::repel(gr::GRAPH_S & g)
{
	auto v = g->vert_size();
	
	float d0 = 2;

	for(int i = 0; i < 10; ++i)
	{
		gr::zero_force(g);

		unsigned int i1 = 0;
		for(auto it1 = g->vert_begin(); it1 != g->vert_end(); ++it1, ++i1)
		{
			unsigned int i2 = 0;
			for(auto it2 = g->vert_begin(); it2 != g->vert_end(); ++it2, ++i2)
			{
				if(i1 == i2) break;

				auto v0 = *it1;
				auto v1 = *it2;

				apply_force(v0, v1, d0, 1);
			}	
		}

		for(auto it = g->edge_begin(); it != g->edge_end(); ++it)
		{
			auto e = *it;
			auto v0 = e->v0();
			auto v1 = e->v1();
			apply_force(v0, v1, d0, 2);
		}

		// move
		for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
		{
			auto v = *it;
			v->_M_dot.x += v->_M_dot.f_x * 0.5;
			v->_M_dot.y += v->_M_dot.f_y * 0.5;
		}
	}

	// record
	for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
	{
		auto v = *it;
		std::stringstream ss;
		ss << v->_M_dot.x << "," << v->_M_dot.y << "!";
		v->_M_dot.pos = ss.str();
	}
}





