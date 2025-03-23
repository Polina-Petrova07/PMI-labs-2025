#include "header.h"
void locat(void) {
    char* locale = setlocale(LC_ALL, "");
}
void vvod(void) {
    printf("Выберите функцию:\n1.sin(x)\n2.обратный sin(x)\n3.cos(x)\n4.обратный cos(x)\n5.exp(x)\n6.обратная exp(x)\n7.ln(1+x)\n8.обратный ln(1+x)\n");
}
double point(void) {
    return ((double)(rand())) / RAND_MAX * 0.5 + 0.5;
}
struct x_n init(x_n a, int n) {
    a.x = (double*)malloc(sizeof(double) * n);
    a.sum = (double*)malloc(sizeof(double) * n);
    a.err = (double*)malloc(sizeof(double) * n);
    return a;
}
void free_x(x_n a) {
    free(a.x);
    free(a.err);
    free(a.sum);
}
void copymas(double masa[], double masb[], int n) {
    for (int i = 0; i < n; i++)
        masa[i] = masb[i];
}
struct x_n sinx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = x;
    for (int i = 0; i < a.n - 1; i++) {
        mas[i + 1] = ((-1) * x * x * mas[i]) / ((2 * i + 3) * (2 * i + 2));
    }
    copymas(a.x, mas, n);
    for (int i = 1; i < a.n; i++) {
        mas[i] = mas[i - 1] + mas[i];
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(sin(x) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
struct x_n resinx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = x;
    for (int i = 0; i < a.n - 1; i++) {
        mas[i + 1] = ((-1) * x * x * mas[i]) / ((2 * i + 3) * (2 * i + 2));
    }
    copymas(a.x, mas, n);
    for (int i = a.n-1; i>=0; i--) {
        for (int j=i-1;j>=0;j--){
            mas[i] += mas[j];
        }
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(sin(x) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
struct x_n cosx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = 1;
    for (int i = 0; i < a.n - 1; i++) {
        mas[i + 1] = ((-1) * x * x * mas[i]) / ((2 * i + 1) * (2 * i + 2));
    }
    copymas(a.x, mas, n);
    for (int i = 1; i < a.n; i++) {
        mas[i] = mas[i - 1] + mas[i];
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(cos(x) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
struct x_n recosx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = 1;
    for (int i = 0; i < a.n - 1; i++) {
        mas[i + 1] = ((-1) * x * x * mas[i]) / ((2 * i + 1) * (2 * i + 2));
    }
    copymas(a.x, mas, n);
    for (int i = a.n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            mas[i] += mas[j];
        }
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(cos(x) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
struct x_n expx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = 1;
    for (int i = 0; i < a.n - 1; i++) {
        mas[i + 1] = (x * mas[i]) / (i + 1);
    }
    copymas(a.x, mas, n);
    for (int i = 1; i < a.n; i++) {
        mas[i] = mas[i - 1] + mas[i];
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(exp(x) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
struct x_n reexpx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = 1;
    for (int i = 1; i < a.n; i++) {
        mas[i] = (x * mas[i - 1]) / i;
    }
    copymas(a.x, mas, n);
    for (int i = a.n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            mas[i] += mas[j];
        }
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(exp(x) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
struct x_n lnx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = x;
    for (int i = 0; i < a.n - 1; i++) {
        mas[i + 1] = ((-1.0) * x * mas[i] * (i + 1)) / (i + 2);
    }
    copymas(a.x, mas, n);
    for (int i = 1; i < a.n; i++) {
        mas[i] = mas[i - 1] + mas[i];
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(log(x + 1) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
struct x_n relnx(int n, double x) {
    struct x_n a;
    a = init(a, n);
    a.n = n;
    double* mas = (double*)malloc(sizeof(double) * n);
    mas[0] = x;
    for (int i = 0; i < a.n - 1; i++) {
        mas[i + 1] = ((-1) * x * mas[i] * (i + 1)) / (i + 2);
    }
    copymas(a.x, mas, n);
    for (int i = a.n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            mas[i] += mas[j];
        }
    }
    copymas(a.sum, mas, n);
    for (int i = 0; i < a.n; i++)
        mas[i] = fabs(log(x + 1) - a.sum[i]);
    copymas(a.err, mas, n);
    free(mas);
    return a;
    free_x(a);
}
void tablichka(char choice) {
    int n = 20;
    double x = point();
    struct x_n(*func) (int, double);
    switch (choice) {
    case '1': {
        func = sinx;
        printf("x = %lf\tsin(x) = %lf\n", x,sin(x));
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i - 1]);
        free_x(line);
        break;
    }
    case '2': {
        printf("x = %lf\tsin(x) = %lf\n", x, sin(x));
        func = resinx;
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i - 1]);
        free_x(line);
        break;
    }
    case '3': {
        printf("x = %lf\tcos(x) = %lf\n", x, cos(x));
        func = cosx;
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i-1]);
        free_x(line);
        break;
    }
    case '4': {
        printf("x = %lf\tcos(x) = %lf\n", x, cos(x));
        func = recosx;
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i-1]);
        free_x(line);
        break;
    }
    case '5': {
        printf("x = %lf\texp(x) = %lf\n", x, exp(x));
        func = expx;
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i-1]);
        free_x(line);
        break;
    }
    case '6': {
        printf("x = %lf\texp(x) = %lf\n", x, exp(x));
        func = reexpx;
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i - 1]);
        free_x(line);
        break;
    }
    case '7': {
        printf("x = %lf\tln(1+x) = %lf\n", x, log(x));
        func = lnx;
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i-1]);
        free_x(line);
        break;
    }
    case '8': {
        printf("x = %lf\tln(1+x) = %lf\n", x, log(x));
        func = relnx;
        x_n line = func(n, x);
        for (int i = 1; i < n + 1; i++)
            printf("%i %.35lf\n", i, line.err[i-1]);
        free_x(line);
        break;
    }
    default: {
        printf("Ошибка. Повторите попытку.\n");
        break;
    }
    }
}