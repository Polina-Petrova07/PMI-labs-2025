#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ��������� ��� �������� ������ ����
typedef struct {
    int numTerms;      // ���������� ������ ����
    double input;      // ������� �������� x
    double* errors;    // ������ ������
    double* sums;      // ������ ��������� ����
} Series;

// ������� ��� ���������� �����
void calculateSineSeries(Series* series);
void calculateCosineSeries(Series* series);
void calculateExponentialSeries(Series* series);
void calculateLogarithmSeries(Series* series);

// ������� ��� ���������� ����� � �������� �������
void calculateSineSeriesReverse(Series* series);
void calculateCosineSeriesReverse(Series* series);
void calculateExponentialSeriesReverse(Series* series);
void calculateLogarithmSeriesReverse(Series* series);

// ��������������� �������
unsigned long long computeFactorial(int n);
void initializeSeries(Series* series, int terms);
void cleanupSeries(Series* series);