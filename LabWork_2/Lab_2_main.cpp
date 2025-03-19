#include "Lab_2.h"
int main() {
    struct Xn array;
    int choice;
    double x;
    int count;
    while (true) {
        printf("Какую функцию вы хотите вычислить?\n1.Синус\n2.Косинус\n3.Экспанента\n4.Натуральный логарифм\n5.Выход из программы\n");
        scanf("%d", &choice);
        if((choice<1)||(choice>5)){
            printf("Функция выбрана неверно\n");
            break;
        }
        if(choice==5){
            printf("Выполнен выход из программы\n");
            break;
        }
        printf("Введите x (В случае натурального логорифма: |x|<1):\n");
        scanf("%lf", &x);
        if ((choice==4)&&(fabs(x)>=1)){
            printf("Ряд не определен при |x|>=1\n\n");
            continue;
        }
        printf("Введите количество итераций: ");
        scanf("%d", &count);
        if (count < 1) {
            printf("Количество итераций должно быть определенно натуральным числом\n\n");
            continue;
        }
        array.x = x;
        create_array(&array, count + 1);
        switch (choice) {
        case 1:
            printf("Синус (прямой порядок):\n");
            sinXn(array.count, array.x, array.err, array.sum);
            printf("Синус (обратный порядок):\n");
            sinXnRev(array.count, array.x, array.err, array.sum);
            break;
        case 2:
            printf("Косинус (прямой порядок):\n");
            cosXn(array.count, array.x, array.err, array.sum);
            printf("Косинус (обратный порядок):\n");
            cosXnRev(array.count, array.x, array.err, array.sum);
            break;
        case 3:
            printf("Экспонента (прямой порядок):\n");
            expXn(array.count, array.x, array.err, array.sum);
            printf("Экспонента (обратный порядок):\n");
            expXnRev(array.count, array.x, array.err, array.sum);
            break;
        case 4:
            printf("Натуральный логарифм (прямой порядок):\n");
            lnXn(array.count, array.x, array.err, array.sum);
            printf("Натуральный логарифм (обратный порядок):\n");
            lnXnRev(array.count, array.x, array.err, array.sum);
            break;
        default:
            break;
        }
        free_array(&array);
    }

    return 0;
}
