#pragma once
#include "vector.h"
template<typename T>
class Matrix :public vector<vector<T>>
{
public:
	Matrix(int len) {
		this->array = new vector<T>[len];
		this->size = len;
		for (int i = 0; i < len; i++)
		{
			this->array[i] =  vector<T>(len);
		}
	};
	friend std::istream& operator>>(std::istream& is, Matrix<T>& matrx) {
		std::cout << "Insert matrix " << std::endl;
		for (int i = 0; i < matrx.get_size(); i++) {
			for (int j = 0; j < matrx.get_size(); j++) {
				is >> matrx[i][j];
			}
		}
		return is;
	}
	vector<T>& operator[](int index) { return this->array[index]; }

	Matrix& operator=(const Matrix& other) {
		for (size_t i = 0; i < other.size; ++i) {
			this[i] = other[i];

		}
		return *this;
	}
	void print() {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++)
			{
				std::cout<< this->array[i][j]<<" ";
			}
			std::cout << "\n";
		}
	}
};