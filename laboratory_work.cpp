#include "laboratory_work.h"

int main() {
    setlocale(LC_ALL, "Rus");
    struct xn array;
    int choice;
    double x;
    int count;

    while (true) {
        printf("Какую функцию вы хотите вычислить?\n");
        printf("1. Синус\n");
        printf("2. Косинус\n");
        printf("3. Экспонента\n");
        printf("4. Натуральный логарифм\n");
        printf("5. Выход\n");
        printf("Введите ваш выбор: ");
        scanf_s("%d", &choice);

        if (choice == 5) {
            break;
        }

        printf("Введите x от 0,5 до 1: ");
        scanf_s("%lf", &x);
        printf("Введите количество итераций: ");
        scanf_s("%d", &count);

        if (count <= 0) {
            printf("Ошибка: количество итераций должно быть больше нуля.\n");
            continue;
        }

        array.x = x;
        createarr(&array, count + 1);

        switch (choice) {
        case 1:
            printf("Синус (прямой порядок):\n");
            sinXn(array.count, array.x, array.err, array.sum);
            printf("Синус (обратный порядок):\n");
            sinXnRE(array.count, array.x, array.err, array.sum);
            break;
        case 2:
            printf("Косинус (прямой порядок):\n");
            cosXn(array.count, array.x, array.err, array.sum);
            printf("Косинус (обратный порядок):\n");
            cosXnRE(array.count, array.x, array.err, array.sum);
            break;
        case 3:
            printf("Экспонента (прямой порядок):\n");
            expXn(array.count, array.x, array.err, array.sum);
            printf("Экспонента (обратный порядок):\n");
            expXnRE(array.count, array.x, array.err, array.sum);
            break;
        case 4:
            printf("Натуральный логарифм (прямой порядок):\n");
            lnXn(array.count, array.x, array.err, array.sum);
            printf("Натуральный логарифм (обратный порядок):\n");
            lnXnRE(array.count, array.x, array.err, array.sum);
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            break;
        }

        freearr(&array);
    }

    return 0;
}