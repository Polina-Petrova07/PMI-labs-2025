#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

template<typename T>

class Matrix: public Vector<Vector<T> > {
public:
    Matrix(): Vector<Vector<T> >() {}
    Matrix(int _rows, int _cols, T val = T(0)) : Vector<Vector<T> >(_rows, Vector<T>(_cols, val)) {}

    int getRows() const { return Vector<Vector<T> >::getSize(); }
    int getCols() const {
        if (getRows() == 0) return 0;
        return (*this)[0].getSize();
    }

    Vector<T> &operator[](int index) const {
        if (index < 0 || index >= getRows()) {
            throw std::out_of_range("Вы вышли за рамки индексации");
        }
        return Vector<Vector<T> >::operator[](index);
    }

    Matrix<T> &operator=(const Matrix<T>& other) {
        if (this != &other) {
            Vector<Vector<T> >::operator=(other);
        }
        return *this;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (getCols() != other.getRows()) {
            throw std::invalid_argument("Не совместные размеры матриц");
        }

        Matrix<T> result(getRows(), other.getCols());
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < other.getCols(); j++) {
                result[i][j] = T();
                for (int k = 0; k < getCols(); k++) {
                    result[i][j] += (*this)[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (getRows() != other.getRows() || getCols() != other.getCols()) {
            throw std::invalid_argument("Не совместные размеры матриц");
        }

        Matrix<T> result(getRows(), getCols());
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < getCols(); j++) {
                result[i][j] = (*this)[i][j] + other[i][j];
            }
        }
        return result;
    }

    friend std::istream& operator>>(std::istream& is, Matrix<T>& mat) {
        std::cout << "Введите матрицу " << mat.getRows() << "x" << mat.getCols() << std::endl;
        for (int i = 0; i < mat.getRows(); i++) {
            for (int j = 0; j < mat.getCols(); j++) {
                is >> mat[i][j];
            }
        }
        return is;
    }

    void print() const {
        for (int i = 0; i < this->getRows(); i++) {
            (*this)[i].print();
            std::cout << std::endl;
        }
    }

};

#endif
