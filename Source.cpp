#include "math.h"
#include "Header.h"
#include <iostream>

double Sin(int n, double x) {
	double r=1;
	for (int i = 1; i <= 2*n+1; i++) { r *= i; }
	int k = -1;
	if (n % 2 == 0) { k = 1; }
	return k * pow(x, n * 2 + 1) / r;
}
double Cos(int n, double x){
	double r = 1;
	for (int i = 1; i <= 2 * n; i++) { r *= i; }
	int k = -1;
	if (n % 2 == 0) { k = 1; }
	return (k * pow(x, 2 * n)) / r;
}
double Exp(int n, double x){
	double r = 1;
	for (int i = 1; i <= n; i++) { r *= i; }
	return pow(x, n) / r;
}
double Log(int n, double x){
	int k = -1;
	if (n % 2 == 0) { k = 1; }
	return (k * pow(x-1, n+1)) / (n+1);
}

void direct_sum(double* x, int l) {
	std::cout << x[0] << "\n";
	for (int i = 1; i < l;i++) {
		x[i] = x[i - 1] + x[i];
		std::cout << x[i] << "\n";
	}
}

void reverse_sum(double* x, int l) {
	double w=0;
	for (int i=l-1; i >= 0; i--) {
		for (int j = i; j >= 0; j--) { w += x[j]; }
		x[i] = w;
		w = 0;
	}

	for (int i = 0; i <l;i++) { std::cout << x[i] << "\n"; }
}