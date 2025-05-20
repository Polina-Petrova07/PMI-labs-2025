#include <iostream>
#include <cmath>

template <class T>
class vector {
protected:
    int size;
public:
    T* array;

    vector() {
        size = 1;
        array = new T[1];
        array[0] = 0;
    }
    vector(int _size) {
        size = _size;
        array = new T[_size];
        for (int i = 0; i < size; i++) { array[i] = 0; }
    }
    void set() {
        for (int i = 0; i < size; i++) { std::cin >> array[i]; }
    }
    T& operator[](int n) {
        return  array[n];
    }
    friend std::ostream& operator<<(std::ostream& os, const vector a) {
        for (int i = 0; i < a.size; i++) {
            os << " " << a.array[i] << "\t";
        }
        os << "\n";
        return os;
    }
};
template <class T>
class matrix :public vector<vector<T>> {
public:
    int str, stlb;

    matrix(int n, int m) {
        str = n;
        stlb = m;
        this->array = new vector<T>[n];
        for (int i = 0; i < n; i++) {
            this->array[i] = vector<T>(m);
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const matrix a) {
        for (int i = 0; i < a.str; i++) {
            os << a.array[i];
        }
        os << "\n";
        return os;
    }
    vector<T>& operator[](int n) {
        return this->array[n];
    }
};

template <class T>
class SLU : public matrix<T> {
private:
    using matrix<T>::array; // SLU dont see array without "using"
    using matrix<T>::str; // SLU dont see str without "using"

    vector<T> b;
    vector<T> x;

    void swap_rows(int row1, int row2) {
        vector<T> temp = array[row1];
        array[row1] = array[row2];
        array[row2] = temp;

        T temp_b = b[row1];
        b[row1] = b[row2];
        b[row2] = temp_b;
    }

    void gaussian_elimination() {
        for (int k = 0; k < str; ++k) {
            // Searching vedushiy element
            int max_row = k;
            T max_val = std::abs(array[k][k]);
            for (int i = k + 1; i < str; ++i) {
                if (std::abs(array[i][k]) > max_val) {
                    max_row = i;
                    max_val = std::abs(array[i][k]);
                }
            }

            if (max_row != k) {
                swap_rows(k, max_row);
            }

            for (int i = k + 1; i < str; ++i) {
                T factor = array[i][k] / array[k][k];
                for (int j = k; j < str; ++j) {
                    array[i][j] -= factor * array[k][j];
                }
                b[i] -= factor * b[k];
            }
        }
    }

    void back_substitution() {
        for (int i = str - 1; i >= 0; --i) {
            x[i] = b[i];
            for (int j = i + 1; j < str; ++j) {
                x[i] -= array[i][j] * x[j];
            }
            x[i] /= array[i][i];
        }
    }

public:


    SLU(matrix<T>& A, vector<T>& _b) : matrix<T>(A), b(_b) {
        x = vector<T>(A.str);
        gaussian_elimination();
        back_substitution();

    }

    vector<T> get_solution() const {
        return x;
    }
};
