#include <iostream>
#include <iomanip>

template <typename T>
class vector {
public:
	unsigned int len;
	T* arr;
	vector() {
		this->len = 0;
		this->arr = nullptr;
	}
	vector(int l, T* a) {
		this->len = l;
		this->arr = new T[l];
		for (int i = 0; i < l; i++) { this->arr[i] = a[i]; }
	}
	vector(const vector<T>& x) {
		this->len = x.len;
		this->arr = new T[x.len];
		for (int i = 0; i < x.len; i++) { this->arr[i] = x.arr[i]; }
	}
	~vector() {
		if (this->len != 0 && this->arr != nullptr) {
			delete[] arr;
			arr = nullptr;
			this->len = 0;
		}
	}
	T* operator [] (int i) { return &this->arr[i]; }
	void operator () (int l, T* &a) {
		delete[] arr;
		this->len = l;
		this->arr = new T[l];
		for (int i = 0; i < l; i++) { this->arr[i] = a[i]; }
	}
};

template <typename T>
class matrix :public vector<vector<T>> {};

template <typename T>
class CLY :public matrix<T> {
public:
	CLY(int l, vector<T>* a) {
		this->len = l;
		this->arr = new vector<T>[l];
		for (int i = 0; i < l; i++) { this->arr[i](l, a[i].arr); }
	}

	void eliminate_row(int Y, int X, vector<double>*& arr, double* V) {
		double k;
		for (int i = Y + 1; i < this->len; i++) {
			if (*arr[Y][X] != 0) {
				k = (double)(*arr[i][X]) / *arr[Y][X];
				for (int j = 0; j < this->len; j++) {
					*arr[i][j] -= *arr[Y][j] * k;
				}
				V[i] -= V[Y] * k;
			}
		}
	}

	vector<double> Gaussian_method(vector<T>& v_) {
		double* w = new double[this->len];
		vector<double> ans(this->len, w);

		double* V = new double[this->len];
		for (int i = 0; i < this->len; i++) { V[i] = *v_[i]; }

		vector<double>* arr = new vector<double>[this->len];
		for (int i = 0; i < this->len; i++) {
			double* q = new double[this->len];
			for (int j = 0; j < this->len; j++) { q[j] = *this->arr[i][j]; }
			arr[i](this->len, q);
		}

		for (int i = 0; i < this->len; i++) {
			for (int j = 0; j < this->len; j++) {
				if (*arr[i][j] != 0) {
					eliminate_row(i, j, arr, V);
					//std::cout << i << " " << j << " eliminate_row\n";
					//print_CLY(arr, V, this->len);
					break;
				}
			}
		}
		for (int i = this->len - 1; i >= 0; i--) {
			for (int j = 0; j < this->len; j++) {
				if (*arr[i][j] != 0) {
					ans.arr[j] = (V[i]) / *(arr[i])[j];
					for (int h = i; h >= 0; h--) {
						V[h] -= (*arr[h][j]) * ans.arr[j];
						*arr[h][j] = 0;
					}
					//std::cout << "\nx" << j + 1 << " = " << ans.arr[j] << "\n";
					//print_CLY(arr, V, this->len);
					break;
				}
			}
		}
		
		delete[] arr;
		std::cout << "\n ans = [";
		for (int i = 0; i < this->len; i++) { std::cout << "  " << ans.arr[i]; }
		std::cout << " ]\n";

		return ans;
	}
};

template <typename T>
void print_CLY(int len, vector<T>*& arr, T*& V) {
	std::cout << std::fixed << std::setprecision(3);
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			std::cout << std::setw(7) << *arr[i][j] << "  ";
		}
		std::cout << "| " << V[i];
		std::cout << "\n";
	}
	std::cout << "\n";
}

int main()
{
	int size;
	std::cout << "size of the array = ";
	std::cin >> size;

	double q;
	vector<double>* x = new vector<double>[size];
	for (int i = 0; i < size; i++) {
		double* qq = new double[size];
		for (int j = 0; j < size; j++) {
			std::cout << "x_"<<j<<"_" << i <<" = ";
			std::cin >> q;
			qq[j] = q;
		}
		x[i](size, qq);
	}

	double* v_ = new double[size];
	for (int i = 0; i < size; i++) {
		std::cout << "v_" << i << " = ";
		std::cin >> q;
		v_[i] = q;
	}
	vector<double> v (size,v_);

	CLY<double> C(size, x);
	vector<double> ddd = C.Gaussian_method(v);
	print_CLY(C.len, C.arr, v.arr);
}