#include <iostream>
#include <cassert>

#include <gr/vert.hpp> // gr/vert.hpp.in
#include <gr/edge_data.hpp> // gr/edge.hpp.in

#include <gr/edge.hpp> // gr/edge.hpp.in

typedef gr::edge THIS;

//THIS::edge()
//{
//	std::cout << "edge default ctor" << std::endl;
//}
THIS::edge(gr::VERT_S const & v0, gr::VERT_S const & v1, EDGE_DATA_S const & data):
	_M_v0(v0),
	_M_v1(v1),
	_M_data(data)
{
//	std::cout << "edge ctor" << std::endl;
	assert(v0);
	assert(v1);
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
	
	if(!_M_data->_M_enabled) return false;

	return true;
}
bool			THIS::operator<(gr::edge const & e) const
{
	gr::VERT_S pv00 = _M_v0.lock();
	gr::VERT_S pv01 = e._M_v0.lock();
	gr::VERT_S pv10 = _M_v1.lock();
	gr::VERT_S pv11 = e._M_v1.lock();
	gr::vert & v00 = *pv00;
	gr::vert & v01 = *pv01;
	gr::vert & v10 = *pv10;
	gr::vert & v11 = *pv11;
	
	if(v00 == v01) {
		return (v10 < v11);
	}

	return (v00 < v01);
}
bool			THIS::operator==(gr::edge const & e) const
{
	gr::VERT_S pv00 = _M_v0.lock();
	gr::VERT_S pv01 = e._M_v0.lock();
	gr::VERT_S pv10 = _M_v1.lock();
	gr::VERT_S pv11 = e._M_v1.lock();
	gr::vert & v00 = *pv00;
	gr::vert & v01 = *pv01;
	gr::vert & v10 = *pv10;
	gr::vert & v11 = *pv11;

	return (v00 == v01) && (v10 == v11);
}



