#pragma once
#include "Vector.h"

template<typename T>
class Matrix {
protected:
    int size;
    Vector<Vector<T>> data;

public:
    Matrix(int n) : size(n), data(n) {
        for (int i = 0; i < size; ++i) {
            data[i] = Vector<T>(size);
        }
    }

    int getSize() const {
        return size;
    }

    Vector<T>& operator[](int i) {
        return data[i];
    }

    const Vector<T>& operator[](int i) const {
        return data[i];
    }

    void swapRows(int i, int j) {
        data.swap(i, j);  // использование swap() из vector.h
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }
};
