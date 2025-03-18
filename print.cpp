#include "print.h"


void print_menu_func()
{
    setlocale(LC_ALL,"rus");
    wprintf(L"---------------\nВыберите функцию для работы:\n1. sin(x)\n2. cos(x)\n3. exp(x)\n4. ln(1+x)\n5. Завершить работу\n---------------\n");
}

void print_required_val()
{
    wprintf(L"Введите желаемое значение x:\n");
}

void print_test_teilor(int count, double value)
{
    wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",value,count);
}

void print_rez_val_sin(double value_sin, double rez_val)
{
    wprintf(L"Значение синуса из библиотеки: %lg, полученное значение: %lg\n",value_sin,rez_val);
}

void print_rez_val_cos(double value_cos, double rez_val)
{
    wprintf(L"Значение косинуса из библиотеки: %lg, полученное значение: %lg\n",value_cos,rez_val);
}

void print_rez_val_exp(double value_exp, double rez_val)
{
    wprintf(L"Значение экспоненты в степени из библиотеки: %lg, полученное значение: %lg\n",value_exp,rez_val);
}

void print_rez_val_ln(double value_ln, double rez_val)
{
    wprintf(L"Значение логарифма из библиотеки: %lg, полученное значение: %lg\n",value_ln,rez_val);
}
    
