#include <cassert>

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

	push(e->v0());
	push(e->v1());
}
void			THIS::push(gr::VERT_S const & v)
{
	auto it = _M_counter.find(v);
	
	if(it == _M_counter.end()) _M_counter[v] = 0;
	
	auto & c = _M_counter[v];
	
	if(c==2) ++_M_count_gt_2;
	
	++c;
}
void			THIS::pop(gr::VERT_S const & v)
{
	auto it = _M_counter.find(v);

	assert(it != _M_counter.end());
	
	int & c = it->second;

	if(c==3) --_M_count_gt_2;
	
	--c;
}
void			THIS::pop_back()
{
	auto e = _M_edges.back();
	
	pop(e->v0());
	pop(e->v1());

	_M_edges.pop_back();
}
void			THIS::pop_front()
{
	auto e = _M_edges.front();

	pop(e->v0());
	pop(e->v1());

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
int			THIS::counter(gr::VERT_S const & v) const
{
	auto it = _M_counter.find(v);
	assert(it != _M_counter.end());
	return it->second;
}


