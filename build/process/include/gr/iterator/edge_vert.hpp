/*
 * DO NOT EDIT THIS FILE
 *
 * graph/include/gr/iterator/edge_vert.hpp_in
 */

#ifndef GR_ITERATOR_EDGE_VERT_HPP_IN
#define GR_ITERATOR_EDGE_VERT_HPP_IN

#include <iterator>

#include <gr/decl.hpp> // gr/decl.hpp.in
//#include <gr/vert.hpp> // gr/vert.hpp.in
//#include <gr/vert_comp.hpp> // gr/vert_comp.hpp.in
#include <gr/edge.hpp> // gr/edge.hpp.in

namespace gr {
namespace iterator {

typedef std::iterator<std::input_iterator_tag, gr::edge> ITERATOR_EDGE;

/**
 * iterates on each edge in a vert's edge container
 */
class edge_vert:
	public ITERATOR_EDGE
{
public:
	typedef typename gr::CONT_EDGE::iterator iterator;

	typedef gr::edge const &	reference;
	typedef gr::edge		value_type;

	edge_vert(gr::container::edge &, iterator);
	edge_vert &			operator=(edge_vert const &);

	void				next();

	gr::iterator::edge_vert		operator++();
	/** postfix */
	gr::iterator::edge_vert		operator++(int);
	
	reference			operator*();
	value_type const *		operator->();

	bool				operator==(gr::iterator::edge_vert const &);
	bool				operator!=(gr::iterator::edge_vert const &);

//private:
	gr::container::edge &		_M_container;
	gr::CONT_EDGE::iterator		_M_i;
};



}}

#endif
