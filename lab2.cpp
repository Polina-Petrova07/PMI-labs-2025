#include "stdio.h"
#include "stdlib.h"
#include "math.h"

struct xn {
	int count;
	double* x;
	double* err;
	double* sum;
};


int factorial(int n) {
	if (n < 0) return 0;
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}
void sinXn(int count, double x, double* err, double* sum) {
	sum[0] = x;
	err[0] = fabs(x - sin(x));
	for (int i = 1; i < count; i++) {
		sum[i] = sum[i - 1] + pow(-1, i) * (pow(x, 2 * i + 1) / factorial(2 * i + 1));
		err[i] = fabs(sum[i] - sin(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
};
void sinXnU(int count, double x, double* err, double* sum) {
	int last = count - 1;
	sum[last] = pow(-1, last) * (pow(x, 2 * last + 1) / factorial(2 * last + 1));
	err[last] = fabs(sum[last] - sin(x));
	for (int i = last - 1; i >= 0; i--) {
		sum[i] = sum[i + 1] + pow(-1, i) * (pow(x, 2 * i + 1) / factorial(2 * i + 1));
		err[i] = fabs(sum[i] - sin(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
}

void cosXn(int count, double x, double* err, double* sum) {
	sum[0] = 1;
	err[0] = fabs(x - cos(x));
	for (int i = 1; i < count; i++) {
		sum[i] = sum[i - 1] + pow(-1, i) * (pow(x, 2 * i) / factorial(2 * i));
		err[i] = fabs(sum[i] - cos(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
};
void cosXnU(int count, double x, double* err, double* sum) {
	int last = count - 1; 	
	sum[last] = pow(-1, last) * (pow(x, 2 * last) / factorial(2 * last));
	err[last] = fabs(sum[last] - cos(x));
	for (int i = last - 1; i >= 0; i--) {
		sum[i] = sum[i + 1] + pow(-1, i) * (pow(x, 2 * i) / factorial(2 * i));
		err[i] = fabs(sum[i] - cos(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
}

void expXn(int count, double x, double* err, double* sum) {
	sum[0] = 1;
	err[0] = fabs(x - exp(x));
	for (int i = 1; i < count; i++) {
		sum[i] = sum[i - 1] + (pow(x, i) / factorial(i));
		err[i] = fabs(sum[i] - exp(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
};
void expXnU(int count, double x, double* err, double* sum) { 
	int last = count - 1; 
	sum[last] = pow(x, last) / factorial(last);
	err[last] = fabs(sum[last] - exp(x));
	for (int i = last - 1; i >= 0; i--) {
		sum[i] = sum[i + 1] + pow(x, i) / factorial(i);
		err[i] = fabs(sum[i] - exp(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
}

void lnXn(int count, double x, double* err, double* sum) {
	sum[0] = x;
	err[0] = fabs(x - log(x+1));
	for (int i = 1; i < count; i++) {
		sum[i] = sum[i - 1] + pow(-1, i) * (pow(x, i+1) / (i+1));
		err[i] = fabs(sum[i] - log(x+1));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
};
void lnXnU(int count, double x, double* err, double* sum) {
	int last = count - 1; 
	sum[last] = pow(-1, last) * pow(x, last + 1) / (last + 1);
	err[last] = fabs(sum[last] - log(x + 1));
	for (int i = last - 1; i >= 0; i--) {
		sum[i] = sum[i + 1] + pow(-1, i) * pow(x, i + 1) / (i + 1);
		err[i] = fabs(sum[i] - log(x + 1));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
}