//#include "gauss.h"
//
//template <class T>
//void SLU<T>::swap_rows(int row1, int row2) {
//    vector<T> temp = mx[row1];
//    mx[row1] = mx[row2];
//    mx[row2] = temp;
//
//    T temp_b = b[row1];
//    b[row1] = b[row2];
//    b[row2] = temp_b;
//}
//template <class T>
//void SLU<T>::gaussian_elimination() {
//    for (int k = 0; k < str; ++k) {
//        // ����ڧ�� �ӧ֧է��֧ԧ� ��ݧ֧ާ֧ߧ�� �� ����ݧҧ�� k
//        int max_row = k;
//        T max_val = std::abs(mx[k][k]);
//        for (int i = k + 1; i < str; ++i) {
//            if (std::abs(mx[i][k]) > max_val) {
//                max_row = i;
//                max_val = std::abs(mx[i][k]);
//            }
//        }
//
//        // ���֧�֧��ѧߧ�ӧܧ� ������, �֧�ݧ� �ߧ֧�ҧ��էڧާ�
//        if (max_row != k) {
//            swap_rows(k, max_row);
//        }
//
//        // �����ާ�� ����: ��ҧߧ�ݧ֧ߧڧ� ��ݧ֧ާ֧ߧ��� �ߧڧا� �ӧ֧է��֧ԧ�
//        for (int i = k + 1; i < str; ++i) {
//            T factor = mx[i][k] / mx[k][k];
//            for (int j = k; j < str; ++j) {
//                mx[i][j] -= factor * mx[k][j];
//            }
//            b[i] -= factor * b[k];
//        }
//    }
//}
//template <class T>
//void SLU<T>::back_substitution() {
//    for (int i = str - 1; i >= 0; --i) {
//        x[i] = b[i];
//        for (int j = i + 1; j < str; ++j) {
//            x[i] -= mx[i][j] * x[j];
//        }
//        x[i] /= mx[i][i];
//    }
//}