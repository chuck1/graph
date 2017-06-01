


#include <gr/layer.hpp> // gr/layer.hpp.in

typedef gr::layer THIS;

THIS::layer():
	_M_enabled(true)
{
}
bool		THIS::enabled() const
{
	return _M_enabled;
}


