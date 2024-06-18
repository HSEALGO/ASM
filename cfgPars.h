#pragma once
#include <stdbool.h>

struct RootCfg
{
	int numf1, numf2;
	double a, b;
	double eps;
	double ans;
};

struct IntegralCfg
{
	int numf;
	double a, b;
	double eps;
	double ans;
};

struct Cfg
{
	bool help, root, iterations;

	bool testRoot;
	struct RootCfg rootCfg;
	bool testIntegral;
	struct IntegralCfg integralCfg;
};

bool ParseCfg(struct Cfg *cfg, int argc, char** argv);
void Help(const char *exe);
void Reset(struct Cfg *cfg);

