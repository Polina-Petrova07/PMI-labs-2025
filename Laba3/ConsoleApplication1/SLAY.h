#pragma once
#include "Matrix.h"
using namespace std;
template <typename T>
class SLAY : public Matrix<T> {
public:
	int* lead_number;
	SLAY(int row, int col) : Matrix<T>(row, col) {
		lead_number = new int[row];
		for (int i = 0; i < this->row; i++) {
			lead_number[i] = 0;
		}
	}
	SLAY(Matrix<T>& m) :Matrix<T>(m) {
		lead_number = new int[m.Row()];
		for (int i = 0; i < this->row; i++) {
			lead_number[i] = 0;
		}
	}
	void Gauss_Jardan_method(Vector<T>& vector) {
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < this->col; j++) {
				if (this->data[i][j] != 0) {
					(*this).String_conversion(i, j, vector);
					lead_number[i] = j;
					break;
				}
			}
		}
		for (int i = 0; i < this->row; i++) {
			if (lead_number[i] != i) {
				Swap(vector[i], vector[lead_number[i]]);
				Swap_int(lead_number[i], lead_number[lead_number[i]]);
			}
		}
	}
	void String_conversion(int a, int b, Vector<T>& vector) {
		for (int i = 0; i < this->row; i++) {
			if (i != a && this->data[a][b] != 0) {
				float ratio = -this->data[i][b] / this->data[a][b];
				for (int j = 0; j < this->col; j++) {
					this->data[i][j] = this->data[a][j] * ratio + this->data[i][j];
				}
				vector.data[i] = vector.data[a] * ratio + vector.data[i];
				(*this).PrintMatrix();
				vector.data[a] = vector.data[a] / this->data[a][b];
				this->data[a] /= this->data[a][b];
			}
		}
	}

	void Gauss(Vector<T>& vector) {
		if ((this->row != vector.Size()) or (this->row != this->col)) {
			throw logic_error("Размеры не совместимы");
		}
		Matrix<T> ww(this->row, this->col);
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < this->col; j++) {
				ww.data[i][j] = this->data[i][j];
			}
		}
		SLAY<T> new_slay(ww);
		new_slay.Gauss_Jardan_method(vector);
		bool flag = new_slay.Сhecking_for_degeneracy();
		if (not flag) {
			throw string{ "Матрица вырождена" };
		}
		PrintEndVector(vector);
		
	}
	void PrintEndVector(Vector<T>& v) {
		cout << "Ответ: ( ";
		for (int i = 0; i < this->row; i++) {
			cout << "x" << i + 1 << " ";
		}
		cout << ") = ( ";
		for (int i = 0; i < this->row; i++) {
			cout << v[i] << " ";
		}
		cout << ")\n";
	}
	void Swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}
	void Swap_int(int & a, int & b) {
		int c = a;
		a = b;
		b = c;
	}
	~SLAY() {
		delete[] lead_number;
	}
};