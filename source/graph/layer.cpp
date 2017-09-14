


#include <gr/layer.hpp> // gr/layer.hpp.in

typedef gr::layer THIS;

THIS::layer():
	_M_enabled(true)
{
}
THIS::layer(bool e):
	_M_enabled(e)
{
}
bool		THIS::enabled() const
{
	return _M_enabled;
}


