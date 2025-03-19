#include <iostream>
#include <stdlib.h>
#include <math.h>

struct Xn {
    int n;
    float ideal;
    double* accurance;
    double* ksum;
};

double Factorial(int num) {
    if (num == 0 || num == 1) return 1;
    else return num * Factorial(num - 1);
}

void Sin(Xn* series, int count, double x, double ideal) {
    for (int i = 1; i < count; i++) {
        series->ksum[i] = series->ksum[i - 1] + pow(-1, i) * (pow(x, 2 * i + 1) / Factorial(2 * i + 1));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
    }
}

void SinR(Xn* series, int count, double x, double ideal) {
    for (int i = count - 1; i >= 0; i--) {
        series->ksum[i] = series->ksum[i + 1] + pow(-1, i) * (pow(x, 2 * i + 1) / Factorial(2 * i + 1));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
    }
}

void Cos(Xn* series, int count, double x, double ideal) {
    for (int i = 1; i < count; i++) {
        series->ksum[i] = series->ksum[i - 1] + pow(-1, i) * (pow(x, 2 * i) / Factorial(2 * i));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
    }
}

void CosR(Xn* series, int count, double x, double ideal) {
    for (int i = count - 1; i >= 0; i--) {
        series->ksum[i] = series->ksum[i + 1] + pow(-1, i) * (pow(x, 2 * i) / Factorial(2 * i));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
    }
}

void Exp(Xn* series, int count, double x, double ideal) {
    for (int i = 1; i < count; i++) {
        series->ksum[i] = series->ksum[i - 1] + (pow(x, i) / Factorial(i));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
    }
}

void ExpR(Xn* series, int count, double x, double ideal) {
    for (int i = count - 1; i >= 0; i--) {
        series->ksum[i] = series->ksum[i + 1] + (pow(x, i) / Factorial(i));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
    }
}

void Ln(Xn* series, int count, double x, double ideal) {
   for (int i = 1; i < count; i++) {
        series->ksum[i] = series->ksum[i - 1] + pow(-1, i) * (pow(x, i + 1) / (i + 1));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
   }
}

void LnR(Xn* series, int count, double x, double ideal) {
    for (int i = count - 1; i >= 0; i--) {
        series->ksum[i] = series->ksum[i + 1] + pow(-1, i) * (pow(x, i + 1) / (i + 1));
        series->accurance[i] = fabs(series->ksum[i] - ideal);
    }
}

void Print(Xn* series, int count) {
    for (int i = 0; i < count; i++) {
        printf("Sum: %lf  Err: %lf\n", series->ksum[i], series->accurance[i]);
    }
    printf("\n");
}

void PrintR(Xn* series, int count) {
    for (int i = count - 1; i >= 0; i--) {
        printf("Sum: %lf  Err: %lf\n", series->ksum[i], series->accurance[i]);
    }
    printf("\n");
}

void Init(Xn* series, int count) {
    series->accurance = (double*)malloc(sizeof(double) * count);
    series->ksum = (double*)malloc(sizeof(double) * count);
}

void UnInit(Xn* series) {
    free(series->accurance);
    free(series->ksum);
    series->accurance = NULL;
    series->ksum = NULL;
}

void InitStation(Xn* series, double ideal, double x0, int count) {
    series->n = count;
    series->ideal = ideal;
    series->ksum[0] = x0;
    series->accurance[0] = series->ideal - x0;
}

void InitStationR(Xn* series, double ideal, double x0, int count) {
    series->n = count;
    series->ideal = ideal;
    series->ksum[count - 1] = x0;
    series->accurance[count - 1] = series->ideal - x0;
}

void Test(Xn* series, void(*func)(Xn*, int, double, double), double ideal, double x, double x0, int count, bool isReversed) {
    Init(series, count);
    if (isReversed) InitStationR(series, ideal, x0, count);
    else InitStation(series, ideal, x0, count);
    func(series, count, x, ideal);
    if (isReversed) PrintR(series, count);
    else Print(series, count);
    UnInit(series);
}

int main()
{
    struct Xn sinXn {}, cosXn{}, logXn{}, expXn{}, sinXnR{}, cosXnR{}, logXnR{}, expXnR{};
    
    int count = 20;

    double x = (rand()/RAND_MAX) * 0.5 + 0.5;
    printf("%lf\n", x);
    double idealSin = sin(x), idealCos = cos(x), idealExp = exp(x), idealLn = log(x+1);

    Test(&sinXn, Sin, idealSin, x, x, count, false);
    Test(&sinXnR, SinR, idealSin, x, pow(-1, count - 1) * (pow(x, 2 * (count - 1) + 1) / Factorial(2 * (count - 1) + 1)), count, true);
    Test(&cosXn, Cos, idealCos, x, 1, count, false);
    Test(&cosXnR, CosR, idealCos, x, pow(-1, count - 1) * (pow(x, 2 * (count - 1)) / Factorial(2 * (count - 1))), count, true);
    Test(&logXn, Ln, idealLn, x, x, count, false);
    Test(&logXnR, LnR, idealLn, x, pow(-1, count - 1)* (pow(x, count - 1 + 1) / (count - 1 + 1)), count, true);
    Test(&expXn, Exp, idealExp, x, 1, count, false);
    Test(&expXnR, ExpR, idealExp, x, (pow(x, count - 1) / Factorial((count - 1))), count, true);
}
