#include <math.h>
#include <iostream>
#include "Header.h"
#include <iomanip>

int main()
{
    double Xn[10];
    double (*MaclaurinXn)(int, double);
    void (*Type_sum)(double*, int);
    double (*standardFn)(double);
    double standard;

    std::cout << "1)Sin 2)Cos 3)Exp 4)Log\n";
    int w;
    std::cin >> w;
    switch(w) {
    case 1:MaclaurinXn = Sin; standardFn = sin; break;
    case 2:MaclaurinXn = Cos; standardFn = cos; break;
    case 3:MaclaurinXn = Exp; standardFn = exp; break;
    default:MaclaurinXn = Log; standardFn = log; break;
    }
    std::cout << "1)direct 2)reverse\n";
    std::cin >> w;
    switch (w) {
    case 1:Type_sum = direct_sum; break;
    default:Type_sum = reverse_sum; break;
    }
    std::cout << "x = ";
    double r;
    std::cin >> r;

    std::cout << std::fixed << std::setprecision(16);   
    
    for (int i = 0; i < 10;i++) { Xn[i] = MaclaurinXn(i,r); }

    Type_sum(Xn, 10);

    standard = standardFn(r);
    std::cout << "standard = " << standard;
    
}
    
