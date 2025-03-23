#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "functions.h"
#include "locale.h"
int main() {
	setlocale(LC_ALL, "Russian");
	int decision1; int decision2; int n; long double x;
	printf("Выберите функцию:\n1. sin x\n2. cos x\n3. e^x\n4. ln(1+x)\n>> ");
	scanf_s("%i", &decision1);
	if ((decision1 <= 0) || (decision1 >= 5)) {
		printf("\nОшибка!\n\n");
		return 0;
	}
	printf("\nВведите аргумент x\n>> ");
	scanf_s("%lf", &x);
	printf("\nВведите количество слагаемых в разложении\n>> ");
	scanf_s("%i", &n);
	if (n <= 0) {
		printf("\nОшибка!\n\n");
		return 0;
	}
	long double* arr = (long double*)malloc(n * sizeof(long double));
	printf("\nВыберете тип суммирования\n1. Прямое суммирование\n2. Обратное суммирование\n>> ");
	scanf_s("%i", &decision2);
	if ((decision2!=1) && (decision2!=2)) {
		printf("\nОшибка!\n\n");
		return 0;
	}
	decision(decision1, decision2, x, n, arr);
}