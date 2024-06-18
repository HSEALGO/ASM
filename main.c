#include "funcs.h"
#include "cfgPars.h"
#include "Calculations.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "float.h"

void printAns (double ans, double right)
{
	double err = fabs(ans - right);
	double eps = err / ans;
	printf("%lf   %lf   %lf\n", ans, err, eps);
}

struct Cfg cfg;

int main(int argc, char** argv)
{
	if (!(ParseCfg(&cfg, argc, argv)))
	{
		printf("Unable to parse options");
		return -1;
	}

	if (cfg.help)
		Help(argv[0]);

	if (cfg.testRoot)
	{
		if (cfg.rootCfg.numf1 == 1 && cfg.rootCfg.numf2 == 2)
		{
			double ans = FindRoot(&func1, &func2, &dfunc1, &dfunc2, cfg.rootCfg.a, cfg.rootCfg.b, cfg.rootCfg.eps);
			printAns(ans, cfg.rootCfg.ans);
		} 
		else if (cfg.rootCfg.numf1 == 2 && cfg.rootCfg.numf2 == 3)
		{
			double ans = FindRoot(&func2, &func3, &dfunc2, &dfunc3, cfg.rootCfg.a, cfg.rootCfg.b, cfg.rootCfg.eps);
			printAns(ans, cfg.rootCfg.ans);
		}
		if (cfg.rootCfg.numf1 == 3 && cfg.rootCfg.numf2 == 1)
		{
			double ans = FindRoot(&func3, &func1, &dfunc3, &dfunc1, cfg.rootCfg.a, cfg.rootCfg.b, cfg.rootCfg.eps);
			printAns(ans, cfg.rootCfg.ans);
		}
	}
	
	if (cfg.testIntegral)
	{
		printf("I'm here!");
		if (cfg.integralCfg.numf == 1)
		{
			printf("Func 1 process");
			double ans = FindIntegral(&func1, cfg.integralCfg.a, cfg.integralCfg.b, DBL_MAX, cfg.integralCfg.eps);
			printAns(ans, cfg.integralCfg.ans);
		}
		else if (cfg.integralCfg.numf == 2)
		{

			double ans = FindIntegral(&func2, cfg.integralCfg.a, cfg.integralCfg.b, DBL_MAX, cfg.integralCfg.eps);
			printAns(ans, cfg.integralCfg.ans);
		}
		else if (cfg.integralCfg.numf == 3)
		{
			double ans = FindIntegral(&func3, cfg.integralCfg.a, cfg.integralCfg.b, DBL_MAX, cfg.integralCfg.eps);
			printAns(ans, cfg.integralCfg.ans);
		}
	}

	if (!cfg.help && !cfg.testRoot && !cfg.testIntegral)
	{
		double ans = FindArea(&func1, &func2, &func3, &dfunc1, &dfunc2, &dfunc3, 
				      ranges, ddfmaxes, eps, eps_r, eps_i);
		printf ("Area is %lf", ans);
	}

	return 0;
}
