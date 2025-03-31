
#include "Functions.h"

struct Values
{
    double x;
    int len;
};

int main()
{
    setlocale(LC_ALL, "rus"); 
    struct Values object;
    struct Values *value = &object;
    struct Values* len = &object;
    
    int function;
    double rez_teilor;
    double value_x = 0;
    int len_teilor = 0;
    


    printf("---------------\nВыберите функцию для работы:\n1. sin(x)\n2. cos(x)\n3. exp(x)\n4. ln(1+x)\n5. Завершить работу\n---------------\n");
    scanf_s("%i", &function);
    while (function != 5)
    {
        switch (function)
        {
        case 1: 
            printf("Введите число x: \n");
            value -> x = value_x;
            scanf_s("%lf", &value_x);

            len->len = len_teilor;
            printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
            scanf_s("%i", &len_teilor);
            while (len_teilor > 0)
            {
                rez_teilor = sin_teilor_pr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение синуса через ряд тейлора: %lf, с использованием %i строк, используя прямой порядок сложения\n", sin(value_x), rez_teilor, len_teilor);

                rez_teilor = sin_teilor_obr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение синуса через ряд тейлора: %lf, с использованием %i строк, используя обратный порядок сложения\n", sin(value_x), rez_teilor, len_teilor);

                printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
                scanf_s("%i", &len_teilor);
            }
            break;
        case 2:
            printf("Введите число x: \n");
            value->x = value_x;
            scanf_s("%lf", &value_x);

            len->len = len_teilor;
            printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
            scanf_s("%i", &len_teilor);
            while (len_teilor > 0)
            {
                rez_teilor = cos_teilor_pr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение косинуса через ряд тейлора: %lf, с использованием %i строк, используя прямой порядок сложения\n", cos(value_x), rez_teilor, len_teilor);

                rez_teilor = cos_teilor_obr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение косинуса через ряд тейлора: %lf, с использованием %i строк, используя обратный порядок сложения\n", cos(value_x), rez_teilor, len_teilor);

                printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
                scanf_s("%i", &len_teilor);
            }
            break;
        case 3:
            printf("Введите число x: \n");
            value->x = value_x;
            scanf_s("%lf", &value_x);

            len->len = len_teilor;
            printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
            scanf_s("%i", &len_teilor);
            while (len_teilor > 0)
            {
                rez_teilor = exp_teilor_pr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение e^x через ряд тейлора: %lf, с использованием %i строк, используя прямой порядок сложения\n", exp(value_x), rez_teilor, len_teilor);

                rez_teilor = exp_teilor_obr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение e^x через ряд тейлора: %lf, с использованием %i строк, используя обратный порядок сложения\n", exp(value_x), rez_teilor, len_teilor);

                printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
                scanf_s("%i", &len_teilor);
            }
            break;
        case 4:
            printf("Введите число x: \n");
            value->x = value_x;
            scanf_s("%lf", &value_x);

            len->len = len_teilor;
            printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
            scanf_s("%i", &len_teilor);
            while (len_teilor > 0)
            {
                rez_teilor = log_teilor_pr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение log(x+1) через ряд тейлора: %lf, с использованием %i строк, используя прямой порядок сложения\n", log(value_x+1), rez_teilor, len_teilor);

                rez_teilor = log_teilor_obr(value_x, len_teilor);
                printf("Требуемое значение: %lf, значение log(x+1) через ряд тейлора: %lf, с использованием %i строк, используя обратный порядок сложения\n", log(value_x+1), rez_teilor, len_teilor);

                printf("Введите количество членов в ряде Тейлора, для выхода введите отрицательное значение: \n");
                scanf_s("%i", &len_teilor);
            }
            break;

        default:
            printf("Ошибка в введеных значениях\n");
            break;
        }
        printf("---------------\nВыберите функцию для работы:\n1. sin(x)\n2. cos(x)\n3. exp(x)\n4. ln(1+x)\n5. Завершить работу\n---------------\n");
        scanf_s("%i", &function);
    }
    
}
    
