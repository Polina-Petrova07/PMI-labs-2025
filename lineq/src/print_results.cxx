#include "print_results.hxx"
#include "fuzzy_eq.hxx"
#include "solve.hxx"
#include <iostream>
#include <sstream>
using namespace std;
#define majrow mat_maj::row
#define majcol mat_maj::col

static size_t pivot_row_of_var(solution_traces const& traces,size_t var) {
    size_t rslt = SIZE_MAX;
    for (size_t i = 0; i < traces.num_pivots(); i++)
        if (traces.pivots()[i].col == var) { rslt = traces.pivots()[i].row; break; }
    return rslt;
}

template<typename T, mat_maj maj>
static string collect_indeps( // NOLINT cog. comp.
    solution_traces const& traces, mat<T, maj> m, size_t split
) {
    stringstream s;
    for (size_t ifv = 0; ifv < traces.num_free_vars(); ifv++) {
        size_t fv = traces.free_vars()[ifv];
        s << " + t";
        if (traces.num_free_vars() > 1) s << ifv + 1;
        s << " * ";
        if (split > 1) s << '[';
        const char* spac = "";
        for (size_t v = 0; v < split; v++) {
            s << spac;
            if (v == fv) s << '1';
            else {
                size_t row = pivot_row_of_var(traces, v);
                if (row == SIZE_MAX) s << '0';
                else {
                    auto val = m[row][fv];
                    s << ((val != 0) ? -val : val); // avoid negative zero
                }
            }
            spac = " ";
        }
        if (split > 1) s << ']';
    }
    return s.str();
}

template<typename T, mat_maj maj>
static bool is_unsatisfiable(solution_traces const& traces, mat<T, maj> m, size_t ei) {
    // If the right-hand side of a zeroed row is non-zero, the equation is unsatisfiable.
    for (size_t i = 0; i < traces.num_0_rows(); i++)
        if (!fuzzy_eq_zero(m[traces.zeroed_rows()[i]][ei])) return true;
    return false;
}

static void print_pivots(ostream& o, solution_traces const& traces) {
    cerr << "pivots: ";
    for (size_t i = 0; i < traces.num_pivots(); i++) {
        auto pivot = traces.pivots()[i];
        o << pivot.row + 1 << ',' << pivot.col + 1 << ' ';
    }
    cerr << '\n';
}

static void print_div(ostream& o, f64 a, f64 b) { o << a / b; }
static void print_div(ostream& o, i64 a, i64 b) {
    if (b < 0) { a = -a; b = -b; }
    reduce_by_gcd(a, b);
    o << frac(a, b);
}

template<typename T, mat_maj maj>
void print_results(ostream& o, solution_traces const& traces, mat<T, maj> m, size_t split) {
    string indeps = collect_indeps(traces, m, split);
    for (size_t ei = split; ei < m.n_cols(); ei++) {
        size_t eqn = ei - split + 1;
        if (m.n_cols() - split > 1) o << "equation " << eqn << ": ";

        if (is_unsatisfiable(traces, m, ei)) {
            o << "no solutions\n";
            continue;
        }
        
        o << "x = ";

        // FIXME this should be a check for whether the free variable vectors form a basis
        if (split == 1 && traces.num_free_vars() == 1) {
            o << "any number\n";
            continue;
        }
        
        if (split > 1) o << '[';
        const char* spac = "";
        for (size_t v = 0; v < split; v++) {
            o << spac;
            size_t row = pivot_row_of_var(traces, v);
            if (row == SIZE_MAX) o << '0';
            else print_div(o, m[row][ei], m[row][v]);
            spac = " ";
        }
        if (split > 1) o << ']';
        o << indeps << '\n';
    }
}

// Explicit instantiation
template void print_results<f64,majrow>(ostream&,solution_traces const&,mat<f64,majrow>,size_t);
template void print_results<f64,majcol>(ostream&,solution_traces const&,mat<f64,majcol>,size_t);
template void print_results<i64,majrow>(ostream&,solution_traces const&,mat<i64,majrow>,size_t);
template void print_results<i64,majcol>(ostream&,solution_traces const&,mat<i64,majcol>,size_t);
