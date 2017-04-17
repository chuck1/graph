#include <iostream>
#include <cassert>
#include <sstream>

#include <gr/vert.hpp> // gr/vert.hpp.in
#include <gr/edge_data.hpp> // gr/edge.hpp.in
#include <gr/layer.hpp>

#include <gr/edge.hpp> // gr/edge.hpp_in

typedef gr::edge THIS;

THIS::edge(gr::VERT_S const & v0, gr::VERT_S const & v1):
	_M_v0(v0),
	_M_v1(v1)
	//_M_enabled(true)
{
	assert(v0);
	assert(v1);
}
std::string		THIS::name() const
{
	std::stringstream ss;
	ss << this;
	return ss.str();
}
gr::VERT_S		THIS::other(gr::VERT_S v) const
{
	auto v0 = _M_v0.lock();
	auto v1 = _M_v1.lock();

	if((*v0) == (*v)) return v1;
	if((*v1) == (*v)) return v0;
	throw std::exception();
}
bool			THIS::enabled() const
{
	//assert(!_M_v0.expired());
	if(_M_v0.expired()) return false;

	if(_M_v1.expired()) return false;

	auto const & v0 = _M_v0.lock();
	auto const & v1 = _M_v1.lock();
	
	if(!v0->enabled()) return false;

	if(!v1->enabled()) return false;
	
	if(!_M_layer.expired()) {
		if(!_M_layer.lock()->enabled()) return false;
	}

	return true;
}
bool			THIS::operator<(gr::edge const & e) const
{
	/*
	auto e0v0 = *v0();
	auto e0v1 = *v1();
	auto e1v0 = *e.v0();
	auto e1v1 = *e.v1();
	
	if(v00 == v01) {
		return (v10 < v11);
	}

	return (v00 < v01);
	*/
	return (this < &e);
}
bool			THIS::operator==(gr::edge const & e) const
{
	/*
	gr::VERT_S pv00 = _M_v0.lock();
	gr::VERT_S pv01 = e._M_v0.lock();
	gr::VERT_S pv10 = _M_v1.lock();
	gr::VERT_S pv11 = e._M_v1.lock();
	gr::vert & v00 = *pv00;
	gr::vert & v01 = *pv01;
	gr::vert & v10 = *pv10;
	gr::vert & v11 = *pv11;

	return (v00 == v01) && (v10 == v11);
	*/

	return (&e == this);
}
bool			THIS::operator!=(gr::edge const & e) const
{
	return !operator==(e);
}
void			THIS::swap()
{
	std::swap(_M_v0, _M_v1);
}
gr::VERT_S		THIS::v0() const
{
	auto v = _M_v0.lock();
	assert(v);
	return _M_v0.lock();
}
gr::VERT_S		THIS::v1() const
{
	auto v = _M_v1.lock();
	assert(v);
	return v;
}
bool			THIS::contains(gr::VERT_S v) const
{
	if((*_M_v0.lock()) == (*v)) return true;
	if((*_M_v1.lock()) == (*v)) return true;
	return false;
}



