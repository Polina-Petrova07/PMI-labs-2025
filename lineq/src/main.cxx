#include "frac.hxx"
#include "mat_mem.hxx"
#include "prognam.hxx"
#include "readmat.hxx"
#include "solve.hxx"
#include "print_results.hxx"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

constexpr u8 FLOATS  = 0x1;
constexpr u8 VERBOSE = 0x2;
constexpr u8 HELP    = 0x4;

static string unknown_option(char c)
    { stringstream s; s << "unknown option " << c; return s.str(); }

static void print_usage() {
    cerr << "usage: " << prognam << " [-ivh]\n\
    -f    use 64-bit floats instead of 64-bit integers\n\
    -v    print algorithm operations step-by-step\n\
    -h    print this help\n";
}

static u8 parse_args(int argc, char ** argv) {
    u8 flags = 0;
    while (argc > 0) {
        if (**argv != '-') throw runtime_error("no positional arguments are accepted");
        argv[0]++;
        char c;
        while (**argv != 0) switch (c = *(*argv)++) {
        case 'f':
            if ((flags & FLOATS) != 0) throw runtime_error("duplicate option f");
            flags |= FLOATS;
            break;
        case 'v':
            flags |= VERBOSE;
            break;
        case 'h':
            if ((flags & HELP) != 0) cerrprog << "duplicate option h\n";
            flags |= HELP;
            break;
        default: throw runtime_error(unknown_option(c));
        }
        argv++;
        argc--;
    }
    return flags;
    
}

template<typename T, mat_maj maj>
static void solve_and_print(mat<frac, maj> m, size_t split, bool verbose) {
    mat_mem<T, mat_maj::row> cm (m.n_rows(), m.n_cols(), false);
    convert_mat_frac(cm.m(), m.to_const());
    solution_traces traces = gauss_jordan(cm.m(), split, verbose);
    print_results(cout, traces, cm.m(), split);
}

template<mat_maj maj>
static void read_and_solve_and_print(bool floats, bool verbose) {
    mat_mem<frac, maj> m;
    size_t split;
    read_mat(cin, m, split);

    if (floats) solve_and_print<f64>(m.m(), split, verbose);
    else        solve_and_print<i64>(m.m(), split, verbose);
}

static void main_inner(int argc, char ** argv) {
    u8 flags = parse_args(argc, argv);
    if ((flags & HELP) != 0) { print_usage(); return; }

    mat_mem<frac, mat_maj::row> m;
    size_t split;
    read_mat(cin, m, split);

    if ((flags & FLOATS) != 0) solve_and_print<f64>(m.m(), split, (flags & VERBOSE) != 0);
    else                       solve_and_print<i64>(m.m(), split, (flags & VERBOSE) != 0);
}

int main(int argc, char ** argv) {
    if (argc != 0) (argc--, argv++);
    try { main_inner(argc, argv); }
    catch (bad_alloc& e) {
        cerrprog << e.what() << endl;
        return 2;
    }
    catch (exception& e) {
        cerrprog << e.what() << endl;
        return 1;
    }
    return 0;
}
