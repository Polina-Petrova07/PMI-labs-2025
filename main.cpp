#include "stdio.h"
#include "math.h"
#include "function.cpp"
#include "locale.h"

struct Values
{
    double val_x_in_t;
    int val_count;
};


int main()
{
    setlocale(LC_ALL,"rus");
    struct Values  test;
    struct Values *p_test = &test; 
    const int count_string_teilor_test[10] = {2,3,4,5,6,7,8,9,10,100000000};
    int choise_func;
    double rez_val;

    wprintf(L"---------------\nВыберите функцию для работы:\n1. sin(x)\n2. cos(x)\n3. exp(x)\n4. ln(1+x)\n5. Завершить работу\n---------------\n");
    scanf("%i", &choise_func);
    while (choise_func != 5)
    {
      

        switch (choise_func)
        {
        case (1): //sin(x) 
            wprintf(L"Введите желаемое значение x:\n");
            scanf("%lg",&test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",sin(test.val_x_in_t),test.val_count);
            rez_val = teilor_sin(test.val_x_in_t,test.val_count); // значение при 2 строчках
            wprintf(L"Значение синуса из библиотеки: %lg, полученное значение: %lg\n",sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[1];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",test.val_x_in_t,test.val_count);
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);   //  значение при 3 строчках 
            wprintf(L"Значение синуса из библиотеки: %lg, полученное значение: %lg\n",sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[2];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",sin(test.val_x_in_t),test.val_count);
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);    // значение при 4 строчках
            wprintf(L"Значение синуса из библиотеки: %lg, полученное значение: %lg\n",sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[3];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",sin(test.val_x_in_t),test.val_count);
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);    // значение при 5 строчках
            wprintf(L"Значение синуса из библиотеки: %lg, полученное значение: %lg\n",sin(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[4];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",sin(test.val_x_in_t),test.val_count);
            rez_val = teilor_sin(test.val_x_in_t,test.val_count);    // значение при 6 строчках
            wprintf(L"Значение синуса из библиотеки: %lg, полученное значение: %lg\n",sin(test.val_x_in_t),rez_val);

            break;
            
        case(2): // cos(x)
            wprintf(L"Введите желаемое значение x:\n");
            scanf("%lg", &test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",cos(test.val_x_in_t),test.val_count);
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            wprintf(L"Значение косинуса из библиотеки: %lg, полученное значение: %lg\n",cos(test.val_x_in_t),rez_val);
            p_test -> val_count = count_string_teilor_test[1];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",cos(test.val_x_in_t),test.val_count);
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            wprintf(L"Значение косинуса из библиотеки: %lg, полученное значение: %lg\n",cos(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[2];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",cos(test.val_x_in_t),test.val_count);
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            wprintf(L"Значение косинуса из библиотеки: %lg, полученное значение: %lg\n",cos(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[3];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",cos(test.val_x_in_t),test.val_count);
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            wprintf(L"Значение косинуса из библиотеки: %lg, полученное значение: %lg\n",cos(test.val_x_in_t),rez_val);
            p_test -> val_count = count_string_teilor_test[4];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",cos(test.val_x_in_t),test.val_count);
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            wprintf(L"Значение косинуса из библиотеки: %lg, полученное значение: %lg\n",cos(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[5];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",cos(test.val_x_in_t),test.val_count);
            rez_val = teilor_cos(test.val_x_in_t,test.val_count);
            wprintf(L"Значение косинуса из библиотеки: %lg, полученное значение: %lg\n",cos(test.val_x_in_t),rez_val);
            break;

        case(3): // exp(x)
            wprintf(L"Введите желаемое значение x:\n");
            scanf("%lg", &test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",exp(test.val_x_in_t),test.val_count);
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            wprintf(L"Значение экспоненты в степени из библиотеки: %lg, полученное значение: %lg\n",exp(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[1];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",exp(test.val_x_in_t),test.val_count);
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            wprintf(L"Значение экспоненты в степени из библиотеки: %lg, полученное значение: %lg\n",exp(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[2];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",exp(test.val_x_in_t),test.val_count);
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            wprintf(L"Значение экспоненты в степени из библиотеки: %lg, полученное значение: %lg\n",exp(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[3];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",exp(test.val_x_in_t),test.val_count);
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            wprintf(L"Значение экспоненты в степени из библиотеки: %lg, полученное значение: %lg\n",exp(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[4];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",exp(test.val_x_in_t),test.val_count);
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            wprintf(L"Значение экспоненты в степени из библиотеки: %lg, полученное значение: %lg\n",exp(test.val_x_in_t),rez_val);

            p_test -> val_count = count_string_teilor_test[8];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",exp(test.val_x_in_t),test.val_count);
            rez_val = teilor_exp(test.val_x_in_t,test.val_count);
            wprintf(L"Значение экспоненты в степени из библиотеки: %lg, полученное значение: %lg\n",exp(test.val_x_in_t),rez_val);
            
            break;
        case(4): // ln(1+x)
            wprintf(L"Введите желаемое значение x:\n");
            scanf("%lg", &test.val_x_in_t);

            p_test -> val_count = count_string_teilor_test[0];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",log(test.val_x_in_t+1),test.val_count);
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            wprintf(L"Значение логарифма из библиотеки: %lg, полученное значение: %lg\n",log(test.val_x_in_t+1),rez_val);

            p_test -> val_count = count_string_teilor_test[1];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",log(test.val_x_in_t+1),test.val_count);
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            wprintf(L"Значение логарифма из библиотеки: %lg, полученное значение: %lg\n",log(test.val_x_in_t+1),rez_val);

            p_test -> val_count = count_string_teilor_test[8];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",log(test.val_x_in_t+1),test.val_count);
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            wprintf(L"Значение логарифма из библиотеки: %lg, полученное значение: %lg\n",log(test.val_x_in_t+1),rez_val);

            p_test -> val_count = count_string_teilor_test[9];
            wprintf(L"Сравниваем значение: %lg, при количество строк: %i\n",log(test.val_x_in_t+1),test.val_count);
            rez_val = teilor_ln(test.val_x_in_t,test.val_count);
            wprintf(L"Значение логарифма из библиотеки: %lg, полученное значение: %lg\n",log(test.val_x_in_t+1),rez_val);



            break;
        }
        wprintf(L"---------------\nВыберите функцию для работы:\n1. sin(x)\n2. cos(x)\n3. exp(x)\n4. ln(1+x)\n5. Завершить работу\n---------------\n");
        scanf("%i", &choise_func);
    }   
}