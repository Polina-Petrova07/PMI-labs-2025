#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class Vector {
public:
    std::vector<T> vect;

    Vector() {}
    Vector(int n): vect(n, T()) {}


    T& operator[](int index){ 
        return vect[index];
    }

    int Size(){
        return vect.size();
    }
    void input() {
        for (auto& el : vect) std::cin >> el;
    }
    friend std::ostream& operator<<(std::ostream& os,  Vector<T>& v) {
        for ( auto& el : v.vect) os << el << "\t";
        return os;
    }
};

template <typename T>
class Matrix : public Vector<Vector<T>> {
public:

    Matrix(int n, int m) {
        this->vect.resize(n, Vector<T>(m));
    }

    int chislo_strok(){
        return this->vect.size();
    }
    int chislo_stolbcov(){
        return this->vect[0].Size();
    }

    void Swap(int stroka1, int stroka2) {
        std::swap(this->vect[stroka1], this->vect[stroka2]);
    }

    void input() {
        for (auto& str : this->vect) str.input();
    }
};

template <typename T>
class SLAU : public Matrix<T> {
private:
    Vector<T> Right_H;    
    Vector<T> reshenie;  
    bool solved = false;

public:
    SLAU( Matrix<T>& A,  Vector<T>& b) : Matrix<T>(A), Right_H(b), reshenie(b.Size()) {
        if (A.chislo_strok() != A.chislo_stolbcov() || A.chislo_strok() != b.Size()) {
            throw std::invalid_argument("Размеры матрицы и вектора не совпадают");
        }
    }
 
    void Resh() {
        int n = this->chislo_strok();

        // Прямой ход
        for (int i = 0; i < n; ++i) {
            // Поиск максимального элемента в столбце
            int max_str = i;
            for (int k = i + 1; k < n; ++k) {
                if (std::abs((*this)[k][i]) > std::abs((*this)[max_str][i])) {
                    max_str = k;
                }
            }
            if (std::abs((*this)[max_str][i]) < 1e-12) {
                throw std::runtime_error("Система вырождена или несовместна");
            }

            this->Swap(i, max_str);
            std::swap(Right_H[i], Right_H[max_str]);

            // Обнуляем строки ниже
            for (int k = i + 1; k < n; ++k) {
                T coeff = (*this)[k][i] / (*this)[i][i];
                for (int j = i; j < n; ++j) {
                    (*this)[k][j] -= coeff * (*this)[i][j];
                }
                Right_H[k] -= coeff * Right_H[i];
            }
        }

        // Обратный ход
        for (int i = n - 1; i >= 0; --i) {
            T sum = Right_H[i];
            for (int j = i + 1; j < n; ++j) {
                sum -= (*this)[i][j] * reshenie[j];
            }
            reshenie[i] = sum / (*this)[i][i];
        }

        solved = true;
    }

    Vector<T> poluchit_reshenie() {
        if (!solved) Resh();
        return reshenie;
    }
};
int main(){
    int n;
    std::cout << "Введите размер матрицы: ";
    std::cin >> n;

    Matrix<double> matrica_koefficientov(n, n);
    Vector<double> Right_H(n);

    std::cout << "Введите матрицу коэффициентов:\n";
    matrica_koefficientov.input();

    std::cout << "Введите правую часть:\n";
    Right_H.input();

    try {
        SLAU<double> sistema(matrica_koefficientov, Right_H);
        Vector<double> reshenie = sistema.poluchit_reshenie();
        std::cout << "Решение: \n(       " << reshenie << ")\n";
    } catch ( std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}