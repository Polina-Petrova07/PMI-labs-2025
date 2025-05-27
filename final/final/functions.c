#include "header.h"

// ���������� ����������
unsigned long long computeFactorial(int n) {
    return (n <= 1) ? 1 : n * computeFactorial(n - 1);
}

// ������������� ��������� Series
void initializeSeries(Series* series, int terms) {
    series->numTerms = terms;
    series->sums = (double*)malloc(terms * sizeof(double));
    series->errors = (double*)malloc(terms * sizeof(double));
    for (int i = 0; i < terms; i++) {
        series->sums[i] = 0.0;
        series->errors[i] = 0.0;
    }
}

// ������������ ������
void cleanupSeries(Series* series) {
    free(series->sums);
    free(series->errors);
    series->sums = NULL;
    series->errors = NULL;
    series->numTerms = 0;
}

// ���������� ������ (������ �������)
void calculateSineSeries(Series* series) {
    double x = series->input;
    series->sums[0] = x;
    series->errors[0] = fabs(series->sums[0] - sin(x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + pow(-1, i) * (pow(x, 2 * i + 1) / computeFactorial(2 * i + 1));
        series->errors[i] = fabs(series->sums[i] - sin(x));
    }
}

// ���������� ������ (�������� �������)
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

// ���������� �������� (������ �������)
void calculateCosineSeries(Series* series) {
    double x = series->input;
    series->sums[0] = 1.0;
    series->errors[0] = fabs(series->sums[0] - cos(x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + pow(-1, i) * (pow(x, 2 * i) / computeFactorial(2 * i));
        series->errors[i] = fabs(series->sums[i] - cos(x));
    }
}

// ���������� �������� (�������� �������)
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

// ���������� ���������� (������ �������)
void calculateExponentialSeries(Series* series) {
    double x = series->input;
    series->sums[0] = 1.0;
    series->errors[0] = fabs(series->sums[0] - exp(x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + (pow(x, i) / computeFactorial(i));
        series->errors[i] = fabs(series->sums[i] - exp(x));
    }
}

// ���������� ���������� (�������� �������)
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

// ���������� ������������ ��������� (������ �������)
void calculateLogarithmSeries(Series* series) {
    double x = series->input;
    series->sums[0] = x;
    series->errors[0] = fabs(series->sums[0] - log(1 + x));
    for (int i = 1; i < series->numTerms; i++) {
        series->sums[i] = series->sums[i - 1] + pow(-1, i) * (pow(x, i + 1) / (i + 1));
        series->errors[i] = fabs(series->sums[i] - log(1 + x));
    }
}

// ���������� ������������ ��������� (�������� �������)
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
    printf("|      �����      |     ������      |  �������� (n)   |\n");
    printf("+-----------------+-----------------+-----------------+\n");
}

void printTableRow(double sum, double error, int iteration) {
    printf("| %15.6lf | %15.6lf | %15d |\n", sum, error, iteration);
}

void printTableFooter() {
    printf("+-----------------+-----------------+-----------------+\n\n");
}

void runProgram() {
    Series data; // ���������� ����� ��������� Series
    int option;
    double value;
    int iterations;

    printf("�������� �������:\n");
    printf("1. �����\n");
    printf("2. �������\n");
    printf("3. ����������\n");
    printf("4. ����������� ��������\n");
    printf("5. �����\n");
    printf("��� �����: ");
    scanf_s("%d", &option);

    if (option == 5) {
        printf("���������� ������ ���������.\n");
        return;
    }

    if (option < 1 || option > 5) {
        printf("������: ������ �������� �������. ���������� �����.\n\n");
        runProgram();
        return;
    }

    printf("������� �������� x: ");
    scanf_s("%lf", &value);

    if (option == 4 && fabs(value) >= 1) {
        printf("������: ��� ��������� |x| ������ ���� ������ 1.\n\n");
        runProgram();
        return;
    }

    printf("������� ���������� ��������: ");
    scanf_s("%d", &iterations);

    if (iterations < 1) {
        printf("������: ���������� �������� ������ ���� ������������� ������.\n\n");
        runProgram();
        return;
    }

    data.input = value; // ���������� ����� ���� input
    initializeSeries(&data, iterations + 1); // ���������� ����� �������� �������

    switch (option) {
    case 1:
        printf("\n���������� ��� ������ (������ �������):\n");
        printTableHeader();
        calculateSineSeries(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("���������� ��� ������ (�������� �������):\n");
        printTableHeader();
        calculateSineSeriesReverse(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    case 2:
        printf("\n���������� ��� �������� (������ �������):\n");
        printTableHeader();
        calculateCosineSeries(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("���������� ��� �������� (�������� �������):\n");
        printTableHeader();
        calculateCosineSeriesReverse(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    case 3:
        printf("\n���������� ��� ���������� (������ �������):\n");
        printTableHeader();
        calculateExponentialSeries(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("���������� ��� ���������� (�������� �������):\n");
        printTableHeader();
        calculateExponentialSeriesReverse(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    case 4:
        printf("\n���������� ��� ������������ ��������� (������ �������):\n");
        printTableHeader();
        calculateLogarithmSeries(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();

        printf("���������� ��� ������������ ��������� (�������� �������):\n");
        printTableHeader();
        calculateLogarithmSeriesReverse(&data); // ���������� ����� �������� �������
        for (int i = 0; i < data.numTerms; i++) {
            printTableRow(data.sums[i], data.errors[i], i);
        }
        printTableFooter();
        break;

    default:
        break;
    }

    cleanupSeries(&data); // ���������� ����� �������� �������

    // ����������� ����� ��� ���������� ������ ��������
    runProgram();
}