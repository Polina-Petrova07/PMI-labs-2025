#include "pch.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

class TaylorSeries {
public:
	static double nthSin(double x, double prev, int n) {
		return n == 0 ? x : (-(prev * x * x) / ((2 * n)*(2 * n + 1)));
	}

	static double nthCos(double x, double prev, int n) {
		return n == 0 ? 1 : (-(prev * x * x) / ((2 * n) * (2 * n - 1)));
	}

	static double nthExp(double x, double prev, int n) {
		return n == 0 ? 1 : prev * x / n;
	}

	static double nthLog(double x, double prev, int n) {
		return n == 0 ? x : -prev * x * n / (n + 1);
	}
};

class SummationStrategy {
public:
	virtual ~SummationStrategy() = default;
	virtual double compute(int n, double(*termFunc)(double, double, int), double x) = 0;
};

class OneToNStrategy : public SummationStrategy {
public:
	double compute(int n, double(*termFunc)(double, double, int), double x) override {
		double ret = 0, val = 0;
		for (int i = 0; i < n; i++) {
			val = termFunc(x, val, i);
			ret += val;
		}
		return ret;
	}
};

class NToOneStrategy : public SummationStrategy {
public:
	double compute(int n, double(*termFunc)(double, double, int), double x) override {
		double ret = 0;
		double* arr = (double*)malloc(n * sizeof(double));
		arr[0] = termFunc(x, 0, 0);
		for (int i = 1; i < n; i++) {
			arr[i] = termFunc(x, arr[i - 1], i);
		}
		for (int i = n - 1; i >= 0; i--) {
			ret += arr[i];
		}
		free(arr);
		return ret;
	}
};

class PairSumStrategy : public SummationStrategy {
private:
	double pairSumFunc(double* arr, int l, int r) {
		double ret = 0;
		if (r - l <= 5) {
			for (int i = r - 1; i >= l; i--) ret += arr[i];
			return ret;
		}
		return pairSumFunc(arr, l, (l + r) / 2) + pairSumFunc(arr, (l + r) / 2, r);
	}

public:
	double compute(int n, double(*termFunc)(double, double, int), double x) override {
		double* arr = (double*)malloc(n * sizeof(double));
		arr[0] = termFunc(x, 0, 0);
		for (int i = 1; i < n; i++) {
			arr[i] = termFunc(x, arr[i - 1], i);
		}
		double ret = pairSumFunc(arr, 0, n);
		free(arr);
		return ret;
	}
};

int main() {
	double X, sinv, cosv, expv, logv;
	int sum;
	int n;

	printf("Select the X value that you would like to approximate Sin, Cos, Exponent and Log with via the Taylor series: ");
	scanf_s("%lf", &X);
	printf("Values being compared to: Sin: %.16lf, Cos:%.16lf, Exp:%.16lf, log:%.16lf \n\n",
		sin(X), cos(X), exp(X), log(1 + X));
	printf("Select the summing method you would like to use for the approximation:\n\n1. 1 to N\n2. N to 1. \n3. Pairs\n");
	scanf_s("%d", &sum);
	printf("\n\n");

	SummationStrategy* strategy = nullptr;
	switch (sum) {
	case 1: strategy = new OneToNStrategy(); break;
	case 2: strategy = new NToOneStrategy(); break;
	case 3: strategy = new PairSumStrategy(); break;
	default:
		printf("Invalid selection\n");
		return 1;
	}

	for (n = 1; n < 100000000; n *= 2) {
		sinv = fabs(strategy->compute(n, TaylorSeries::nthSin, X) - sin(X));
		cosv = fabs(strategy->compute(n, TaylorSeries::nthCos, X) - cos(X));
		expv = fabs(strategy->compute(n, TaylorSeries::nthExp, X) - exp(X));

		printf("N = %d: Sin diff = %.16lf, Cos diff = %.16lf, Exp diff = %.16lf",
			n, sinv, cosv, expv);

		if (X <= 1 && X >= -1) {
			logv = fabs(strategy->compute(n, TaylorSeries::nthLog, X) - log(1 + X));
			printf(", Log diff = %.16lf", logv);
		}
		printf("\n\n");
	}

	delete strategy;
	return 0;
}
