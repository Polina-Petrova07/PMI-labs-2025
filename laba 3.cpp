#pragma once
#include <iostream>

template<typename T>
class Vector {
private:
    T* data;          
    int size;         
    int capacity;     

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

public:
    Vector() {
        size = 0;
        capacity = 4;
        data = new T[capacity];
    }

    Vector(int n, const T& value = T()) {
        size = n;
        capacity = n;
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = value;
    }

    Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size >= capacity)
            resize();
        data[size++] = value;
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void swap(int i, int j) {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
};


template<typename T>
class Matrix {
private:
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
        data.swap(i, j);  
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


class SLAU : public Matrix<double> {
public:

    using Matrix::Matrix; 

    Vector<double> gauss(Vector<double> rhs) {
        int n = getSize();

        for (int i = 0; i < n; ++i) {
            int maxRow = i;
            for (int k = i + 1; k < n; ++k) {
                if (std::abs((*this)[k][i]) > std::abs((*this)[maxRow][i])) {
                    maxRow = k;
                }
            }
            swapRows(i, maxRow);
            rhs.swap(i, maxRow);

            double pivot = (*this)[i][i];
            if (pivot == 0.0) {
                bool allZero = true;
                for (int j = 0; j < n; ++j) {
                    if ((*this)[i][j] != 0.0) {
                        allZero = false;
                        break;
                    }
                }

                if (allZero && rhs[i] != 0.0) {
                    std::cerr << "Система несовместна: строка " << i << " имеет вид 0 = " << rhs[i] << "\n";
                    exit(1);
                }
                else if (allZero && rhs[i] == 0.0) {
                    std::cerr << "Система вырождена: строка " << i << " имеет вид 0 = 0 (бесконечно много решений)\n";
                    exit(1);
                }
                else {
                    std::cerr << "Ошибка: ведущий элемент равен нулю после выбора главного элемента (матрица вырождена) (pivot = 0).\n";
                    exit(1);
                }
            }

            for (int j = i; j < n; ++j) {
                (*this)[i][j] /= pivot;
            }
            rhs[i] /= pivot;

            for (int k = i + 1; k < n; ++k) {
                double factor = (*this)[k][i];
                for (int j = i; j < n; ++j) {
                    (*this)[k][j] -= factor * (*this)[i][j];
                }
                rhs[k] -= factor * rhs[i];
            }
        }
        Vector<double> result(n);
        for (int i = n - 1; i >= 0; --i) {
            result[i] = rhs[i];
            for (int j = i + 1; j < n; ++j) {
                result[i] -= (*this)[i][j] * result[j];
            }
        }

        return result;
    }
};


int main() {
    setlocale(LC_ALL, "Ru");

    int n;
    std::cout << "Введите размерность системы (N x N): ";
    std::cin >> n;

    SLAU system(n);
    Vector<double> rhs(n);  

    std::cout << "Введите коэффициенты матрицы (a11,a12,a13,...,a21,a22,...), с размерностью " << n << "x" << n << ":\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double value;
            std::cin >> value;
            system[i][j] = value;
        }
    }

    std::cout << "Введите правую часть (" << n << " значений):\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> rhs[i];
    }

    Vector<double> solution = system.gauss(rhs);

    std::cout << "Решение:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x[" << i+1 << "] = " << solution[i] << "\n";
    }

    return 0;
}
