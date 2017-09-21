#include <gr/lp/Error.hpp> // gr/lp/Error.hpp_in

typedef gr::lp::Error THIS;

THIS::Error(int rc):
	_M_rc(rc)
{
	_M_s = new char[128];
	sprintf(_M_s, "glp error code: %i", _M_rc);
}
const char *    THIS::what() const noexcept
{
	return _M_s;
}

