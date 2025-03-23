#include "function.h"

int factorial( int n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

double teilor_sin(double x, int count_string) 
{
    int k = 0;
    double s=0.0;
    while (k<count_string)
    {
        double c = (pow(-1,k) * pow(x,2*k+1));
        int b = factorial(2*k+1);
        double m = c/b;
        s+=m;
        k++;
    }
    return s;
}

double teilor_cos(double x, int count_string)
{
    int k = 0;
    double s=0.0;
    while (k<count_string)
    {
        double c = (pow(-1,k) * pow(x,2*k));
        int b = factorial(2*k);
        double m = c/b;
        s+=m;
        k++;
    }
    return s;

}

double teilor_exp (double x, int count_string)
{
    int k = 0;
    double s=0.0;
    while (k<count_string)
    {
        double c = pow(x,k);
        int b = factorial(k);
        double m = c/b;
        s+=m;
        k++;
    }
    return s;
}

double teilor_ln (double x, int count_string)
{
    int k = 0;
    double s=0.0;
    while (k<count_string)
    {
        double c = pow(-1,k)* pow(x,(k+1));
        int b = k+1;
        double m = c/b;
        s+=m;
        k++;
    }
    return s;
}