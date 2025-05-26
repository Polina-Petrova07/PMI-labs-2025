#include "elim.hxx"
#include "euclid.hxx"
#include "checked_arith.hxx"
#include "vec.hxx"
#include <stdexcept>
using namespace std;

static void assert_len_eq(size_t la, size_t lb)
    { if (la != lb) throw logic_error("vector length mismatch"); }

static bool int_do_elem(i64& dst, i64 src, i64 dstfac, i64 srcfac){// NOLINT
    i64 dstm, srcm; // new_dst = old_dst * dstfac - src * srcfac
    return ret_checked_mul(dstm, dst , dstfac)
        && ret_checked_mul(srcm, src , srcfac)
        && ret_checked_sub(dst , dstm, srcm  );
}

template<bool hs>
static size_t int_fwd_loop(
    vec<i64, hs>& dst, vec<i64 const, hs> const& src,
    i64 dstfac, i64 srcfac, size_t start, size_t end) { // NOLINT I'm consistent with it
    size_t i;
    for (i = start; i < end; i++) if (!int_do_elem(dst[i], src[i], dstfac, srcfac)) break; 
    return i;
}

static void int_undo_elem(i64& dst, i64 src, i64 dstfac, i64 srcfac)
    { dst = (dst + src * srcfac) / dstfac; } // solve above equation for old_dst

template<bool hs>
static void int_bwd_loop(
    vec<i64, hs>& dst, vec<i64 const, hs> const& src,
    i64 dstfac, i64 srcfac, size_t start, size_t failpoint) { // NOLINT same here
    for (size_t i = failpoint; i > start; i--) int_undo_elem(dst[i-1], src[i-1], dstfac, srcfac);
}

template<bool hs> bool elim_rowcol(vec<i64, hs> dst, vec<i64 const, hs> src, size_t col) {
    assert_len_eq(dst.len(), src.len());

    i64 dstfac = src[col], srcfac = dst[col];
    reduce_by_gcd(dstfac, srcfac);

    // perform elimination before the pivot (undoing and bailing on overflow), do it again after,
    // then zero out destination at the pivot index if all goes well
    size_t reached = int_fwd_loop(dst, src, dstfac, srcfac, 0, col);
    if(reached!=col)      { int_bwd_loop(dst,src,dstfac,srcfac, 0, reached);       return false; }
    reached        = int_fwd_loop(dst, src, dstfac, srcfac, col + 1, dst.len());
    if(reached!=dst.len()){ int_bwd_loop(dst,src,dstfac,srcfac, col + 1, reached); return false; }
    dst[col] = 0;
    return true;
}
template bool elim_rowcol<false>(vec<i64, false>, vec<i64 const, false>, size_t);
template bool elim_rowcol< true>(vec<i64,  true>, vec<i64 const,  true>, size_t);

template<bool hs> bool elim_rowcol(vec<f64, hs> dst, vec<f64 const, hs> src, size_t col) {
    assert_len_eq(dst.len(), src.len());
    f64 srcfac = dst[col] / src[col];
    for (size_t i = 0      ; i < col      ; i++) dst[i] -= src[i] * srcfac;
    dst[col] = 0;
    for (size_t i = col + 1; i < dst.len(); i++) dst[i] -= src[i] * srcfac;
    return true;
}
template bool elim_rowcol<false>(vec<f64, false>, vec<f64 const, false>, size_t);
template bool elim_rowcol< true>(vec<f64,  true>, vec<f64 const,  true>, size_t);
