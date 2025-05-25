#include <iostream>
#include <locale.h>
using namespace std;
template <typename T>
class Vector {
protected:
	int length;
public:
	T* m_x;
	Vector() {
		length=10;
		m_x = new T[10];
	}
	Vector(int size_0, T value = T()) : length(size_0) {
		m_x = new T[length];
		for (int i = 0; i < length; i++) {
			m_x[i] = value;
		}
	}
	~Vector() {}
	void output(int z) {
		for (int i = 0; i < z-1; i++) {
			cout << m_x[i] << " ";
		}
		cout << m_x[z-1];
	}
	void input(int z) {
		for (int i = 0;i < z;i++) {
			cin >> m_x[i];
		}
	}
	Vector<T>& operator=(const Vector<T> A) {
		for (int i = 0;i < length;i++) {
			m_x[i] = A.m_x[i];
		}
		return *this;
	}
	Vector<T>& operator=(T x) {
		for (int i = 0;i < length;i++) {
			m_x[i] = x;
		}
		return *this;
	}
	Vector<T>& operator +(const Vector<T> A) {
		for (int i = 0; i < length; i++) {
			m_x[i] += A.m_x[i];
		}
		return *this;
	}
	Vector<T>& operator -(const Vector<T> A) {
		for (int i = 0; i < length; i++) {
			m_x[i] -= A.m_x[i];
		}
		return *this;
	}
	Vector<T>& operator *(T x) {
		for (int i = 0; i < length; i++) {
			m_x[i] *= x;
		}
		return *this;
	}
	Vector<T>& operator *=(T x) {
		for (int i = 0; i < length; i++) {
			m_x[i] *= x;
		}
		return *this;
	}
	Vector<T>& operator /(T x) {
		//Vector<T> a(length);
		//a.data = data;
		if (x != 0) {
			for (int i = 0; i < length; i++) {
				m_x[i] /= x;
			}
		}
		return *this;
	}
	Vector<T>& operator /=(T x) {
		for (int i = 0; i < length; i++) {
			if (m_x[i] != 0) {
				m_x[i] /= x;
			}
		}
		return *this;
	}
	T& operator[](int index) { return m_x[index]; }
};
template <typename T>
class Sq_Matrix :public Vector<Vector<T>> {
protected:
	int n;
public:
	Vector<T>* matrix;
	Sq_Matrix() {
		matrix = new Vector<T>[n];
		for (int i = 0;i < n;i++) {
			matrix[i] = Vector<T>(n);
		}
	}
	Sq_Matrix(int len) {
		n = len;
		matrix = new Vector<T>[len];
		for (int i = 0;i < len;i++) {
			matrix[i] = Vector<T>(len);
		}
	}
	~Sq_Matrix() {}
	void input_matrix() {
		for (int i = 0;i < n;i++) {
			matrix[i].input(n);
		}
		cout << endl;
	}
	void output_matrix() {
		for (int i = 0;i < n;i++) {
			matrix[i].output(n);
			cout << endl;
		}
	}
	void swap(int a,int b) {
		Vector<T> C=matrix[b];
		T* z = new T[n];
		for (int i = 0;i < n;i++) {
			z[i] = C[i];
		}
		matrix[b] = matrix[a];
		for (int i = 0;i < n;i++) {
			matrix[a][i] = z[i];
		}
	}
	Sq_Matrix<T>& operator =(T x) {
		for (int i = 0;i < n;i++) {
			matrix[i] = x;
		}
		return *this;
	}
	Sq_Matrix<T>& operator =(const Sq_Matrix<T> A) {
		for (int i = 0;i < n;i++) {
			matrix[i] = A.matrix[i];
		}
		n = A.n;
		return *this;
	}
};
template <typename T>
class SLAE :public Sq_Matrix<T> {
protected:
public:
	int order;
	SLAE(int len) {
		order = len;
	}
	~SLAE(){}
	void Gauss(Vector<T> b) {
		Sq_Matrix<T> A(order);
		Vector<T> answer(order);
		answer = 0;
		cout << "Введите матрицу A размером и рангом " << order << ":" << endl;
		A.input_matrix();
		//b.input(order);
		Sq_Matrix<T> E(order);
		E = 0;
		for (int i = 0;i < order;i++) {
			E.matrix[i][i] = 1;
		}
		for (int k = 0;k < order;k++) {
			if (A.matrix[k][k] == 0) {
				for (int j = k+1;j < order;j++) {
					if (A.matrix[j][k] != 0) {
						A.swap(k, j);
						E.swap(k, j);
						break;
					}
				}
			}
		}
		//A.output_matrix();
		for (int i = 0;i < order;i++) {
			for (int j = 0;j < order;j++) {
				if ((i != j) && (A.matrix[j][i]!=0)) {
					T lead_el = A.matrix[i][i];
					T koef = A.matrix[j][i];
					A.matrix[i] *= koef;
					E.matrix[i] *= koef;
	
					A.matrix[j] *= lead_el;
					E.matrix[j] *= lead_el;
		
					A.matrix[j] = A.matrix[j] - A.matrix[i];
					E.matrix[j] = E.matrix[j] - E.matrix[i];
				
					A.matrix[i] /= koef;
					E.matrix[i] /= koef;
				}
			}
		}
		for (int i = 0;i < order;i++) {
			E.matrix[i] /= A.matrix[i][i];
		}
		for (int i = 0;i < order;i++) {
			for (int j = 0;j < order;j++) {
				answer[i] += (E.matrix[i][j]*b[j]);
			}
		}
		cout << "Уравнение A * x = b;" << endl<<"x = (";
		answer.output(order);
		int decision;
		cout << ")"<<endl<<endl;
		cout << "Введите 0, чтобы вывести обратную к А матрицу" << endl;
		cin >> decision;
		if (decision == 0) {
			cout << endl;
			E.output_matrix();
		}
	}
};
int main() {
	setlocale(LC_ALL, "Russian");
	int rank;
	cout << "Укажите размерность (до 10):" << endl;
	cin >> rank;
	cout << endl;
	Vector<double>A(rank);
	cout << "Введите вектор b:" << endl;
	A.input(rank);
	cout << endl;
	SLAE<double> S(rank);
	S.Gauss(A);
}