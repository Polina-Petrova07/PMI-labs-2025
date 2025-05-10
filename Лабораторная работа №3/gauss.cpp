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
//        // §±§à§Ú§ã§Ü §Ó§Ö§Õ§å§ë§Ö§Ô§à §ï§Ý§Ö§Þ§Ö§ß§ä§Ñ §Ó §ã§ä§à§Ý§Ò§è§Ö k
//        int max_row = k;
//        T max_val = std::abs(mx[k][k]);
//        for (int i = k + 1; i < str; ++i) {
//            if (std::abs(mx[i][k]) > max_val) {
//                max_row = i;
//                max_val = std::abs(mx[i][k]);
//            }
//        }
//
//        // §±§Ö§â§Ö§ã§ä§Ñ§ß§à§Ó§Ü§Ñ §ã§ä§â§à§Ü, §Ö§ã§Ý§Ú §ß§Ö§à§Ò§ç§à§Õ§Ú§Þ§à
//        if (max_row != k) {
//            swap_rows(k, max_row);
//        }
//
//        // §±§â§ñ§Þ§à§Û §ç§à§Õ: §à§Ò§ß§å§Ý§Ö§ß§Ú§Ö §ï§Ý§Ö§Þ§Ö§ß§ä§à§Ó §ß§Ú§Ø§Ö §Ó§Ö§Õ§å§ë§Ö§Ô§à
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