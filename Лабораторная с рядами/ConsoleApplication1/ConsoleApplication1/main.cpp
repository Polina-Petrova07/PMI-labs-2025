#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <iostream>
#include <iomanip>


 long double Sin(int n, long double x, long double *mas) {
	mas[0] = x;
	for (int i = 1; i < n; i++) {
		mas[i] = long double(((-x * x) / ((2 * i) * (2 * i + 1))) * mas[i-1]);
	}
	return long double(sin(x));
}

long double Cos(int n, long double x, long double *mas) {
	mas[0] = 1.0;
	for (int i = 1; i < n; i++) {
		mas[i] = long double((-1) * ((x * x) / ((2 * i - 1) * (2 * i))) * mas[i - 1]);
	}
	return long double(cos(x));
}

long double logarifm(int n, long double x, long double* mas) {
	mas[0] = x;
	for (int i = 1; i < n; i++) {
		mas[i] = long double((-1) * x * i / (i+1) * mas[i - 1]);
	}
	return long double(log(1 + x));
}

long double Exp(int n, long double x, long double* mas) {
	mas[0] = 1.0;
	for (int i = 1; i < n; i++) {
		mas[i] = long double(x/i * mas[i - 1]);
	}
	return long double(exp(x));
}

long double direct_summation(int n, long double x, long double* mas) {
	long double sum = 0.0;
	for (int i = 0; i < n; i++) {
		sum += mas[i];
	}
	return long double(sum);
}

long double reverse_summation(int n, long double x, long double* mas) {
	long double sum = 0.0;
	for (int i = n-1; i >= 0; i--) {
		sum += mas[i];
	}
	return sum;
}
typedef long double (*CompleteFunction)(int count, long double x, long double *mas);
typedef long double (*TypeSummation)(int count, long double x, long double* mas);

int main() {
	setlocale(LC_ALL, "Rus");
	long double x;
	int fun_type;
	int sum_type;
	int count;
	long double value;
	CompleteFunction mas_function[] = { Sin, Cos, logarifm, Exp };
	TypeSummation mas_type_sum[] = { direct_summation, reverse_summation };
	while (true){
		long double sum = 0.0;
		printf("Выберите фукнцию:\n1.sin x\n2.cos x\n3.ln(1+x)\n4.e^x\n");
		while (true) {
			scanf_s("%i", &fun_type);
			if ((fun_type <= 4) and (fun_type >= 1)) {
				break;
			}
			printf("Ввдите число от 1 до 4:");
		}
		printf("Выберите тип суммирования:\n1.Прямое суммирование\n2.Обратное суммирование\n");
		while (true) {
			scanf_s("%i", &sum_type);
			if ((sum_type <= 2) and (sum_type >= 1)) {
				break;
			}
			printf("Ввдите число от 1 до 2:");
		}
		printf("Введите кол-во слагаемых в ряде: ");
		scanf_s("%i", &count);
		printf("Введите аргумент: ");
		scanf_s("%Lf", &x);
		long double* arr = (long double*)malloc(count * sizeof(long double));
		value = mas_function[fun_type - 1](count, x, arr);
		sum = mas_type_sum[sum_type - 1](count, x, arr);

		std::cout << std::setprecision(30) << "Истинное значение: " << value<<"\n";
		std::cout << std::setprecision(30) << "Значение, полученное с помощью ряда Тейлора при "<<count<<" слагаемых: " << sum << "\n";
		printf("Погрешность: %.30Lf %\n", abs(value - sum) / value * 100);
	}
}

