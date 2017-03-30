/*
 * DO NOT EDIT THIS FILE
 *
 * /home/crymal/git/graph/include/gr/iterator/edge_graph.hpp_in
 */

#ifndef GR_ITERATOR_EDGE_GRAPH_HPP_IN
#define GR_ITERATOR_EDGE_GRAPH_HPP_IN

#include <iterator>

#include <gr/decl.hpp> // gr/decl.hpp.in
//#include <gr/vert.hpp> // gr/vert.hpp.in
#include <gr/vert_comp.hpp> // gr/vert_comp.hpp.in
#include <gr/edge.hpp> // gr/edge.hpp.in

namespace gr {
namespace iterator {

typedef std::iterator<std::input_iterator_tag, gr::edge> ITERATOR_EDGE;

/**
 * iterates on each unique edge of graph. first iterators on each vert, then
 * iterates on each edge of the vert's edge container if the opposite vert evaluates to
 * less than the first vert
 */
class edge_graph:
	public ITERATOR_EDGE
{
public:
	typedef gr::edge const &	reference;
	typedef gr::edge		value_type;

	typedef typename gr::CONT_VERT::iterator iterator0;
	typedef typename gr::CONT_EDGE::iterator iterator1;

	edge_graph(gr::container::vert &, iterator0 const &);
	edge_graph(gr::container::vert &, iterator0 const &, iterator1 const &);
	
	edge_graph			operator=(edge_graph const &);

	/** prefix */
	gr::iterator::edge_graph	operator++();
	/** postfix */
	gr::iterator::edge_graph	operator++(int);

	void				next();

	reference			operator*();
	value_type const *		operator->();

	bool				operator==(gr::iterator::edge_graph const &);
	bool				operator!=(gr::iterator::edge_graph const &);

//private:
	gr::container::vert &		_M_container;
	gr::CONT_VERT::iterator		_M_i;
	gr::CONT_EDGE::iterator		_M_j;
	//value_type			_M_value;
};


}}

#endif
