
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <locale.h>
struct xn {
    int count;
    double x;
    double* err;
    double* sum;
};
unsigned long long factorial(int n);
void sinXn(int count, double x, double* err, double* sum);
void sinXnRE(int count, double x, double* err, double* sum);
void cosXn(int count, double x, double* err, double* sum);
void cosXnRE(int count, double x, double* err, double* sum);
void expXn(int count, double x, double* err, double* sum);
void expXnRE(int count, double x, double* err, double* sum);
void lnXn(int count, double x, double* err, double* sum);
void lnXnRE(int count, double x, double* err, double* sum);
void createarr(struct xn* array, int count);
void freearr(struct xn* array);

 