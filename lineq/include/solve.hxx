#pragma once
#include "mat.hxx"

struct solution_traces;
template<typename T, mat_maj maj>
solution_traces gauss_jordan(mat<T, maj> m, size_t split, bool verbose = false);

struct solution_traces {
private:
    size_t     _cols             ;
    size_t     _rows             ;
    mat_coord* _pivots           ;
    size_t     _num_pivots       ;
    size_t*    _f_vars_and_0_rows;
    size_t     _num_free_vars    ;
    size_t     _num_0_rows       ;

public:
    solution_traces() noexcept;
    solution_traces(size_t rows, size_t cols);

    [[nodiscard]] mat_coord* pivots       () const noexcept { return _pivots                   ; }
    [[nodiscard]] size_t*    free_vars    () const noexcept { return _f_vars_and_0_rows        ; }
    [[nodiscard]] size_t*    zeroed_rows  () const noexcept { return _f_vars_and_0_rows + _cols; }
    [[nodiscard]] size_t     num_pivots   () const noexcept { return _num_pivots               ; }
    [[nodiscard]] size_t     num_free_vars() const noexcept { return _num_free_vars            ; }
    [[nodiscard]] size_t     num_0_rows   () const noexcept { return _num_0_rows               ; }

    solution_traces(solution_traces const& o) = delete;
    solution_traces(solution_traces&& o) noexcept;
    solution_traces& operator=(solution_traces const& o) = delete;
    solution_traces& operator=(solution_traces&& o) noexcept;
    ~solution_traces();

private:
    template<typename T, mat_maj maj>
    friend solution_traces gauss_jordan(mat<T, maj>, size_t, bool);
};
