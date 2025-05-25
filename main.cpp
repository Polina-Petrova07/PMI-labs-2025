#include "SLU.h"
int main() {
	
	int s = 0;
	std::cout << "Insert matrix size\n";
	std::cin >> s;
	Matrix<double> a(s);
	vector<double> r_p(s);
	std::cin >> a;
	std::cout << "\nInsert right part\n";
	for (int i = 0; i < s; i++)
	{
		std::cin >> r_p[i];
	}

	std::cout << "\n";
	SLU<double> A(a);
 	A.Gaus(r_p);
	std::cout << "answer:\n";
	for (int i = 0; i < s; i++)
	{
		std::cout << r_p[i]<<" ";
	}
	return 0;
}