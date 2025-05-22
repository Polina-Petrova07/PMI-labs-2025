#pragma once
#ifndef SLAY_H
#define SLAY_H

#include "Matrix.h"

template<typename T>

class SLAY:public Matrix<T>{
public:
    SLAY(Matrix<T>& Matr ) : Matrix<T>(Matr)  {}

    void swap(T &a , T &b){
        T temp = a;
        a = b;
        b = temp;
    }

    void swap_vector(int index_N1 ,int index_N2){
        int M = this->getCols();
        for (int i = 0; i < M; i++) {
            swap((*this)[index_N1][i], (*this)[index_N2][i]);
        }
    }

    Vector<T> gauss(Vector<T> b) {
        int N = this->getRows();
        int M = this->getCols();
        Vector<T> x(N);

        for (int i = 0; i < N; i++) {

            int maxRow = i;
            T maxVal = abs((*this)[i][i]);

            for (int k = i + 1; k < N; k++) {
                if (abs((*this)[k][i]) > maxVal) {
                    maxVal = abs((*this)[k][i]);
                    maxRow = k;
                }
            }

            if (maxRow != i) {
                (*this).swap_vector(i, maxRow);
                swap(b[i], b[maxRow]);
            }

            T div = (*this)[i][i];
            if (div == 0) {
                throw std::runtime_error("Матрица не вырождена");
            }

            for (int j = i; j < M; j++) {
                (*this)[i][j] /= div;
            }
            b[i] /= div;

            for (int k = i + 1; k < N; k++) {
                T factor = (*this)[k][i];
                for (int j = i; j < M; j++) {
                    (*this)[k][j] -= (*this)[i][j] * factor;
                }
                b[k] -= b[i] * factor;
            }
        }

        for (int i = N - 1; i >= 0; i--) {
            x[i] = b[i];
            for (int j = i + 1; j < N; j++) {
                x[i] -= (*this)[i][j] * x[j];
            }
        }

        return x;
    }

    Vector<T> solve(Vector<T>& b) {
        if (this->getRows() != b.getSize()) {
            throw std::invalid_argument("Не совместные размеры");
        }
        Matrix<T> temp(*this);
        SLAY<T> temp_solver(temp);

        return temp_solver.gauss(b);
    }
};

#endif


