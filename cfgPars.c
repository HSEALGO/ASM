#include "cfgPars.h"
#include <getopt.h>
#include <string.h>
#include <stdio.h>


const char* helpstr = 
"Usage:\n"
"%s [OPTIONS]\n"
"\n"
"Options:\n"
"-h, --help          Print help\n"
"-r, --root          Print roots\n"
"-i, --iterations    Print number of iterations needed to count integral\n"
"-R, --test-root F1:F2:A:B:E:R\n"
"                    Counts intersection point of functions with\n"
"                    numbers F1 and F2 (1 <= F1, F2 <= 3) on range [A, B]\n"
"                    with precision E. Compares an answer to R.\n"
"                    Prints answer, absolute and relative error.\n"
"-I, --test-integral F:A:B:E:R\n"
"                    Counts integral of function with numbers F (1 <= F <= 3)\n"
"                    on range [A, B] with precision E. Compares an answer to R.\n"
"                    Prints answer, absolute and relative error.\n";


const char* optstr = "hriR:I:";
struct option options[] = {
	{"help", no_argument, 0, 'h'},	
	{"root", no_argument, 0, 'r'},
	{"iterations", no_argument, 0, 'i'},
	{"test-root", required_argument, 0, 'R'},
	{"test-integral", required_argument, 0, 'I'},
	{0, 0, 0, 0} 
};

void Reset(struct Cfg *cfg)
{
	cfg->help = false;
	cfg->root = false;
	cfg->iterations = false;
	cfg->testRoot = false;
	cfg->testIntegral = false;
}

bool ParseRootCfg(struct RootCfg *cfg, const char* s)
{
	int opts = sscanf(s, "%d:%d:%lf:%lf:%lf:%lf",
			&cfg->numf1, &cfg->numf2, &cfg->a, &cfg->b, 
			&cfg->eps, &cfg->ans);

	bool res = (opts == 6) && (cfg->numf1 >= 1) && (cfg->numf2 >= 1) &&
				  (cfg->numf1 <= 3) && (cfg->numf2 <= 3);
	return res;
} 

bool ParseIntegralCfg(struct IntegralCfg *cfg, const char* s)
{
	printf("Parsing Integral!");
	int opts = sscanf(s, "%d:%lf:%lf:%lf:%lf",
			&cfg->numf, &cfg->a, &cfg->b, 
			&cfg->eps, &cfg->ans);


	bool res = (opts == 5) && (cfg->numf >= 1) && (cfg->numf <= 1);

	return res;
}

bool ParseCfg(struct Cfg *cfg, int argc, char** argv)
{
	printf("Start to parse cfg!");
	Reset(cfg);

	int opt;

	while ((opt = getopt_long(argc, argv, optstr, options, NULL)) != -1)
	{
		printf("New opt!");
		switch (opt) 
		{
			case 'h':
				cfg->help = true;
				break;
			case 'r':
				cfg->root = true;
				break;
			case 'i':
				cfg->iterations = true;
				break;
			case 'R':
				cfg->testRoot = true;
				if (!ParseRootCfg(&cfg->rootCfg, optarg)) return false;
				break;
			case 'I':
				cfg->testIntegral = true;
				if (!ParseIntegralCfg(&cfg->integralCfg, optarg)) return false;
				break;
			default:
				return false;
		}
	}

	return optind == argc;
}


void Help(const char* exe)
{
	printf(helpstr, exe);
}
