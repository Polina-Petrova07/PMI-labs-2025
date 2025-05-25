#include <iostream>
#include <locale>
#include "Matrix.h"
#include "SLAY.h"
#include "Vector.h"
using namespace std;

int main() {
	int row, col, size;
	setlocale(LC_ALL, "Russian");
	while (true){
		cout << "Введите размеры матрицы(row, col): ";
		cin >> row >> col;
		SLAY<double> w(row, col);
		cout << "Введите матрицу:\n";
		w.Add_Matrix();
		try {
			cout << "Введите размер вектора	свободных членов: ";
			cin >> size;
			Vector<double> v(size);
			cout << "Введите вектор свободных членов:\n";
			v.Add_Vector();
			w.Gauss(v);
		}
		catch (const logic_error& error) {
			cout << error.what()<<"\nВведите корректные данные\n";
		}
		catch (const string& error) {
			cout << error << "\nВведите невырожденную матрицу\n";
		}
	}
}