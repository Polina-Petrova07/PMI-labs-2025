#include <iostream>
#include <iomanip>

template<typename T>
class Vector {
public:
    T* arr;
    int size;

    Vector() {
        size = 0;
        arr = nullptr;
    }
    Vector(int _size) {
        size = _size;
        arr = new T[_size];
    }
    ~Vector() {
        size = 0;
        arr = nullptr;
    }

    T& operator[](int index) {
        return arr[index];
    }

    friend std::ostream& operator << (std::ostream& out, Vector vector) {
        for (int i = 0; i < vector.size; i++) {
            std::cout << std::setw(5) << vector.arr[i] << std::setw(1);
        }
        std::cout << "\n";

        return out;
    }

    friend std::istream& operator >> (std::istream& in, Vector vector) {
        for (int i = 0; i < vector.size; i++) {
            std::cin >> vector.arr[i];
        }

        return in;
    }
};

template <typename T>
class Matrix : public Vector<Vector<T>> {
public:
    int rows;

    Matrix() {
        rows = 0;
        this->arr = nullptr;
    }
    Matrix(int _rows) {
        rows = _rows;
        this->arr = new Vector<T>[rows];
        for (int i = 0; i < rows; i++) {
            this->arr[i] = Vector<T>(rows);
        }
    }
    Matrix(Matrix<T> &other) {
        rows = other.rows;
        this->arr = other.arr;
    }
    ~Matrix() {
        this->arr = nullptr;
        this->size = 0;
        rows = 0;
    }

    Vector<T>& operator[](int index) { return this->arr[index]; }

    friend std::ostream& operator << (std::ostream& out, Matrix matrix) {
        for (int i = 0; i < matrix.rows; i++) {
            std::cout << matrix.arr[i];
        }
        std::cout << "\n";

        return out;
    }

    friend std::istream& operator >> (std::istream& in, Matrix matrix) {
        for (int i = 0; i < matrix.rows; i++) {
            std::cin >> matrix.arr[i];
        }
        std::cout << "\n";

        return in;
    }
};

template <typename T>
class SLU : public Matrix<T> {
public:
    Vector<T> ans, x;

    SLU(Matrix<T> a) :  Matrix<T>(a){
        x = Vector<T>(a.rows);
    }
    ~SLU() {
        ans = NULL;
        x = NULL;
    }
    
    Vector<T> Solve(Vector<T>& _b) {
        Matrix<T> newMatrix(*this);
        ans = Vector<T>(_b);

        for (int i = 0; i < newMatrix.rows - 1; i++) {
            for (int j = i + 1; j < newMatrix.rows; j++) {
                T multiplicator = -1 * (newMatrix.arr[j][i] / newMatrix.arr[i][i]);
                for (int k = i; k < newMatrix.rows; k++) {
                    newMatrix.arr[j][k] += multiplicator * newMatrix.arr[i][k];
                }
                ans[j] += multiplicator * ans[i];
            }

            for (int j = 0; j < newMatrix.rows; j++) {
                std::cout << newMatrix.arr[j] << "\n";
            }
            std::cout << "\n";
        }

        for (int i = newMatrix.rows - 1; i >= 0; i--) {
            x[i] = ans[i];
            for (int j = i + 1; j < newMatrix.rows; ++j) {
                x[i] -= newMatrix.arr[i][j] * x[j];
            }
            x[i] /= newMatrix.arr[i][i];
        }
        return x;
    }
};


int main()
{
    int rows;
    bool isContinue = true;

    std::cout << "Enter matrix rows:\n";
    std::cin >> rows;    

    Vector<double> b(rows);
    Matrix<double> matrix(rows);
    SLU<double> slu(matrix);

    std::cout << "Enter your matrix:\n";
    std::cin >> matrix;

    while (isContinue) {
        int cont;

        std::cout << "Enter your answer:\n";
        std::cin >> b;

        Vector<double> x(rows);
        x = slu.Solve(b);
        std::cout << "X: " << x << "\n";

        std::cout << "Do you want to enter a new answer? (1 - yes, 0 - no)" << "\n";
        std::cin >> cont;
        if (cont == 0) {
            isContinue = false;
            break;
        }
    }
}   

