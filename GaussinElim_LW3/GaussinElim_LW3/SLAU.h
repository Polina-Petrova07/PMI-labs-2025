#pragma once
#include "Matrix.h"
#include "Vector.h"

class SLAU : public Matrix<double> {
public:

    using Matrix::Matrix; // ���������� ����������� �������� ������

    Vector<double> gauss(Vector<double> rhs) {
        int n = getSize();

        // ������ ���
        for (int i = 0; i < n; ++i) {
            // ����� �������� �������� �� ������ � i-� �������
            int maxRow = i;
            for (int k = i + 1; k < n; ++k) {
                if (std::abs((*this)[k][i]) > std::abs((*this)[maxRow][i])) {
                    maxRow = k;
                }
            }

            // ����� �����
            swapRows(i, maxRow);
            rhs.swap(i, maxRow);

            double pivot = (*this)[i][i];
            if (pivot == 0.0) {
                // ��������: ��� ������ � ����, � ������ ����� �� ���� ? �����������
                bool allZero = true;
                for (int j = 0; j < n; ++j) {
                    if ((*this)[i][j] != 0.0) {
                        allZero = false;
                        break;
                    }
                }

                if (allZero && rhs[i] != 0.0) {
                    std::cerr << "������� �����������: ������ " << i << " �������� ������ ����, �� ������ ����� = " << rhs[i] << "\n";
                    exit(1);
                }
                else if (allZero && rhs[i] == 0.0) {
                    // ���������� ����� ������� � ������ ���� 0 = 0
                    std::cerr << "������� ����� ���������� ����� ������� (��������������).\n";
                    exit(1);
                }
                else {
                    std::cerr << "������� ��������� ��� ����� ����������� (pivot = 0).\n";
                    exit(1);
                }
            }

            // ������������ ������
            for (int j = i; j < n; ++j) {
                (*this)[i][j] /= pivot;
            }
            rhs[i] /= pivot;

            // �������� ������ ������
            for (int k = i + 1; k < n; ++k) {
                double factor = (*this)[k][i];
                for (int j = i; j < n; ++j) {
                    (*this)[k][j] -= factor * (*this)[i][j];
                }
                rhs[k] -= factor * rhs[i];
            }
        }

        // �������� ���
        Vector<double> result(n);
        for (int i = n - 1; i >= 0; --i) {
            result[i] = rhs[i];
            for (int j = i + 1; j < n; ++j) {
                result[i] -= (*this)[i][j] * result[j];
            }
        }

        return result;
    }
};