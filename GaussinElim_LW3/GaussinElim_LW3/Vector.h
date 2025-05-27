#pragma once
#include <iostream>

template<typename T>
class Vector {
private:
    T* data;          // Указатель на массив
    int size;         // Количество элементов
    int capacity;     // Выделенная память

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