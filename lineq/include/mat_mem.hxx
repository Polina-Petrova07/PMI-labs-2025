#pragma once
#include "fwd.hxx"
#include "checked_arith.hxx"
#include "mat.hxx"
#include <cstring>
#include <new>
#include <utility>

template<typename T, mat_maj maj> struct mat_mem final {
private:
    T *    elems {};
    size_t rows  {};
    size_t cols  {};
public:
    mat_mem() noexcept = default;
    mat_mem(size_t rows, size_t cols, bool zero_mem = true) : rows(rows), cols(cols) {
        size_t num_cells = checked_mul(rows, cols);
        elems = new T[num_cells]; // NOLINT, we own this
        if (zero_mem) zero_fill();
    }

    mat_mem(mat_mem const& o) : rows(o.rows), cols(o.cols)
        { elems = memcpy(new T[rows * cols], elems, rows * cols * sizeof(T)); }
    mat_mem(mat_mem&& o) noexcept : elems(o.elems), rows(o.rows), cols(o.cols) {
        o.elems = nullptr;
        o.rows = o.cols = 0;
    }

    mat_mem& operator=(mat_mem const& o)
        {if(this==&o)return *this; this->~mat_mem();new(this)mat_mem(o);            return *this;}
    mat_mem& operator=(mat_mem && o) noexcept
        {if(this==&o)return *this; this->~mat_mem();new(this)mat_mem(std::move(o)); return *this;}

    ~mat_mem() { delete[] elems; elems = nullptr; rows = cols = 0; }

    void zero_fill() noexcept { memset(elems, 0, rows * cols * sizeof(T)); }

    void copy_from(mat_mem<T, maj> const& other, bool zero_rest = true) & {
        // PERF doesn't vectorize if column-major
        size_t x;
        for (x = 0; x < other.cols; x++) {
            size_t y;
            for (y = 0; y < other.rows; y++) this->m()[y][x] = other.m()[y][x];
            if (zero_rest) for (; y < rows; y++) this->m()[y][x] = 0;
        }
        if (zero_rest) for(; x < cols; x++) for(size_t y = 0; y < rows; y++) this->m()[y][x] = 0;
    }
    void copy_from(mat_mem<T, maj> const& other) && = delete;

    void grow_row(bool zero_mem = true) & {
        mat_mem<T, maj> n(rows + 1, cols, zero_mem);
        n.copy_from(*this, zero_mem);
        *this = std::move(n);
    }
    void grow_row(bool zero_mem = true) && = delete;

    void grow_col(bool zero_mem = true) & {
        mat_mem<T, maj> n(rows, cols + 1, zero_mem);
        n.copy_from(*this, zero_mem);
        *this = std::move(n);
    }
    void grow_col(bool zero_mem = true) && = delete;

    [[nodiscard]] operator mat<T, maj>() const &  noexcept {return mat<T, maj>(elems,rows,cols);};
    [[nodiscard]] mat<T, maj>        m() const &  noexcept {return *this                       ;};
    [[nodiscard]] operator mat<T, maj>() const && noexcept = delete;
    [[nodiscard]] mat<T, maj>        m() const && noexcept = delete;

    [[nodiscard]] mat_mem<T, maj_transpose<maj>> transpose() && noexcept {
        auto ret = mat_mem<T, maj_transpose<maj>>();
        ret.elems = elems; ret.rows = rows; ret.cols = cols;
        elems = nullptr;   rows = cols = 0;
        return ret;
    }
};
