#include "abbrev.hxx"
#include "frac.hxx"
#include "mat.hxx"
#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace std;
#define majrow mat_maj::row
#define majcol mat_maj::col

template<mat_maj md, mat_maj ms>
void convert_mat_frac(mat<i64, md> dst, mat<frac const, ms> src) {
    if (src.n_rows() > dst.n_rows() || src.n_cols() > dst.n_cols())
        throw range_error("denominator removal destination too small");
    for (size_t i = 0; i < dst.n_rows(); i++) equalize_and_drop_row_denom(src[i], dst[i]);
}
template<mat_maj md, mat_maj ms>
void convert_mat_frac(mat<f64, md> dst, mat<frac const, ms> src) {
    if (src.n_rows() > dst.n_rows() || src.n_cols() > dst.n_cols())
        throw range_error("matrix conversion destination too small");
    for (size_t r = 0; r < dst.n_rows(); r++) for (size_t c = 0; c < dst.n_cols(); c++)
        dst[r][c] = f64(src[r][c].n()) / src[r][c].d();
}

template<typename T, mat_maj maj>
ostream& operator<<(ostream& o, mat<T, maj> m)
    { print_mat_with_split(o, m, m.n_cols()); return o; }

template<typename T, mat_maj maj>
void print_mat_with_split(ostream& o, mat<T, maj> m, size_t split) {
    for (size_t r = 0; r < m.n_rows(); r++) {
        for (size_t c = 0; c < m.n_cols(); c++) {
            if (c == split) o << "  | ";
            o << setw(6) << m[r][c];
        }
        o << '\n';
    }
}

// Explicit instantiations
template void convert_mat_frac<majrow, majrow>(mat<i64, majrow>, mat<frac const, majrow>);
template void convert_mat_frac<majrow, majcol>(mat<i64, majrow>, mat<frac const, majcol>);
template void convert_mat_frac<majcol, majrow>(mat<i64, majcol>, mat<frac const, majrow>);
template void convert_mat_frac<majcol, majcol>(mat<i64, majcol>, mat<frac const, majcol>);

template void convert_mat_frac<majrow, majrow>(mat<f64, majrow>, mat<frac const, majrow>);
template void convert_mat_frac<majrow, majcol>(mat<f64, majrow>, mat<frac const, majcol>);
template void convert_mat_frac<majcol, majrow>(mat<f64, majcol>, mat<frac const, majrow>);
template void convert_mat_frac<majcol, majcol>(mat<f64, majcol>, mat<frac const, majcol>);

template ostream& operator<<<f64 , majrow>(ostream&, mat<f64 , majrow>);
template ostream& operator<<<i64 , majrow>(ostream&, mat<i64 , majrow>);
template ostream& operator<<<frac, majrow>(ostream&, mat<frac, majrow>);
template ostream& operator<<<f64 , majcol>(ostream&, mat<f64 , majcol>);
template ostream& operator<<<i64 , majcol>(ostream&, mat<i64 , majcol>);
template ostream& operator<<<frac, majcol>(ostream&, mat<frac, majcol>);
