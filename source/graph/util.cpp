#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <gr/algo/less_cycle.hpp>
#include <gr/edge.hpp> // gr/edge.hpp_in
#include <gr/graph.hpp> // gr/graph.hpp_in
#include <gr/io.hpp> // gr/io.hpp_in
#include <gr/vert/Vert.hpp> // gr/vert.hpp_in
#include <gr/iterator/edge/EdgeGraph.hpp>

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

	if(!cycles.empty()) {

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
			Eigen::Vector2f p(r * cos(a), r * sin(a));

			v0->_M_dot.p = p;

			std::stringstream ss; ss << p[0] << "," << p[1] << "!";
			v0->_M_dot.pos = ss.str();

			v0 = e->other(v0);

			++i;
		}
	}
	// repel
	gr::repel(g);
}
void		gr::zero_force(gr::GRAPH_S & g)
{
	for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
	{
		auto v1 = *it;
		v1->_M_dot.f = Eigen::Vector2f(0,0);
	}
}
float		force_repel(float d, float d0, float k)
{
	return k / d / d;
}
float		force_spring(float d, float d0, float k)
{
	return (d0 - d) * k;
}
void		apply_force(gr::VERT_S & v0, gr::VERT_S & v1, float d0, float k, float(*force)(float,float,float))
{
	Eigen::Vector2f D = v1->_M_dot.p - v0->_M_dot.p;

	float d = D.norm();

	if(d < 0.0001) return;
	if(d > 10) return;

	float f = (*force)(d, d0, k);

	Eigen::Vector2f F = D / d * f;

	v0->_M_dot.f -= F;
	v1->_M_dot.f += F;
}
void		record_pos(gr::GRAPH_S & g)
{
	for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
		(*it)->set_pos();
}
void		do_repel(gr::GRAPH_S & g)
{
	unsigned int i1 = 0;
	for(auto it1 = g->vert_begin(); it1 != g->vert_end(); ++it1, ++i1)
	{
		unsigned int i2 = 0;
		for(auto it2 = g->vert_begin(); it2 != g->vert_end(); ++it2, ++i2)
		{
			if(i1 == i2) break;

			auto v0 = *it1;
			auto v1 = *it2;

			apply_force(v0, v1, 0, 1, force_repel);
		}	
	}
}
void			do_spring(
		gr::GRAPH_S & g,
		float d0)
{
		for(auto it = g->edge_begin(); it != g->edge_end(); ++it)
		{
			auto e = *it;
			auto v0 = e->v0();
			auto v1 = e->v1();
			apply_force(v0, v1, d0, 1, force_spring);
		}
}
void			do_move(
		gr::GRAPH_S & g,
		float alpha,
		float & m,
		float & m_max)
{
	for(auto it = g->vert_begin(); it != g->vert_end(); ++it)
	{
		auto v = *it;
		Eigen::Vector2f a = v->_M_dot.f * alpha;

		float d = a.norm();

		if(d > 1) {
			a = a / d;
			d = 1;
		}

		v->_M_dot.p += a;

		m += d;
		m_max = fmax(m_max, d);
	}
}
void		gr::repel(gr::GRAPH_S & g)
{
	//auto v = g->vert_size();

	float d0 = 2;

	float m_last = 0;
	
	float alpha = 0.1;
	
	for(int i = 0; i < 1000; ++i)
	{
		gr::zero_force(g);

		do_repel(g);
		do_spring(g, d0);
		
		float m = 0;
		float m_max = 0;
		
		do_move(g, alpha, m, m_max);
		
		float dm = m - m_last;
		m_last = m;

		printf("i = %4i m = %8.3e m_max = %8.3e dm = %+8.3e alpha = %8.3e\n", i, m, m_max, dm, alpha);

		//record_pos(g);
		//g->dot();

		if(m < 1e-2) break;
	}

	record_pos(g);
}





