#include <gr/layer.hpp> // gr/layer.hpp_in

#include <gr/LayerStack.hpp> // gr/LayerStack.hpp_in

typedef gr::LayerStack THIS;

bool			THIS::enabled() const
{
	return get<bool, &gr::layer::_M_enabled>(true);
}
bool			THIS::plot() const
{
	return get<bool, &gr::layer::_M_plot>(true);
}
std::string		THIS::plot_color() const
{
	//static constexpr char const * def = "";
	//static char * const def = new char[8];
	//def[0] = 0;
	//char * def = new char[1];
	//def[0] = 0;

	return get<std::string, &gr::layer::_M_plot_color>("");
}

void			THIS::push_front(LAYER_S l)
{
	_M_stack.push_front(l);
}
void			THIS::pop_front()
{
	_M_stack.pop_front();
}
gr::LAYER_S &		THIS::front()
{
	return _M_stack.front();
}
bool			THIS::contains(
		gr::S_Layer const & l) const
{
	for(auto p : _M_stack)
	{
		if(p == l) return true;
	}
	return false;
}


