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
class matrix :public vector<T> {
public:
    vector<T>* mx;
    int str, stlb;

    matrix(int n, int m) {
        str = n;
        stlb = m;
        mx = new vector<T>[n];
        for (int i = 0; i < n; i++) {
            mx[i] = vector<T>(m);
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const matrix a) {
        for (int i = 0; i < a.str; i++) {
            os << a.mx[i];
        }
        os << "\n";
        return os;
    }
    vector<T>& operator[](int n) {
        return mx[n];
    }
};

template <class T>
class SLU : public matrix<T> {
private:
    using matrix<T>::mx; // �������� �� ��ߧѧ�ݧ֧է�ӧѧߧߧ�ާ� ���ݧ� mx (�ҧ֧� ����ԧ� �ߧ� ��ѧҧ��ѧ֧�)
    using matrix<T>::str; // �������� �� ��ߧѧ�ݧ֧է�ӧѧߧߧ�ާ� ���ݧ� str (�ҧ֧� ����ԧ� �ߧ� ��ѧҧ��ѧ֧�)

    vector<T> b;
    vector<T> x;

    void swap_rows(int row1, int row2) {
        vector<T> temp = mx[row1];
        mx[row1] = mx[row2];
        mx[row2] = temp;

        T temp_b = b[row1];
        b[row1] = b[row2];
        b[row2] = temp_b;
    }

    void gaussian_elimination() {
        for (int k = 0; k < str; ++k) {
            // ����ڧ�� �ӧ֧է��֧ԧ� ��ݧ֧ާ֧ߧ�� �� ����ݧҧ�� k
            int max_row = k;
            T max_val = std::abs(mx[k][k]);
            for (int i = k + 1; i < str; ++i) {
                if (std::abs(mx[i][k]) > max_val) {
                    max_row = i;
                    max_val = std::abs(mx[i][k]);
                }
            }

            // ���֧�֧��ѧߧ�ӧܧ� ������, �֧�ݧ� �ߧ֧�ҧ��էڧާ�
            if (max_row != k) {
                swap_rows(k, max_row);
            }

            // �����ާ�� ����: ��ҧߧ�ݧ֧ߧڧ� ��ݧ֧ާ֧ߧ��� �ߧڧا� �ӧ֧է��֧ԧ�
            for (int i = k + 1; i < str; ++i) {
                T factor = mx[i][k] / mx[k][k];
                for (int j = k; j < str; ++j) {
                    mx[i][j] -= factor * mx[k][j];
                }
                b[i] -= factor * b[k];
            }
        }
    }

    void back_substitution() {
        for (int i = str - 1; i >= 0; --i) {
            x[i] = b[i];
            for (int j = i + 1; j < str; ++j) {
                x[i] -= mx[i][j] * x[j];
            }
            x[i] /= mx[i][i];
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