#pragma once
#include "matrix.h"


template<typename T>
class SLU : public Matrix<T>
{
private:
public:

    SLU(Matrix<T>& r_p) : Matrix<T>(r_p) {};
    vector<T> Gaus(vector<T>& Right_P) {
        int n = this->get_size();
        Matrix<T> newMatrix(*this);

        for (int i = 0; i < n; ++i) {
            int maxRow = i;
            for (int k = i + 1; k < n; ++k) {
                if (fabs(newMatrix[k][i]) > fabs(newMatrix[maxRow][i])) {
                    maxRow = k;
                }
            }

            if (maxRow != i) {
                swap(newMatrix[i], newMatrix[maxRow]);
                swap(Right_P[i], Right_P[maxRow]);
            }

            if (fabs(newMatrix[i][i]) = 0) {
                return {}; 
            }
            for (int k = i + 1; k < n; ++k) {
                double factor = newMatrix[k][i] / newMatrix[i][i];
                for (int j = i; j < n; ++j) { 
                    newMatrix[k][j] -= factor * newMatrix[i][j];
                    
                }
                Right_P[k] -= factor * Right_P[i];
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                Right_P[i] -= newMatrix[i][j] * Right_P[j];
            }
            Right_P[i] /= newMatrix[i][i];
        }

        return Right_P;



    }
};
