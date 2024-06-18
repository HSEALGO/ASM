#include "Calculations.h"
#include "cfgPars.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

//----------------------------ROOT-------------------------------

#define F(x) (f1(x) - f2(x))
#define dF(x) (df1(x) - df2(x))


bool IsdFddFpositive(dfunc *df1, dfunc *df2, double a, double b)
{
	return (dF(a)*(dF(b) - dF(a)) < 0);
}

double FindRoot(func *f1, func *f2, dfunc *df1, dfunc *df2, double a, double b, double eps)
{
	if (IsdFddFpositive(df1, df2, a, b))
	{
		while (fabs(a - b) > eps)
		{
			a = a - (b - a) / (F(b) - F(a)) * F(a);
			b = b - F(b) / dF(b);
		}
	} else
	{
		while (fabs(a - b) > eps)
		{
			a = a - F(a) / dF(a);
			b = b - (b - a) / (F(b) - F(a)) * F(b);
		}
	}
	
	printf("Found root!");
	return 0.5 * (a + b);
}

//--------------------------INTEGRAL------------------------------


//Calculate segment partisions from Newton-Cotes formula
size_t Partisions(double ddFvmax, double eps, double a, double b)
{
	printf("Done parts");
	return 1 + ceil(pow(fabs(a - b), 3) / (12 * eps) * ddFvmax);
}

double FindIntegral(func *f, double a, double b, double ddFvMax, double eps)
{
	size_t n = Partisions(ddFvMax, eps, a, b);
	double h = (b - a) / n;
	
	printf("StartIntegral");

	double ans = 0;
	ans += 0.5 * f(a);

	for (size_t i = 1; i < n - 1; i++)
	{
		ans += f(a + i * h); 
	}

	ans += 0.5 * f(b);

	return ans;
}

//-----------------------------AREA----------------------------------




//Find figure points as intersection point 

void CalcPoints(func *f1, func *f2, func *f3, 
		dfunc *df1, dfunc *df2, dfunc *df3,
		double ranges[3][2], double figure_points[3][2],
		double eps_r)
{
	figure_points[0][0] = FindRoot(f1, f2, df1, df2, ranges [0][0], ranges[0][1], eps_r);
	figure_points[0][1] = f1(figure_points[0][1]);

	figure_points[1][0] = FindRoot(f2, f3, df2, df3, ranges [1][0], ranges[1][1], eps_r);
	figure_points[1][1] = f2(figure_points[0][1]);

	figure_points[2][0] = FindRoot(f3, f1, df3, df1, ranges [2][0], ranges[2][1], eps_r);
	figure_points[2][1] = f3(figure_points[0][1]);
	return;
}





double FindArea(func *f1, func *f2, func *f3,
		dfunc *df1, dfunc *df2, dfunc *df3,
		double ranges[3][2], double ddfmaxes[3], 
		double eps, double eps_r, double eps_i)
{
	double figure_points[3][2];
	CalcPoints(f1, f2, f3, df1, df2, df3, ranges, figure_points, eps_r);

	double ans = 0;
	ans  += FindIntegral(f1, figure_points[0][0], figure_points[0][1], ddfmaxes[0], eps_i);
	ans  += FindIntegral(f2, figure_points[1][0], figure_points[1][1], ddfmaxes[1], eps_i);
	ans  += FindIntegral(f3, figure_points[2][0], figure_points[2][1], ddfmaxes[2], eps_i);

	return fabs(ans);
}

