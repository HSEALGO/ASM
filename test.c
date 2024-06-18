#include "Calculations.h"
#include "cfgPars.h"
#include <stdio.h>
#include <math.h>

void ASSERT_EQ(double a, double b, double eps)
{
	if (fabs(a - b) < eps)
	{
		printf("PASSED\n"); 
	} else 
	{
		printf("FAILED\n");
	}
}
//Test
double testf1 (double x)
{
	return sin(x) * sin(x) + 2;
}

double testdf1 (double x)
{
	return sin(2 * x);
}

double testf2 (double x)
{
	return 3 * x + 3;
}

double testdf2 (double x)
{
	return 3;
}

double testf3 (double x)
{
	return x * x;
}

double testdf3(double x)
{
	return 2 * x;
}


double testranges[3][2] = {{-1, 1}, {-1, 0}, {1, 2}};
double testddfmax[3] = {2, 0, 2};

//Ans
double roots[3] = {-0.303554, -0.791287, 1.752088};
double integrals[3];
int main()
{
	double r1 = FindRoot(&testf1, &testf2, &testdf1, &testdf2, testranges[0][0], testranges[0][1], 0.00001);
	ASSERT_EQ(r1, roots[0], 0.00001);
	double r2 = FindRoot(&testf2, &testf3, &testdf2, &testdf3, testranges[1][0], testranges[1][1], 0.00001);
	ASSERT_EQ(r2, roots[1], 0.00001);
	double r3 = FindRoot(&testf3, &testf1, &testdf3, &testdf1, testranges[2][0], testranges[2][1], 0.00001);
	ASSERT_EQ(r3, roots[2], 0.00001);
	return 0;
}
