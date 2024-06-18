#pragma once

typedef double func(double);
typedef double dfunc(double);
double FindRoot(func *f1, func *f2, dfunc *df1, dfunc *df2, double a, double b, double eps);
double FindIntegral(func *f, double a, double b, double ddFvMax, double eps);
double FindArea(func *f1, func *f2, func *f3,
		dfunc *df1, dfunc *df2, dfunc *df3,
		double ranges [3][2], double ddfmaxes[3], 
		double eps, double eps_r, double eps_i);

