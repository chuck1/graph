#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

#include <eigen3/Eigen/Core>

#include <gr/lp/Error.hpp> // gr/lp.hpp_in

#include <gr/lp/LP.hpp> // gr/lp.hpp_in

typedef gr::lp::LP THIS;

THIS::LP():
	_M_lp(0),
	_M_r(0),
	_M_c(0)
{
}
void			THIS::set_col_kind(int kind)
{
	for(unsigned int i = 0; i < _M_c; ++i)
		glp_set_col_kind(_M_lp, i+1, kind);
}
void			THIS::reset(
		Eigen::MatrixXd const & A, 
		Eigen::VectorXd const & B, 
		Eigen::VectorXd const & C)
{
	assert(A.rows() == B.size());
	assert(A.cols() == C.size());

	_M_r = A.rows();
	_M_c = A.cols();

	int * ia = new int[1 + _M_r * _M_c];
	int * ja = new int[1 + _M_r * _M_c];
	double * ar = new double[1 + _M_r * _M_c];

	_M_lp = glp_create_prob(); assert(_M_lp);
	
	glp_set_prob_name(_M_lp, "sample"); assert(_M_lp);
	
	glp_set_obj_dir(_M_lp, GLP_MAX); assert(_M_lp);
	
	glp_add_rows(_M_lp, _M_r); assert(_M_lp);

	for(unsigned int i = 0; i < _M_r; ++i)
	{
		//glp_set_row_name(lp, i, "p");
		glp_set_row_bnds(_M_lp, i+1, GLP_UP, 0.0, B[i]); assert(_M_lp);
	}
	
	glp_add_cols(_M_lp, _M_c); assert(_M_lp);
	
	for(unsigned int i = 0; i < _M_c; ++i)
	{
		//glp_set_col_name(lp, 1, "x1");
		glp_set_col_bnds(_M_lp, i+1, GLP_LO, 0.0, 0.0); assert(_M_lp);
		glp_set_obj_coef(_M_lp, i+1, C[i]); assert(_M_lp);
	}
	
	int k = 1;
	for(unsigned int i = 0; i < _M_r; ++i)
	{
		for(unsigned int j = 0; j < _M_c; ++j)
		{
			ia[k] = i+1;
			ja[k] = j+1;
			ar[k] = A(i,j);
			++k;
		}
	}

	glp_load_matrix(_M_lp, _M_r*_M_c, ia, ja, ar);
}
void			THIS::intopt(glp_iocp const * param)
{
	int rc = glp_intopt(_M_lp, param);
	if(rc != 0) throw gr::lp::Error(rc);
}

