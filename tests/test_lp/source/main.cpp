#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>
#include <eigen3/Eigen/Core>
#include <gr/lp.hpp>

int			main()
{
	Eigen::VectorXd B(3);
	B[0] = 100;
	B[1] = 600;
	B[2] = 300;

	Eigen::VectorXd C(3);
	C[0] = 10;
	C[1] = 6;
	C[2] = 4;

	Eigen::MatrixXd A(3, 3);
	A(0,0) = 1;
	A(0,1) = 1;
	A(0,2) = 1;
	A(1,0) = 10;
	A(1,1) = 4;
	A(1,2) = 5;
	A(2,0) = 2;
	A(2,1) = 2;
	A(2,2) = 6;
	
	gr::LP p;
	p.reset(A, B, C);
	glp_prob * lp = p._M_lp;

	double z, x1, x2, x3;

	glp_simplex(lp, NULL);
	
	z = glp_get_obj_val(lp);

	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	x3 = glp_get_col_prim(lp, 3);
	
	printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3);

	glp_delete_prob(lp);

	return 0;
}

