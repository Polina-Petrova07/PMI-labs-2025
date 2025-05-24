#include <iostream>
#include <cmath>

template <typename T>
class Vector {
protected:
    size_t size;
public:
    T* data;

    Vector(size_t n = 1) : size(n), data(new T[n]()) {}

    Vector(const Vector& other) : size(other.size), data(new T[other.size]) {
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    ~Vector() { delete[] data; }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (size_t i = 0; i < v.size; ++i)
            os << v.data[i] << " ";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& v) {
        for (size_t i = 0; i < v.size; ++i)
            is >> v.data[i];
        return is;
    }
};
template <typename T>
class Matrix : public Vector<Vector<T>> {
public:
    Matrix(size_t n = 1) : Vector<Vector<T>>(n) {
        for (size_t i = 0; i < n; ++i)
            this->data[i] = Vector<T>(n);
    }

    void swapRows(size_t i, size_t j) {
        std::swap(this->data[i], this->data[j]);
    }
};

template <typename T>
class SLAU : public Matrix<T> {
public:
    using Matrix<T>::swapRows;
    using Matrix<T>::data;

    SLAU(size_t n) : Matrix<T>(n) {}

    Vector<T> solve(Vector<T> b) const {
        const T eps = 1e-10; 
        size_t n = this->size;
        Matrix<T> temp(*this);
        Vector<T> x(n);

       
        for (size_t k = 0; k < n; ++k) {
            size_t max_row = k;
            T max_val = std::abs(temp[k][k]);

            for (size_t i = k + 1; i < n; ++i) {
                if (std::abs(temp[i][k]) > max_val) {
                    max_val = std::abs(temp[i][k]);
                    max_row = i;
                }
            }

            
            if (max_val < eps) {
                throw std::runtime_error("The matrix is degenerate");
            }

            if (max_row != k) {
                temp.swapRows(k, max_row);
                std::swap(b[k], b[max_row]);
            }

            
            for (size_t i = k + 1; i < n; ++i) {
                T factor = temp[i][k] / temp[k][k];
                for (size_t j = k; j < n; ++j)
                    temp[i][j] -= factor * temp[k][j];
                b[i] -= factor * b[k];
            }
        }

        
        for (int i = n - 1; i >= 0; --i) {
            if (std::abs(temp[i][i]) < eps) {
                throw std::runtime_error("The zero element on the ghosts diagonal");
            }

            x[i] = b[i];
            for (int j = i + 1; j < n; ++j)
                x[i] -= temp[i][j] * x[j];
            x[i] /= temp[i][i];
        }

        return x;
    }
};