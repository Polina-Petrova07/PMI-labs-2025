#pragma once
#include "euclid.hxx"
#include "frac.hxx"
#include "fuzzy_eq.hxx"
#include "fwd.hxx"
#include <cstdlib>
#include <functional>
#include <iosfwd>
#include <stdexcept>
#include <type_traits>

template<bool has_stride> struct size_if_stride;
template<> struct size_if_stride<false> {
    size_if_stride(size_t) noexcept {}
    [[nodiscard]] operator size_t() const noexcept { return 1; }
};
template<> struct size_if_stride<true> {
    using stride_t = size_t;
    size_if_stride() = delete;
    size_if_stride(size_t stride) noexcept : strid(stride) {}
    [[nodiscard]] operator size_t() const noexcept { return strid; }
private:
    size_t strid;
};

template<typename T, bool has_stride>
struct vec {
    vec() noexcept : _ptr(nullptr), _len(0), _stride(1) {}
    explicit vec(T* ptr, size_t len) noexcept : _ptr(ptr), _len(len), _stride(1) {}
    explicit vec(T* ptr, size_t len, size_t stride) noexcept // NOLINT obvious
        : _ptr(ptr), _len(len), _stride(stride) {}

    [[nodiscard]] vec<T const, has_stride> to_const() const noexcept
        { return vec<T const, has_stride>(_ptr,_len); }
    [[nodiscard]] operator vec<T const, has_stride>() const noexcept { return to_const(); }
    

    [[nodiscard]] T const& operator[](size_t idx) const noexcept { return _ptr[idx * _stride]; }
    [[nodiscard]] T      & operator[](size_t idx)       noexcept { return _ptr[idx * _stride]; }
    [[nodiscard]] T*       ptr()                  const noexcept { return _ptr               ; }
    [[nodiscard]] size_t   len()                  const noexcept { return _len               ; }
    [[nodiscard]] size_t   stride()               const noexcept { return _stride            ; }

    template<typename A, typename F>
    [[nodiscard]] A range_fold(size_t start, size_t end, A acc, F f) const {
        for (size_t i = start; i < end; i++) acc = f(acc, (*this)[i]);
        return acc;
    }
    template<typename A, typename F>
    [[nodiscard]] A fold(A acc, F f) const { return range_fold(0, _len, acc, f); }

    template<typename F>
    [[nodiscard]] T fold1(F f, const char* exc = "cannot fold1 over an empty vector") const {
        if (_len == 0) throw std::range_error(exc);
        return range_fold(1, _len, (*this)[0], f);
    }

    template<typename F>
    [[nodiscard]] size_t idx_fold(F f) const
        { size_t acc = SIZE_MAX; for (size_t i = 0; i < _len; i++) acc = f(acc, i); return acc; }
    template<typename F>
    [[nodiscard]] size_t idx_fold1(
        F f, const char* exc = "cannot index-fold over an empty vector"
    ) const {
        if (_len == 0) throw std::range_error(exc);
        size_t acc = 0;
        for (size_t i = 1; i < _len; i++) acc = f(acc, i);
        return acc;
    }

    [[nodiscard]] T lcm() const
        { if (_len == 0) return 1; return fold1([&](T a, T b) { return ::lcm(a, b); }); }
    [[nodiscard]] u64 denlcm() const {
        u64 ret = (_len != 0) ? (*this)[0].d() : 1;
        for (size_t i = 1; i < _len; i++) ret = ::lcm(ret, (*this)[i].d());
        return ret;
    }

    [[nodiscard]] size_t first_nonzero_idx() const {
        for (size_t i; i < _len; i++) if (!fuzzy_eq_zero((*this)[i])) return i;
        return SIZE_MAX;
    }

private:
    friend vec<T const, has_stride>;

    T*                         _ptr;
    size_t                     _len;
    size_if_stride<has_stride> _stride;
};

template<typename T, bool hs> std::ostream& operator<<(std::ostream& o, vec<T const, hs> v);
template<typename T, bool hs> std::ostream& operator<<(std::ostream& o, vec<T      , hs> v)
    { return o << static_cast<vec<T const, hs>>(v); }
