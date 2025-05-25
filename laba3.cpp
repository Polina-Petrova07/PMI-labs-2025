#include <iostream>
#include <cmath>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data;
    size_t size;

public:
    // Конструкторы
    Vector(size_t size = 0) : size(size) {
        data = new T[size]();
    }

    Vector(const Vector& other) : size(other.size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~Vector() {
        delete[] data;
    }

    // Оператор присваивания
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Доступ к элементам
    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Размер вектора
    size_t getSize() const { return size; }

    // Изменение размера
    void resize(size_t newSize) {
        T* newData = new T[newSize]();
        size_t minSize = (newSize < size) ? newSize : size;
        for (size_t i = 0; i < minSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

    // Обмен элементов
    void swap(Vector& other) {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be of the same size to swap");
        }
        for (size_t i = 0; i < size; ++i) {
            std::swap(data[i], other.data[i]);
        }
    }

    // Вывод вектора
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
        os << "[ ";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.data[i] << " ";
        }
        os << "]";
        return os;
    }
};

template <typename T>
class Matrix {
protected:
    Vector<Vector<T>> data;
    size_t size;

public:
    // Конструкторы
    Matrix(size_t size = 0) : size(size), data(size) {
        for (size_t i = 0; i < size; ++i) {
            data[i].resize(size);
        }
    }

    // Доступ к строкам матрицы
    Vector<T>& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const Vector<T>& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Размер матрицы
    size_t getSize() const { return size; }

    // Изменение размера
    void resize(size_t newSize) {
        data.resize(newSize);
        for (size_t i = 0; i < newSize; ++i) {
            data[i].resize(newSize);
        }
        size = newSize;
    }

    // Обмен строк
    void swapRows(size_t i, size_t j) {
        if (i >= size || j >= size) throw std::out_of_range("Matrix indices out of range");
        data[i].swap(data[j]);
    }

    // Вывод матрицы
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
        for (size_t i = 0; i < mat.size; ++i) {
            os << mat.data[i] << "\n";
        }
        return os;
    }
};

template <typename T>
class SLAE : public Matrix<T> {
public:
    using Matrix<T>::Matrix;
    using Matrix<T>::size;
    using Matrix<T>::data;
    using Matrix<T>::swapRows;

    Vector<T> solveGauss(Vector<T> rightSide) {
        if (rightSide.getSize() != size) {
            throw std::invalid_argument("Right side vector size doesn't match matrix size");
        }

        // Прямой ход метода Гаусса с выбором ведущего элемента
        for (size_t col = 0; col < size; ++col) {
            // Поиск ведущего элемента
            size_t maxRow = col;
            T maxVal = std::abs(data[col][col]);

            for (size_t row = col + 1; row < size; ++row) {
                T currentVal = std::abs(data[row][col]);
                if (currentVal > maxVal) {
                    maxVal = currentVal;
                    maxRow = row;
                }
            }

            // Перестановка строк
            if (maxRow != col) {
                swapRows(col, maxRow);
                std::swap(rightSide[col], rightSide[maxRow]);
            }

            // Нормализация текущей строки
            T pivot = data[col][col];
            if (std::abs(pivot) < 1e-10) {
                throw std::runtime_error("Matrix is singular or nearly singular");
            }

            for (size_t j = col; j < size; ++j) {
                data[col][j] /= pivot;
            }
            rightSide[col] /= pivot;

            // Исключение переменной из других уравнений
            for (size_t row = 0; row < size; ++row) {
                if (row != col && std::abs(data[row][col]) > 1e-10) {
                    T factor = data[row][col];
                    for (size_t j = col; j < size; ++j) {
                        data[row][j] -= factor * data[col][j];
                    }
                    rightSide[row] -= factor * rightSide[col];
                }
            }
        }

        return rightSide;
    }
};

int main() {
    try {
        // Задаем размер кв матрицы
        int size_matrix = 0;
        std::cout << "Size matrix:" << "\n";
        std::cin >> size_matrix;
        SLAE<double> matrix(size_matrix);



        // Заполнение матрицы
        double rez;
        for (int i = 0; i < size_matrix;i++)
        {
            std::cout << "String number:" << i+1 << "\n";
            for (int j = 0; j < size_matrix; j++)
            {
                std::cout << "Value:" <<"\n";
                std::cin >> rez;
                matrix[i][j] = rez;
            }
        }
    

        // Правая часть
        Vector<double> rightSide(size_matrix);
        for (int i = 0; i < size_matrix; i++)
        {
            
            std::cout << "Send rigth value:" << "\n";
            std::cin >> rez;
            rightSide[i] = rez;
        }

        std::cout << "Matrix:\n" << matrix;
        std::cout << "Right side: " << rightSide << "\n";

        // Решение системы
        Vector<double> solution = matrix.solveGauss(rightSide);
        std::cout << "Solution: " << solution << "\n";

    }
    // ошибка
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}

// входные данные для проверки
   // matrix[0][0] = 2; matrix[0][1] = 1; matrix[0][2] = -1;
   // matrix[1][0] = -3; matrix[1][1] = -1; matrix[1][2] = 2;
   // matrix[2][0] = -2; matrix[2][1] = 1; matrix[2][2] = 2;
   // rightSide[0] = 8;
   // rightSide[1] = -11;
   // rightSide[2] = -3;