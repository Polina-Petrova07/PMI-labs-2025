#include "lab2.h"

struct xn {
    int count;
    double x;
    double* err;
    double* sum;
};

void create_array(struct xn* array, int count) {
    array->count = count;
    array->sum = (double*)malloc(sizeof(double) * array->count);
    array->err = (double*)malloc(sizeof(double) * array->count);
    for (int i = 0; i < count; i++) {
        array->err[i] = 0;
        array->sum[i] = 0;
    }
}

void free_array(struct xn* array) {
    free(array->sum);
    free(array->err);
    array->sum = NULL;
    array->err = NULL;
    array->count = 0;
}

void test(void (*f)(int count, double x, double* err, double* sum), void (*f1)(int count, double x, double* err, double* sum)) {
    struct xn array;
    double v;
    int n;
    printf("Введите x:");
    scanf_s("%lf", &v);
    printf("Введите количество итераций:");
    scanf_s("%i", &n);
    array.x = v;
    create_array(&array, n+1);
    f(array.count, array.x, array.err, array.sum);
    f1(array.count, array.x, array.err, array.sum);
    free_array(&array);
}

int main() {
    int s;
    printf("Какую функцию вы хотите вычислить?\n1.Синус\n2.Косинус\n3.Экспанента\n4.Натуральный логарифм\n");
    scanf_s("%i", &s);
    while (s < 5) {
        switch (s)
        {
        case 1:
            test(sinXn,sinXnU);
            break;
        case 2:
            test(cosXn,cosXnU);
            break;
        case 3:
            test(expXn,expXnU);
            break;
        case 4:
            test(lnXn,lnXnU);
            break;
        default:
            break;
        }
        printf("\n");
        printf("Какую функцию вы хотите вычислить?\n1.Синус\n2.Косинус\n3.Экспанента\n4.Натуральный логарифм\n");
        scanf_s("%i", &s);
    }
}