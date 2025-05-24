#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template<typename T>

class Vector {
protected:
    int size;
    T *arr;
public:
    Vector() : size(0), arr(nullptr) {}

    Vector(int size_, T val = T(0))  {
        this->size = size_;
        this->arr = new T[size_];
        for (int i = 0; i < size_; i++) {
            this->arr[i] = val;
        }
    }

    Vector(const Vector &copy) {
        this->size = copy.size;
        this->arr = new T[copy.size];
        for (int i = 0; i < copy.size; i++) {
            this->arr[i] = copy.arr[i];
        }
    }

    int getSize() const {return this->size;}

    Vector<T> operator+(Vector &b) const {
        if (this->size != b.size) {}
        Vector result=*this;
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] + b.arr[i];
        }
        return result;
    }

    Vector<T> operator-( Vector &b) const{
        if (this->size != b.size) {}
        Vector result=*this;
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] - b.arr[i];
        }
        return result;
    }

    Vector<T> operator*(const Vector &b) const{
        if (this->size != b.size) {}
        Vector result=*this;
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] * b.arr[i];
        }
        return result;
    }

    Vector<T> operator* (int val) const{
        Vector<T> result=*this;
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] * val;
        }
        return result;
    }

    Vector<T> &operator=(const Vector &b) {
        if (this != &b) {
            delete[] arr;
            size = b.size;
            arr = new T[size];
            for (int i = 0; i < size; i++) {
                arr[i] = b.arr[i];
            }
        }
        return *this;
    }

    T & operator [](int index) const{
        if (index >= this->size) std::cout << "Вы вышли за рамки индексации" << std::endl;
        else return arr[index];
    }

    friend std::istream &operator>>(std::istream &is, Vector<T> &vec) {
        std::cout << "Введите вектор состоящий из " << vec.size <<" элементов" << std::endl;
        for (int i = 0; i < vec.size; i++) {
            is >> vec.arr[i];
        }
        return is;
    }

    void print() const{
        for (int i =0 ; i< this->size;i++){
            std::cout << this -> arr[i] << ' ';
        }
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }
};

#endif
