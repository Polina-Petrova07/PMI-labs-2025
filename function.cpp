#include "laboratory_work.h"

unsigned long long factorial(int n) {
    if (n < 0) return 0;

    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

//sin(x)
void sinXn(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    sum[0] = x; 
    err[0] = fabs(sum[0] - sin(x));

    for (int i = 1; i < count; i++) {
        double term = pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        sum[i] = sum[i - 1] + term;
        err[i] = fabs(sum[i] - sin(x));
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}
void sinXnRE(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    int last = count - 1;
    sum[last] = pow(-1, last) * pow(x, 2 * last + 1) / factorial(2 * last + 1);
    err[last] = fabs(sum[last] - sin(x));

    for (int i = last - 1; i >= 0; i--) {
        double term = pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        sum[i] = sum[i + 1] + term; 
        err[i] = fabs(sum[i] - sin(x)); 
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}

//cos(x)
void cosXn(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    sum[0] = 1.0;
    err[0] = fabs(sum[0] - cos(x));

    for (int i = 1; i < count; i++) {
        double term = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        sum[i] = sum[i - 1] + term; 
        err[i] = fabs(sum[i] - cos(x)); 
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}
void cosXnRE(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    int last = count - 1;
    sum[last] = pow(-1, last) * pow(x, 2 * last) / factorial(2 * last);
    err[last] = fabs(sum[last] - cos(x));

    for (int i = last - 1; i >= 0; i--) {
        double term = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        sum[i] = sum[i + 1] + term; 
        err[i] = fabs(sum[i] - cos(x)); 
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}

//exp
void expXn(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    sum[0] = 1.0; 
    err[0] = fabs(sum[0] - exp(x));

    for (int i = 1; i < count; i++) {
        double term = pow(x, i) / factorial(i);
        sum[i] = sum[i - 1] + term; 
        err[i] = fabs(sum[i] - exp(x));
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}
void expXnRE(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    int last = count - 1;
    sum[last] = pow(x, last) / factorial(last);
    err[last] = fabs(sum[last] - exp(x));

    for (int i = last - 1; i >= 0; i--) {
        double term = pow(x, i) / factorial(i);
        sum[i] = sum[i + 1] + term; 
        err[i] = fabs(sum[i] - exp(x)); 
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}

//ln(1+x)
void lnXn(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    sum[0] = x;
    err[0] = fabs(sum[0] - log(1 + x));

    for (int i = 1; i < count; i++) {
        double term = pow(-1, i) * (pow(x, i + 1) / (i + 1));
        sum[i] = sum[i - 1] + term;
        err[i] = fabs(sum[i] - log(1 + x));
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}
void lnXnRE(int count, double x, double* err, double* sum) {
    if (sum == NULL || err == NULL) {
        printf("Ошибка: нулевой указатель.\n");
        return;
    }
    int last = count - 1;
    sum[last] = pow(-1, last) * pow(x, last + 1) / (last + 1);
    err[last] = fabs(sum[last] - log(1 + x));

    for (int i = last - 1; i >= 0; i--) {
        double term = pow(-1, i) * pow(x, i + 1) / (i + 1);
        sum[i] = sum[i + 1] + term;
        err[i] = fabs(sum[i] - log(1 + x));
        printf("Шаг %d: Сумма = %lf, Ошибка = %lf\n", i, sum[i], err[i]);
    }
    printf("\n");
}
void createarr(struct xn* array, int count) {
    if (count <= 0) {
        printf("Ошибка: некорректное количество элементов.\n");
        exit(1);
    }

    array->count = count;
    array->sum = (double*)malloc(sizeof(double) * array->count);
    array->err = (double*)malloc(sizeof(double) * array->count);

    if (array->sum == NULL || array->err == NULL) {
        printf("Ошибка выделения памяти.\n");
        free(array->sum);
        free(array->err);
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        array->sum[i] = 0;
        array->err[i] = 0;
    }
}
void freearr(struct xn* array) {
    if (array->sum != NULL) {
        free(array->sum);
        array->sum = NULL;
    }
    if (array->err != NULL) {
        free(array->err);
        array->err = NULL;
    }
    array->count = 0;
}
