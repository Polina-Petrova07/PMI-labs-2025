#include "Lab_2.h"
unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
//sin
void sinXn(int count, double x, double* err, double* sum) {
	sum[0] = x; // Первый член ряда Тейлора для sin(x): x
	err[0] = fabs(x - sin(x)); // Ошибка для первого члена
	for (int i = 1; i < count; i++) {
		sum[i] = sum[i - 1] + pow(-1, i) * (pow(x, 2 * i + 1) / factorial(2 * i + 1));
		err[i] = fabs(sum[i] - sin(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
};
void sinXnRev(int count, double x, double* err, double* sum) {
	int last = count - 1; // Последний член, так как нумерация с нулевого индекса
	sum[last] = pow(-1, last) * (pow(x, 2 * last + 1) / factorial(2 * last + 1));
	err[last] = fabs(sum[last] - sin(x)); //Ошибка для последнего члена 
	for (int i = last - 1; i >= 0; i--) {
		sum[i] = sum[i + 1] + pow(-1, i) * (pow(x, 2 * i + 1) / factorial(2 * i + 1));
		err[i] = fabs(sum[i] - sin(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
}

//cos
void cosXn(int count, double x, double* err, double* sum) {
	sum[0] = 1;
	err[0] = fabs(1 - cos(x));
	for (int i = 1; i < count; i++) {
		sum[i] = sum[i - 1] + pow(-1, i) * (pow(x, 2 * i) / factorial(2 * i));
		err[i] = fabs(sum[i] - cos(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
};
void cosXnRev(int count, double x, double* err, double* sum) {
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

//exp
void expXn(int count, double x, double* err, double* sum) {
	sum[0] = 1;
	err[0] = fabs(1 - exp(x));
	for (int i = 1; i < count; i++) {
		sum[i] = sum[i - 1] + (pow(x, i) / factorial(i));
		err[i] = fabs(sum[i] - exp(x));
		printf("%lf\t%lf\n", sum[i], err[i]);
	}
	printf("\n");
};
void expXnRev(int count, double x, double* err, double* sum) { 
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

//ln
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
void lnXnRev(int count, double x, double* err, double* sum) {
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

void create_array(struct Xn* array, int count) {
    array->count = count;
    array->sum = (double*)malloc(sizeof(double) * array->count);
    array->err = (double*)malloc(sizeof(double) * array->count);
    for (int i = 0; i < count; i++) {
        array->err[i] = 0;
        array->sum[i] = 0;
    }
}
void free_array(struct Xn* array) {
    free(array->sum);
    free(array->err);
    array->sum = NULL;
    array->err = NULL;
    array->count = 0;
}
