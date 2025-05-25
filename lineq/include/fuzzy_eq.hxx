#pragma once
#include <cmath>
#include "abbrev.hxx"
inline bool fuzzy_eq_zero(f64 v) { return v == 0 || std::fabs(v) < 1e-14; }
inline bool fuzzy_eq_zero(i64 v) { return v == 0                        ; }
