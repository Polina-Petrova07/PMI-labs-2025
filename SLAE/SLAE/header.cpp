#include "header.h"
void locale(void) {
	char* locale = setlocale(LC_ALL, "");
}
void print(void) {
	std::cout << "������� ���������� ��������� ������� �������� ���������\n";
	int size;
	std::cin >> size;
	std::cout << "������� ������������ ������� �������� ��������� ���������\n";
	SLAE<double> m1;
	m1.setMatrix(size);
	int choice = 1;
	while (choice == 1) {
		if (choice ==1) { 
			std::cout << "������� �������� ������ ����� ������� �������� ���������\n";
			my_vector<double> v1;
			v1.setVector(size);
			my_vector<double> v2 = m1.gauss_solve(v1);
			std::cout << "�����: ";
			v2.print();
		}
		std::cout << "������ ������ ������� �������� �������� � ��� ��� ������ ������ ������?\n1.��\t2.���\n";
		std::cin >> choice;
	}
}