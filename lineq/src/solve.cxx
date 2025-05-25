#include "bitset.hxx"
#include "checked_arith.hxx"
#include "elim.hxx"
#include "fuzzy_eq.hxx"
#include "mat.hxx"
#include "solve.hxx"
#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

solution_traces::solution_traces() noexcept { new(this) solution_traces(0, 0); } // NOLINT, pnew

solution_traces::solution_traces(size_t rows, size_t cols)
    : _rows(rows), _cols(cols),
      _pivots((cols != 0) ? new mat_coord[cols] : nullptr),
      _f_vars_and_0_rows((checked_add(rows, cols) != 0) ? new size_t[cols + rows] : nullptr),
      _num_pivots(0), _num_free_vars(0), _num_0_rows(0) {}

solution_traces::solution_traces(solution_traces&& o) noexcept
    : _rows(o._rows), _cols(o._cols), _pivots(o._pivots),
      _f_vars_and_0_rows(o._f_vars_and_0_rows), _num_pivots(o._num_pivots),
      _num_free_vars(o._num_free_vars), _num_0_rows(o._num_0_rows)
    { new(&o) solution_traces(); }
solution_traces& solution_traces::operator=(solution_traces&& o) noexcept {
    if (this == &o) return *this;
    this->~solution_traces(); new(this) solution_traces(std::move(o)); return *this;
}

solution_traces::~solution_traces()
    { delete[] _pivots; delete[] _f_vars_and_0_rows; new(this) solution_traces(); }

template<bool hs> static size_t select_pivot(vec<f64, hs> v, bitset const& pivots) {
    return v.idx_fold([&](size_t acc, size_t i) {
        if (pivots[i]||fuzzy_eq_zero(v[i]) || acc!=SIZE_MAX && fabs(v[acc])>fabs(v[i]))return acc;
        return i;
    });
}
template<bool hs> static size_t select_pivot(vec<i64, hs> v, bitset const& pivots) {
    return v.idx_fold([&](size_t acc, size_t i) {
        if (pivots[i] || v[i] == 0 || acc != SIZE_MAX && v[acc] < v[i]) return acc;
        return i;
    });
}

template<typename T> constexpr bool elim_can_overflow      = false;
template<>           constexpr bool elim_can_overflow<i64> = true;

template<bool hs>
static void elim(vec<i64, hs> dst, vec<i64, hs> src, size_t col) {
    if (!elim_rowcol(dst, src.to_const(), col))
        throw overflow_error("overflow during Gaussian elimination");
}
template<bool hs>
static void elim(vec<f64, hs> dst, vec<f64, hs> src, size_t col)
    { elim_rowcol(dst, src.to_const(), col); }


template<typename T, mat_maj maj>
solution_traces gauss_jordan(mat<T, maj> m, size_t split, bool verbose) {
    if (split > m.n_cols()) throw range_error("matrix split out of bounds");

    solution_traces traces {m.n_rows(), m.n_cols()};
    bitset          pivots {m.n_cols()};
    size_t end = min(m.n_rows(), split);

    for (size_t col = 0; col < end; col++) {
        size_t pivot_row = select_pivot(m.col(col), pivots);
        if (pivot_row == SIZE_MAX) {
            // No pivot found for this column – we have a free variable
            traces.free_vars()[traces._num_free_vars++] = col;
            if (verbose) cerr << "solver: column " << col << " is a free variable\n";
            continue;
        }

        if (verbose)
            cerr << "solver: selected row " <<pivot_row+1<< " column " <<col+1<< " as pivot\n";

        traces.pivots()[traces._num_pivots++] = {pivot_row, col};
        pivots[pivot_row] = true; // Don't use this row for pivots in the future

        for (size_t row = 0;         row<pivot_row ; row++) elim(m.row(row),m.row(pivot_row),col);
        for (size_t row=pivot_row+1; row<m.n_rows(); row++) elim(m.row(row),m.row(pivot_row),col);

        if (verbose) {
            cerr << "solver: matrix state at column " << col + 1 << ":\n";
            print_mat_with_split(cerr, m, split);
        }
    }

    // If we don't have enough equations, all remaining variables are free
    for (size_t c = m.n_rows(); c < split; c++) traces.free_vars()[traces._num_free_vars++] = c;

    for (size_t r = 0; r < m.n_rows(); r++) {
        size_t idx = m.row(r).first_nonzero_idx();
        // If there are non-zero elements in a row but all of them are to the right of the split,
        // some of the right-hand sides form unsatisfiable equations, and in those columsn to
        // the right of the split where the element at a zeroed row is non-zero, the system of
        // equations is unsatisfiable.
        if (idx != SIZE_MAX && idx >= split) traces.zeroed_rows()[traces._num_0_rows++] = r;
    };

    if (verbose) cerr << "solver: finished with " << traces.num_free_vars() << " free variables and "
         << traces.num_0_rows() << " rows with unsatisfiable equations\n";
    return traces;
}

// Explicit instantiation
template solution_traces gauss_jordan<f64, mat_maj::row>(mat<f64, mat_maj::row>, size_t, bool);
template solution_traces gauss_jordan<f64, mat_maj::col>(mat<f64, mat_maj::col>, size_t, bool);
template solution_traces gauss_jordan<i64, mat_maj::row>(mat<i64, mat_maj::row>, size_t, bool);
template solution_traces gauss_jordan<i64, mat_maj::col>(mat<i64, mat_maj::col>, size_t, bool);
