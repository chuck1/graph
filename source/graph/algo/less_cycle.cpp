
#include <gr/algo/cycle.hpp> // gr/algo/cycle.hpp_in
#include <gr/edge.hpp>

#include <gr/algo/less_cycle.hpp> // gr/algo/less_cycle.hpp_in


bool		gr::algo::less_cycle::operator()(cycle const & c0, cycle const & c1)
{
	if(c0.size() == c1.size())
	{
		auto it1 = c1.begin();
		auto it0 = c0.begin();
		for(; it0 != c0.end(); ++it0, ++it1)
		{
			gr::edge & e0 = *(*it0);
			gr::edge & e1 = *(*it1);
			if(e0 != e1) return e0 < e1;
		}
		return false;
	}

	return c0.size() < c1.size();
}

