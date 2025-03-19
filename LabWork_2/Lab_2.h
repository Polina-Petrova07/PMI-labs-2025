#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Xn {
    int count;
    double x;
    double* err;
    double* sum;
};
unsigned long long factorial(int n); //Вычисление факториала

void sinXn(int count, double x, double* err, double* sum); //Прямое суммирование
void sinXnRev(int count, double x, double* err, double* sum); //Обратное (Rev-->reverse) суммирование

void cosXn(int count, double x, double* err, double* sum); //Прямое суммирование
void cosXnRev(int count, double x, double* err, double* sum); //Обратное (Rev-->reverse) суммирование

void expXn(int count, double x, double* err, double* sum); //Прямое суммирование
void expXnRev(int count, double x, double* err, double* sum); //Обратное (Rev-->reverse) суммирование

void lnXn(int count, double x, double* err, double* sum); //Прямое суммирование
void lnXnRev(int count, double x, double* err, double* sum); //Обратное (Rev-->reverse) суммирование

void create_array(struct Xn* array, int count);
void free_array(struct Xn* array);