#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Структура для хранения данных ряда
typedef struct {
    int numTerms;      // Количество членов ряда
    double input;      // Входное значение x
    double* errors;    // Массив ошибок
    double* sums;      // Массив частичных сумм
} Series;

// Функции для вычисления рядов
void calculateSineSeries(Series* series);
void calculateCosineSeries(Series* series);
void calculateExponentialSeries(Series* series);
void calculateLogarithmSeries(Series* series);

// Функции для вычисления рядов в обратном порядке
void calculateSineSeriesReverse(Series* series);
void calculateCosineSeriesReverse(Series* series);
void calculateExponentialSeriesReverse(Series* series);
void calculateLogarithmSeriesReverse(Series* series);

// Вспомогательные функции
unsigned long long computeFactorial(int n);
void initializeSeries(Series* series, int terms);
void cleanupSeries(Series* series);