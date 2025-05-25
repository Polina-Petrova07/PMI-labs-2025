#pragma once
using namespace std;
template <typename T>
class Vector {
public:
	int size;
	T* data;
	Vector() : size(0), data(nullptr) {}

	Vector(int size_0) : size(size_0) {
		data = new T[size];
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}
	void Add_Vector() {
		for (int i = 0; i < size; i++) {
			cin >> data[i];
		}
	}

	void Print_Vector() {
		for (int i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
		cout << "\n";
	}
	void operator /=(double ratio) {
		for (int i = 0; i < size; i++) {
			if (data[i] != 0) {
				data[i] /= ratio;
			}
		}
	}
	int Size() const { return size; }

	T& operator[](int index) { return data[index]; }
};
