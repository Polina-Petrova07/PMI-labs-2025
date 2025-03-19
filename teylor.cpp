#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#define _USE_MATH_DEFINES
#include <math.h>
#define PI M_PI
#include <locale.h>

void sinx(float* terms, int n, float x)
{
    x = fmodf(x, 2.0f * (float)PI);
    terms[0] = x;
    for (int i = 1; i < n; i++) {
        terms[i] = (terms[i - 1] * -1 * x * x) / ((2 * i + 1) * (2 * i));
    }
}

void cosx(float* terms, int n, float x)
{
    x = fmodf(x, 2.0f * (float)PI);
    terms[0] = 1.0f;
    for (int i = 1; i < n; i++) {
        terms[i] = (terms[i - 1] * -1 * x * x) / ((2 * i - 1) * (2 * i));
    }
}

void ln(float* terms, int n, float x)
{
    terms[0] = x;
    for (int i = 1; i < n; i++) {
        terms[i] = (terms[i - 1] * -1 * x * i) / (i + 1);
    }
}

void expx(float* terms, int n, float x)
{
    terms[0] = 1.0f;
    for (int i = 1; i < n; i++) {
        terms[i] = (terms[i - 1] * x) / i;
    }
}


float direct_sum(float* terms, int n)
{
    float fx = 0.0f;
    for (int i = 0; i < n; i++) {
        fx += terms[i];
    }
    return fx;
}

float reverse_sum(float* terms, int n)
{
    float fx = 0.0f;
    for (int i = n - 1; i >= 0; i--) {
        fx += terms[i];
    }
    return fx;
}



void filling(float* terms, int n, int func, float x, float* direct_fx, float* reverse_fx, float* expected_res)
{
    if (func == 1) {
        sinx(terms, n, x);
        *expected_res = sin(x);
    }
    if (func == 2) {
        cosx(terms, n, x);
        *expected_res = cos(x);
    }
    if (func == 3) {
        ln(terms, n, x);
        *expected_res = log(1 + x);
    }
    if (func == 4) {
        expx(terms, n, x);
        *expected_res = exp(x);
    }

    *direct_fx = direct_sum(terms, n);
    *reverse_fx = reverse_sum(terms, n);
}
int countDigits(int number) {
    if (number == 0) return 1; 
    int count = 0;
    while (number != 0) {
        number /= 10; 
        count++;
    }
    return count;
}



void printres(int n, float x, int func)
{
    int k = countDigits(n), pr = 1;
    float direct_fx, reverse_fx, expected_res;
    printf("\n");
    printf("n %*s| Прямое   | Обратное | Значение из math.h \n", k, " ");
    for (int i = 1; i < n + 1; i++)
    {
        float* terms = (float*)malloc(sizeof(float) * i);
        filling(terms, i, func, x, &direct_fx, &reverse_fx, &expected_res);
        if (countDigits(i) > countDigits(i - 1))
            k--;
        printf("%d %*s| %f | %f | %f\n", i, k, " ", direct_fx, reverse_fx, expected_res);
        if (pr == 1 && ((expected_res - direct_fx) == 0.0 || (expected_res - reverse_fx) == 0) )
        {
            printf("Значение сравнялось со значением из math.h \n");
            pr--;
        }
        free(terms);
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int n, func;
    float x;

    printf("Выберите функцию:\n");
    printf("1. sinx\n");
    printf("2. cosx\n");
    printf("3. ln(1+x)\n");
    printf("4. e^x\n");
    scanf_s("%d", &func);

    printf("Введите количество элементов: ");
    scanf_s("%d", &n);

    printf("\nВведите x: ");
    scanf_s("%f", &x);
    printres(n, x, func);
}
