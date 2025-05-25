#pragma once
#include "Vector.h"
using namespace std;
template <typename T>
class Matrix : public Vector<Vector<T>> {
protected:
	int row;
	int col;
public:
	Matrix(int row_, int col_) :
		row(row_),
		col(col_),
		Vector<Vector<T>>(row_) {
		for (int i = 0; i < row; i++) {
			this->data[i] = Vector<T>(col);
		}
	}
	Matrix(const Matrix<T>& a) :row(a.Row()), col(a.Col()), Vector<Vector<T>>(a.Row()) {
		this->data = a.data;
	}
	void PrintMatrix() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << this->data[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}

	void Add_Matrix() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cin >> this->data[i][j];
			}
		}
	}

	bool Ñhecking_for_degeneracy() {
		for (int i = 0; i < row; i++) {
			int ct = 0;
			for (int j = 0; j < col; j++) {
				if (this->data[i][j] == 0) {
					ct += 1;
				}
			}
			if (ct == col) {
				return false;
			}
		}
		return true;
	}
	int Row() const { return row; }
	int Col() const { return col; }
	~Matrix() {}
};
