#pragma once
#include <iostream>
#include <cmath>
template <typename T>
class my_vector {
public:
    T* m_x;
    int size;
    my_vector() : size(10), m_x(new T[10]()) {}
    my_vector(int size, T value = T()) : size(size), m_x(new T[size]) {
        for (int i = 0; i < size; i++) {
            m_x[i] = value;
        }
    }
    my_vector(const my_vector& other) : size(other.size), m_x(new T[other.size]) {
        for (int i = 0; i < size; i++) {
            m_x[i] = other.m_x[i];
        }
    }
    my_vector& operator=(const my_vector& other) {
        if (this != &other) {
            delete[] m_x;
            size = other.size;
            m_x = new T[size];
            for (int i = 0; i < size; i++) {
                m_x[i] = other.m_x[i];
            }
        }
        return *this;
    }
    ~my_vector() { delete[] m_x;}
    void setVector(int size) {
        T* new_data = new T[size]();
        for (int i = 0; i < size; i++) {
            std::cin >> new_data[i];
        }
        delete[] m_x;
        m_x = new T[size];
        this->size = size;
        for (int i = 0; i < size; i++) {
            m_x[i] = new_data[i];
        }
        delete[] new_data;
    }
    void print() {
        for (int i = 0; i < this->size; i++) {
            std::cout << m_x[i] << " ";
        }
        std::cout << std::endl;
    }
    T& operator [] (int index) {
        return m_x[index];
    }
};
template <typename T>
class my_matrix :public my_vector<my_vector<T>> {
public:
    my_matrix() : my_vector<my_vector<T>>() {};
    my_matrix(int size) : my_vector<my_vector<T>>(size, my_vector<T>(size)) { this->size = size; };
    my_vector<T>& operator [] (int index) {
        return this->m_x[index];
    }
    ~my_matrix() {};
    void setMatrix(int size) {
        my_matrix<T> new_data(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cin >> new_data[i][j];
            }
        }
        *this = new_data;
    }
    my_matrix(const my_matrix& other) : my_vector<my_vector<T>>(other) {}
    my_matrix& operator=(const my_matrix& other) {
        my_vector<my_vector<T>>::operator=(other);
        return *this;
    }
    void print() {
        for (int i = 0; i < this->size; i++) {
            this->m_x[i].print();
        }
    }
};
template <typename T>
class SLAE : public my_matrix<T> {
public:
    SLAE() : my_matrix<T>() {}
    SLAE(int size) : my_matrix<T>(size) {};
    void swap_lines(my_matrix<T>& mat, int i, int j) {
        if (i == j) return;
        T* temp_ptr = mat[i].m_x;
        int temp_size = mat[i].size;
        mat[i].m_x = new T[mat[j].size];
        mat[i].size = mat[j].size;
        for (int k = 0; k < mat[j].size; k++) {
            mat[i].m_x[k] = mat[j].m_x[k];
        }
        mat[j].m_x = new T[temp_size];
        mat[j].size = temp_size;
        for (int k = 0; k < temp_size; k++) {
            mat[j].m_x[k] = temp_ptr[k];
        }
        delete[] temp_ptr;
    }
    void swap_elements(my_vector<T>& vec, int i, int j) {
        if (i == j) return;
        T temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }
    ~SLAE() {};
    my_vector<T> gauss_solve(const my_vector<T>& b) {
        const int n = this->size;
        my_matrix<T> a(*this);
        my_vector<T> b_copy = b;
        my_vector<T> x(n);
        int rang = 0;
        my_vector<T> vec(n, 0);
        for (int i = 0; i < n; i++) {
            int max_index = i;
            for (int j = i + 1; j < n; j++) {
                if ((std::abs(a[j][i])) > (std::abs(a[max_index][i]))) {
                    max_index = j;
                }
            }
            if ((std::abs(a[max_index][i])) < 1e-10) { continue; }
            if (max_index != i) {
                swap_lines(a, i, max_index);
                swap_elements(b_copy, i, max_index);
            }
            rang++;
            T div = a[i][i];
            for (int j = i; j < n; j++) {
                a[i][j] /= div;
            }
            b_copy[i] /= div;
            for (int j = i + 1; j < n; j++) {
                T factor = a[j][i];
                for (int k = i; k < n; k++) {
                    a[j][k] -= a[i][k] * factor;
                }
                b_copy[j] -= b_copy[i] * factor;
            }
        }
        for (int i = rang; i < n; i++) {
            if (std::abs(b_copy[i]) > 1e-10) {
                std::cout << "Система несовместна\n";
                return vec; 
            }
        }
        if (rang < n) {
            std::cout << "Бесконечно много решений\n";
            return vec;
        }
        for (int i = n - 1; i >= 0; i--){
            x[i] = b_copy[i];
            for (int j = i + 1; j < n; j++) {
                x[i] -= a[i][j] * x[j];
            }
            x[i] /= a[i][i];
        }
        return x;
    }
};
void locale(void);
void print(void);