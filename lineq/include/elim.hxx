#pragma once
#include "abbrev.hxx"
#include "fwd.hxx"

// elim_rowcol treats the element at the given index of the given source row as the pivot and
// subtracts a multiple of the source row from the destination row such that the element with
// that index in the destination row becomes zero, returning false if overflow is encountered

template<bool hs>
bool elim_rowcol(vec<i64, hs> dst, vec<i64 const, hs> src, size_t col);
template<bool hs>
bool elim_rowcol(vec<f64, hs> dst, vec<f64 const, hs> src, size_t col);
