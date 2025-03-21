#include "header.h"

// Вычисление факториала
unsigned long long computeFactorial(int n) {
    return (n <= 1) ? 1 : n * computeFactorial(n - 1);
}

// Инициализация структуры Series
void initializeSeries(Series* series, int terms) {
    series->numTerms = terms;
    series->sums = (double*)malloc(terms * sizeof(double));
    series->errors = (double*)malloc(terms * sizeof(double));
    for (int i = 0; i < terms; i++) {
        series->sums[i] = 0.0;
        series->errors[i] = 0.0;
    }
}

// Освобождение памяти
void cleanupSeries(Series* series) {
    free(series->sums);
    free(series->errors);
    series->sums = NULL;
    series->errors = NULL;
    series->numTerms = 0;
}

// Вычисление синуса (прямой порядок)
void calculateSineSeries(Series* series) {
    double x = series->input;
    series->sums[0] = x;
    series->errors[0] = fabs(series->sums[0] - sin(x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + pow(-1, i) * (pow(x, 2 * i + 1) / computeFactorial(2 * i + 1));
        series->errors[i] = fabs(series->sums[i] - sin(x));
    }
}

// Вычисление синуса (обратный порядок)
void calculateSineSeriesReverse(Series* series) {
    double x = series->input;
    int last = series->numTerms - 1;
    series->sums[last] = pow(-1, last) * (pow(x, 2 * last + 1) / computeFactorial(2 * last + 1));
    series->errors[last] = fabs(series->sums[last] - sin(x));
    for (int i = last - 1; i >= 0; i--) {
        series->sums[i] = series->sums[i + 1] + pow(-1, i) * (pow(x, 2 * i + 1) / computeFactorial(2 * i + 1));
        series->errors[i] = fabs(series->sums[i] - sin(x));
    }
}

// Вычисление косинуса (прямой порядок)
void calculateCosineSeries(Series* series) {
    double x = series->input;
    series->sums[0] = 1.0;
    series->errors[0] = fabs(series->sums[0] - cos(x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + pow(-1, i) * (pow(x, 2 * i) / computeFactorial(2 * i));
        series->errors[i] = fabs(series->sums[i] - cos(x));
    }
}

// Вычисление косинуса (обратный порядок)
void calculateCosineSeriesReverse(Series* series) {
    double x = series->input;
    int last = series->numTerms - 1;
    series->sums[last] = pow(-1, last) * (pow(x, 2 * last) / computeFactorial(2 * last));
    series->errors[last] = fabs(series->sums[last] - cos(x));
    for (int i = last - 1; i >= 0; i--) {
        series->sums[i] = series->sums[i + 1] + pow(-1, i) * (pow(x, 2 * i) / computeFactorial(2 * i));
        series->errors[i] = fabs(series->sums[i] - cos(x));
    }
}

// Вычисление экспоненты (прямой порядок)
void calculateExponentialSeries(Series* series) {
    double x = series->input;
    series->sums[0] = 1.0;
    series->errors[0] = fabs(series->sums[0] - exp(x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + (pow(x, i) / computeFactorial(i));
        series->errors[i] = fabs(series->sums[i] - exp(x));
    }
}

// Вычисление экспоненты (обратный порядок)
void calculateExponentialSeriesReverse(Series* series) {
    double x = series->input;
    int last = series->numTerms - 1;
    series->sums[last] = pow(x, last) / computeFactorial(last);
    series->errors[last] = fabs(series->sums[last] - exp(x));
    for (int i = last - 1; i >= 0; i--) {
        series->sums[i] = series->sums[i + 1] + (pow(x, i) / computeFactorial(i));
        series->errors[i] = fabs(series->sums[i] - exp(x));
    }
}

// Вычисление натурального логарифма (прямой порядок)
void calculateLogarithmSeries(Series* series) {
    double x = series->input;
    series->sums[0] = x;
    series->errors[0] = fabs(series->sums[0] - log(1 + x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + pow(-1, i) * (pow(x, i + 1) / (i + 1));
        series->errors[i] = fabs(series->sums[i] - log(1 + x));
    }
}

// Вычисление натурального логарифма (обратный порядок)
void calculateLogarithmSeriesReverse(Series* series) {
    double x = series->input;
    int last = series->numTerms - 1;
    series->sums[last] = pow(-1, last) * pow(x, last + 1) / (last + 1);
    series->errors[last] = fabs(series->sums[last] - log(1 + x));
    for (int i = last - 1; i >= 0; i--) {
        series->sums[i] = series->sums[i + 1] + pow(-1, i) * pow(x, i + 1) / (i + 1);
        series->errors[i] = fabs(series->sums[i] - log(1 + x));
    }
}

void printTableHeader() {
    printf("+-----------------+-----------------+-----------------+\n");
    printf("|      Сумма      |     Ошибка      |  Итерация (n)   |\n");
    printf("+-----------------+-----------------+-----------------+\n");
}

void printTableRow(double sum, double error, int iteration) {
    printf("| %15.6lf | %15.6lf | %15d |\n", sum, error, iteration);
}

void printTableFooter() {
    printf("+-----------------+-----------------+-----------------+\n\n");
}

void runProgram() {
    Series data; // Используем новую структуру Series
    int option;
    double value;
    int iterations;

    printf("Выберите функцию:\n");
    printf("1. Синус\n");
    printf("2. Косинус\n");
    printf("3. Экспонента\n");
    printf("4. Натуральный логарифм\n");
    printf("5. Выход\n");
    printf("Ваш выбор: ");
    scanf_s("%d", &option);

    if (option == 5) {
        printf("Завершение работы программы.\n");
        return;
    }

    if (option < 1 || option > 5) {
        printf("Ошибка: выбран неверный вариант. Попробуйте снова.\n\n");
        runProgram();
        return;
    }

    printf("Введите значение x: ");
    scanf_s("%lf", &value);

    if (option == 4 && fabs(value) >= 1) {
        printf("Ошибка: для логарифма |x| должен быть меньше 1.\n\n");
        runProgram();
        return;
    }

    printf("Введите количество итераций: ");
    scanf_s("%d", &iterations);

    if (iterations < 1) {
        printf("Ошибка: количество итераций должно быть положительным числом.\n\n");
        runProgram();
        return;
    }

    data.input = value; // Используем новое поле input
    initializeSeries(&data, iterations + 1); // Используем новое название функции

    switch (option) {
    case 1:
        printf("\nРезультаты для синуса (прямой порядок):\n");
        printTableHeader();
        calculateSineSeries(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("Результаты для синуса (обратный порядок):\n");
        printTableHeader();
        calculateSineSeriesReverse(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    case 2:
        printf("\nРезультаты для косинуса (прямой порядок):\n");
        printTableHeader();
        calculateCosineSeries(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("Результаты для косинуса (обратный порядок):\n");
        printTableHeader();
        calculateCosineSeriesReverse(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    case 3:
        printf("\nРезультаты для экспоненты (прямой порядок):\n");
        printTableHeader();
        calculateExponentialSeries(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("Результаты для экспоненты (обратный порядок):\n");
        printTableHeader();
        calculateExponentialSeriesReverse(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    case 4:
        printf("\nРезультаты для натурального логарифма (прямой порядок):\n");
        printTableHeader();
        calculateLogarithmSeries(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("Результаты для натурального логарифма (обратный порядок):\n");
        printTableHeader();
        calculateLogarithmSeriesReverse(&data); // Используем новое название функции
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    default:
        break;
    }

    cleanupSeries(&data); // Используем новое название функции

    // Рекурсивный вызов для повторного выбора операции
    runProgram();
}