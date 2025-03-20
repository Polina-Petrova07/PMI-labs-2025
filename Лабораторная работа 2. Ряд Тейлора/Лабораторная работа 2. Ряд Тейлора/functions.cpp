#include "stdio.h"
#include "math.h"
void sinus(long double x, int n,long double *arr) {
	arr[0] = x;
	for (int i = 1;i < n;i++) {
		arr[i] = (-1) * x * x * arr[i - 1] / (2 * i) / (2 * i + 1);
	}
}
void cosinus(long double x, int n,long double* arr) {
	arr[0] = 1.0;
	for (int i = 1;i < n;i++) {
		arr[i] = (-1) * x * x * arr[i - 1] / (2 * i) / (2 * i - 1);
	}
}
void e_x(long double x,int n,long double *arr) {
	arr[0] = 1.0;
	for (int i = 1;i < n;i++) {
		arr[i] = x * arr[i - 1] / i;
	}
}
void nat_log(long double x, int n, long double* arr) {
	arr[0] = x;
	for (int i = 1;i < n;i++) {
		arr[i] = ((-1) * x * i / (i + 1) * arr[i - 1]);
	}
}
void straight(long double real, int n, long double sum, long double* arr) {
	for (int i = 0;i < n;i++) {
		sum += arr[i];
	}
	printf("\nПри разложении в ряд Тейлора до %i слагаемых: %.20Lf\n\n", n, sum);
	printf("Погрешность: %.20lf процентов\n\n", fabs((sum - real) / real) * 100);
}
void reverse(long double real,int n, long double sum, long double* arr) {
	for (int i = n-1;i>=0;i--) {
		sum += arr[i];
	}
	printf("\nПри разложении в ряд Тейлора до %i слагаемых: %.20Lf\n\n", n, sum);
	printf("Погрешность: %.20lf процентов\n\n", fabs((sum - real) / real) * 100);
}
void decision(int decision1, int decision2, long double x, int n, long double* arr) {
	long double sum = 0.0;
	if (decision1 == 1) {
		sinus(x, n, arr);
		long double real = sin(x);
		printf("\nsin %.20Lf = %.20Lf", x, sin(x));
		if (decision2 == 1) {
			straight(real,n, sum, arr);
		}
		else {
			reverse(real,n, sum, arr);
		}
	}
	if (decision1 == 2) {
		cosinus(x, n, arr);
		long double real = cos(x);
		printf("\ncos %.20Lf = %.20Lf", x, cos(x));
		if (decision2 == 1) {
			straight(real,n, sum, arr);
		}
		else {
			reverse(real,n, sum, arr);
		}
	}
	if (decision1 == 3) {
		e_x(x, n, arr);
		long double real = exp(x);
		printf("\ne^ %.20Lf = %.20Lf", x, exp(x));
		if (decision2 == 1) {
			straight(real,n, sum, arr);
		}
		else {
			reverse(real,n, sum, arr);
		}
	}
	if (decision1 == 4) {
		nat_log(x, n, arr);
		long double real = log(1 + x);
		printf("\nln(1 + %.20Lf) = %.20Lf", x, log(1+x));
		if (decision2 == 1) {
			straight(real,n, sum, arr);
		}
		else {
			reverse(real,n, sum, arr);
		}
	}
}