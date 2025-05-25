#include "header.h"
void locale(void) {
	char* locale = setlocale(LC_ALL, "");
}
void print(void) {
	std::cout << "Введите количество уравнений системы линейных уравнений\n";
	int size;
	std::cin >> size;
	std::cout << "Введите коэффициенты системы линейных уравнений построчно\n";
	SLAE<double> m1;
	m1.setMatrix(size);
	int choice = 1;
	while (choice == 1) {
		if (choice ==1) { 
			std::cout << "Введите значение правой части системы линейных уравнений\n";
			my_vector<double> v1;
			v1.setVector(size);
			my_vector<double> v2 = m1.gauss_solve(v1);
			std::cout << "Ответ: ";
			v2.print();
		}
		std::cout << "Хотите решить систему линейных уранений с ещё раз другой правой частью?\n1.Да\t2.Нет\n";
		std::cin >> choice;
	}
}