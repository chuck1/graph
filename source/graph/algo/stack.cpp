#include <gr/edge.hpp>
#include <gr/vert.hpp>

#include <gr/algo/stack.hpp> // gr/algo/stack.hpp_in

typedef gr::algo::stack THIS;

THIS::stack(): _M_count_gt_2(0)
{}
unsigned int		THIS::size() const
{
	return _M_edges.size();
}
void			THIS::push_back(gr::EDGE_S const & e)
{
	_M_edges.push_back(e);

	//++e->v0()->algo.counter;
	//++e->v1()->algo.counter;
	
	{
		auto it = _M_counter.find(e->v0());
		if(it == _M_counter.end()) _M_counter[e->v0()] = 0;
	}
	{
		auto it = _M_counter.find(e->v1());
		if(it == _M_counter.end()) _M_counter[e->v1()] = 0;
	}
	auto & c0 = _M_counter[e->v0()];
	auto & c1 = _M_counter[e->v1()];
	if(c0==2) ++_M_count_gt_2;
	if(c1==2) ++_M_count_gt_2;
	++c0;
	++c1;
}
void			THIS::pop_back()
{
	auto e = _M_edges.back();
	//--e->v0()->algo.counter;
	//--e->v1()->algo.counter;
	auto & c0 = _M_counter[e->v0()];
	auto & c1 = _M_counter[e->v1()];
	if(c0==3) --_M_count_gt_2;
	if(c1==3) --_M_count_gt_2;
	--c0;
	--c1;

	_M_edges.pop_back();
}
void			THIS::pop_front()
{
	auto e = _M_edges.front();
	//--e->v0()->algo.counter;
	//--e->v1()->algo.counter;
	auto & c0 = _M_counter[e->v0()];
	auto & c1 = _M_counter[e->v1()];
	if(c0==3) --_M_count_gt_2;
	if(c1==3) --_M_count_gt_2;
	--c0;
	--c1;

	_M_edges.pop_front();
}
bool			THIS::empty() const
{
	return _M_edges.empty();
}
gr::EDGE_S		THIS::front()
{
	return _M_edges.front();
}
THIS::iterator		THIS::begin()
{
	return _M_edges.begin();
}
THIS::iterator		THIS::end()
{
	return _M_edges.end();
}


