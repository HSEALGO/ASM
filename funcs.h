#pragma once

//---------------------DECLARATION-------------------
double func1(double x);
double func2(double x);
double func3(double x);

double dfunc1(double x);
double dfunc2(double x);
double dfunc3(double x);

//--------------------CONSTANTS----------------------
double ranges[3][2] = {
	{5, 7}, //f1 f2
	{3, 5}, //f2 f3
	{4.01, 5} };

double eps = 0.0001;

//Were calculated
double eps_r = 0.00001;
double eps_i = 0.00001;

double ddfmaxes[3] = {0, 0, 2};




