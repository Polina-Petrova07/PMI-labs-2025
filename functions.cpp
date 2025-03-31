
#include "Functions.h"

int factorial(int n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}


double sin_teilor_pr(double value_x, int len_teilor)
{
    int k = 0;
    double s = 0.0;
    while (k < len_teilor)
    {
        double c = (pow(-1, k) * pow(value_x, 2 * k + 1));
        int b = factorial(2 * k + 1);
        double m = c / b;
        s += m;
        k++;
    }
    return s;
}

double sin_teilor_obr(double value_x, int len_teilor)
{
    int k = len_teilor;
    double s = 0.0;
    while (k >= 0)
    {
        double c = (pow(-1, k) * pow(value_x, 2 * k + 1));
        int b = factorial(2 * k + 1);
        double m = c / b;
        s += m;
        k--;
    }
    return s;
	
}

double cos_teilor_pr(double value_x, int len_teilor)
{
    int k = 0;
    double s = 0.0;
    while (k < len_teilor)
    {
        double c = (pow(-1, k) * pow(value_x, 2 * k));
        int b = factorial(2 * k);
        double m = c / b;
        s += m;
        k++;
    }
    return s;
}

double cos_teilor_obr(double value_x, int len_teilor)
{
    int k = len_teilor;
    double s = 0.0;
    while (k >=0)
    {
        double c = (pow(-1, k) * pow(value_x, 2 * k));
        int b = factorial(2 * k);
        double m = c / b;
        s += m;
        k--;
    }
    return s;
}

double exp_teilor_pr(double value_x, int len_teilor)
{
    int k = 0;
    double s = 0.0;
    while (k < len_teilor)
    {
        double c = pow(value_x, k);
        int b = factorial(k);
        double m = c / b;
        s += m;
        k++;
    }
    return s;

}

double exp_teilor_obr(double value_x, int len_teilor)
{
    int k = len_teilor;
    double s = 0.0;
    while (k >=0)
    {
        double c = pow(value_x, k);
        int b = factorial(k);
        double m = c / b;
        s += m;
        k--;
    }
    return s;
}

double log_teilor_pr(double value_x, int len_teilor)
{
    int k = 0;
    double s = 0.0;
    while (k < len_teilor)
    {
        double c = pow(-1, k) * pow(value_x, (k + 1));
        int b = k + 1;
        double m = c / b;
        s += m;
        k++;
    }
    return s;
}

double log_teilor_obr(double value_x, int len_teilor)
{
    int k = len_teilor;
    double s = 0.0;
    while (k >=0)
    {
        double c = pow(-1, k) * pow(value_x, (k + 1));
        int b = k + 1;
        double m = c / b;
        s += m;
        k--;
    }
    return s;
}