#pragma once
#include "fwd.hxx"
#include "vec.hxx"
#include <iosfwd>

struct mat_coord final { size_t row, col; };

// ======
// Specialization-based dispatch of matrix indexing to strideful and strideless vector types
template<typename T, mat_maj maj> struct row_tpl {};
template<typename T, mat_maj maj> struct col_tpl {};
template<typename T, mat_maj maj> using row_vec = typename row_tpl<T, maj>::tvec;
template<typename T, mat_maj maj> using col_vec = typename col_tpl<T, maj>::tvec;

template<typename T> struct row_tpl<T, mat_maj::row> {
    using tvec = vec<T, false>;
private:
    using tmat = mat<T, mat_maj::row>; friend tmat;
    static tvec row(tmat& m, size_t i) noexcept { return tvec(m.row_ptr(i), m.n_cols()); }
};
template<typename T> struct row_tpl<T, mat_maj::col> {
    using tvec = vec<T, true>;
private:
    using tmat = mat<T, mat_maj::col>; friend tmat;
    static tvec row(tmat& m, size_t i) noexcept
        { return tvec(m.row_ptr(i), m.n_cols(), m.col_stride()); }
};

template<typename T> struct col_tpl<T, mat_maj::row> {
    using tvec = vec<T, true>;
private:
    using tmat = mat<T, mat_maj::row>; friend tmat;
    static tvec col(tmat& m, size_t i) noexcept
        { return tvec(m.col_ptr(i), m.n_rows(), m.row_stride()); }
};
template<typename T> struct col_tpl<T, mat_maj::col> {
    using tvec = vec<T, false>;
private:
    using tmat = mat<T, mat_maj::col>; friend tmat;
    static tvec col(tmat& m, size_t i) noexcept { return tvec(m.col_ptr(i), m.n_rows()); }
};
// End of dispatch of matrix indexing to strideful and strideless vector types
// ======

template<typename T, mat_maj maj> struct mat final {
private:
    T*     elems{};
    size_t rows {};
    size_t cols {};

public:
    mat() noexcept = default;
    
    template<typename SF = T>
    mat(T* elems, size_t rows, size_t cols) noexcept // NOLINT (easily swapped)
        : elems(elems), rows(rows), cols(cols) {}

    [[nodiscard]] mat<T const, maj> to_const()  const noexcept
        { return mat<T const, maj>(elems, rows, cols); }
    [[nodiscard]] operator mat<T const, maj>()  const noexcept { return to_const()             ; }

    [[nodiscard]] mat<T, maj_transpose<maj>> transpose() const noexcept
        { return mat(elems, rows, cols); }

    [[nodiscard]] size_t row_stride()           const noexcept {return(maj==mat_maj::row)?cols:1;}
    [[nodiscard]] size_t col_stride()           const noexcept {return(maj==mat_maj::col)?rows:1;}
    [[nodiscard]] size_t row_idx   (size_t row) const noexcept {return row * row_stride()       ;}
    [[nodiscard]] size_t col_idx   (size_t col) const noexcept {return col * col_stride()       ;}
    [[nodiscard]] T*     row_ptr   (size_t row) const noexcept {return elems + row_idx(row)     ;}
    [[nodiscard]] T*     col_ptr   (size_t col) const noexcept {return elems + col_idx(col)     ;}

    [[nodiscard]] row_vec<T const, maj> row(size_t row) const noexcept {
        return row_tpl<T const, maj>::row(*this, row);
    }
    [[nodiscard]] col_vec<T const, maj> col(size_t col) const noexcept {
        return col_tpl<T const, maj>::col(*this, col);
    }
    [[nodiscard]] row_vec<T, maj> row(size_t row)noexcept{return row_tpl<T,maj>::row(*this, row);}
    [[nodiscard]] col_vec<T, maj> col(size_t col)noexcept{return col_tpl<T,maj>::col(*this, col);}

    [[nodiscard]] row_vec<T const, maj> operator[](size_t i) const noexcept { return row(i); } 
    [[nodiscard]] row_vec<T      , maj> operator[](size_t i)       noexcept { return row(i); } 

    [[nodiscard]] size_t n_rows() const noexcept { return rows; }
    [[nodiscard]] size_t n_cols() const noexcept { return cols; }
};

template<mat_maj md, mat_maj ms> void convert_mat_frac(mat<i64, md> dst, mat<frac const, ms> src);
template<mat_maj md, mat_maj ms> void convert_mat_frac(mat<f64, md> dst, mat<frac const, ms> src);

template<typename T, mat_maj maj>
std::ostream& operator<<(std::ostream& o, mat<T, maj> m);

template<typename T, mat_maj maj>
void print_mat_with_split(std::ostream& o, mat<T, maj> m, size_t split);
