#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "locale.h"
#include <ctime>
struct x_n {
	int n;
	double* x;
	double* err;
	double* sum;
};
void locat(void);
struct x_n init(x_n a, int n);
void vvod(void);
double point(void);
void free_x(x_n a);
void copymas(double masa[], double masb[], int n);
struct x_n sinx(int n, double x);
struct x_n resinx(int n, double x);
struct x_n cosx(int n, double x);
struct x_n recosx(int n, double x);
struct x_n expx(int n, double x);
struct x_n reexpx(int n, double x);
struct x_n lnx(int n, double x);
struct x_n relnx(int n, double x);
void tablichka(char choice);