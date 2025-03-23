#include <math.h>
#include<stdio.h>
#include<stdlib.h>

struct Xn
{

    int n;
    double* err;
    double* sum;
};

double fact(int num) {
    if (num == 0 || num == 1) return 1;
    else return num * fact(num - 1);
}
void Msin(Xn* xn,   double x, double ideal)
{
    for (int i = 1; i < xn->n; i++) 
    {
        xn->sum[i] = xn->sum[i - 1] + pow(-1, i) * (pow(x, 2 * i + 1) / fact(2 * i + 1));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}
void MsinR(Xn* xn,   double x, double ideal)
{
    for (int i = xn->n - 1; i >= 0; i--)
    {
        xn->sum[i] = xn->sum[i + 1] + pow(-1, i) * (pow(x, 2 * i + 1) / fact(2 * i + 1));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}
void Mcos(Xn* xn,   double x, double ideal)
{
    for (int i = 1; i < xn->n; i++)
    {
        xn->sum[i] = xn->sum[i - 1] + pow(-1, i) * (pow(x, 2 * i) / fact(2 * i));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}
void McosR(Xn* xn,   double x, double ideal)
{
    for (int i = xn->n - 1; i >= 0; i--)
    {
        xn->sum[i] = xn->sum[i + 1] + pow(-1, i) * (pow(x, 2 * i) / fact(2 * i));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}
void Mexp(Xn* xn,  double x, double ideal)
{
    for (int i = 1; i < xn->n; i++) 
    {
        xn->sum[i] = xn->sum[i - 1] + (pow(x, i) / fact(i));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}

void MexpR(Xn* xn, double x, double ideal)
{
    for (int i = xn->n - 1; i >= 0; i--)
    {
        xn->sum[i] = xn->sum[i + 1] + (pow(x, i) / fact(i));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}
void Mln(Xn* xn , double x, double ideal) 
{
    x = x - 1;
    for (int i = 1; i < xn->n; i++) 
    {
        xn->sum[i] = xn->sum[i - 1] + pow(-1, i) * (pow(x, i + 1) / (i + 1));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}

void MlnR(Xn* xn , double x, double ideal) 
{
    x = x - 1;
    for (int i = xn->n - 1; i >= 0; i--) 
    {
        xn->sum[i] = xn->sum[i + 1] + pow(-1, i) * (pow(x, i + 1) / (i + 1));
        xn->err[i] = fabs(xn->sum[i] - ideal);
    }
}
void print(Xn* xn ) 
{
    for (int i = 0; i < xn->n; i++) 
    {
        printf("sum %lf  err %lf\n", xn->sum[i], xn->err[i]);
    }
    printf("\n");
}

void printR(Xn* xn ) 
{
    for (int i = xn->n - 1; i >= 0; i--) 
    {
        printf("sum %lf  err %lf\n", xn->sum[i], xn->err[i]);
    }
    printf("\n");
}
void Free(Xn* xn) 
{
    free(xn->err);
    free(xn->sum);
    xn->err = NULL;
    xn->sum = NULL;
}
void init(Xn* xn, double ideal, double x0, int count) 
{
    xn->n = count;
    xn->err = (double*)malloc(sizeof(double) * count);
    xn->sum = (double*)malloc(sizeof(double) * count);
    xn->sum[0] = x0;
    xn->err[0] = ideal - x0;
}

void initR(Xn* xn, double ideal, double x0, int count) 
{
    xn->n = count;

    xn->err = (double*)malloc(sizeof(double) * count);
    xn->sum = (double*)malloc(sizeof(double) * count);
    xn->sum[count - 1] = x0;
    xn->err[count - 1] = ideal - x0;
}

void Main(void(*func)(Xn*, double, double), double (*ideal)(double), double num, double x0, int count, bool isReversed)
{
    struct Xn xn;
    if (isReversed) 
    {
        initR(&xn, ideal(num), x0, count); 
    }
    else
    {
        init(&xn, ideal(num), x0, count);
    }
    func(&xn, num, ideal(num));
    if (isReversed)
    {
        printR(&xn);
    }
    else
    {
        print(&xn);
    }
    Free(&xn);
}
int main()
{

    int count = 10;

    double x = (rand() / RAND_MAX) * 0.5 + 0.5;
    printf("%f\n", x);

    Main( Msin, sin, x, x, count, false);
    Main(MsinR, sin, x, pow(-1, count - 1) * (pow(x, 2 * (count - 1) + 1) / fact(2 * (count - 1) + 1)), count, true);
    Main( Mcos, cos, x, 1, count, false);
    Main( McosR, cos, x, pow(-1, count - 1) * (pow(x, 2 * (count - 1)) / fact(2 * (count - 1))), count, true);
    Main( Mln, log, x+1, x, count, false);
    Main(MlnR, log, x+1, pow(-1, count - 1) * (pow(x, count - 1 + 1) / (count - 1 + 1)), count, true);
    Main( Mexp, exp, x, 1, count, false);
    Main( MexpR, exp, x, (pow(x, count - 1) / fact((count - 1))), count, true);
}