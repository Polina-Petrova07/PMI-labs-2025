#pragma once
#include <cmath>
#include<iostream>
template<typename T>
class vector
{
protected:
	int size;
	T* array;
public:
	vector() {
		size = 0;
		array = nullptr;
	}
	vector(vector& copy) {
		this->size = copy.size;
		this->array = new T[copy.size];
		for (int i = 0; i < copy.size; i++) {
			this->array[i] = copy.array[i];
		}
	}
	vector(int _size) {
		size = _size;
		array = new T[_size];
		for (int i = 0; i < _size; i++) { array[i] = 0; }
	}
	T& operator[](int _num) {
		return array[_num];
	}
	int get_size() { return size; };
	~vector(){
			delete[] array;
			array = nullptr;
		
	}
		
	vector& operator=(const vector& other) {
			size = other.size;
			array = new T[size];
			for (size_t i = 0; i < size; ++i) {
				array[i] = other.array[i];
			
		}
		return *this;
	}
	
};
template<typename T>
void swap_v(vector<T> a, vector<T> b) {
	for (int i = 0; i < a.get_size(); i++)
	{
		b[i] = b[i] + a[i];
		a[i] = b[i] - a[i];
		b[i] = b[i] - a[i];
	}
}
template<typename T>
void swap(T a, T b) {
	T t = a;
	a = b;
	b = t;
}