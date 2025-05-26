#include "abbrev.hxx"
#include "frac.hxx"
#include "vec.hxx"
#include <iostream>
#include <iomanip>
using namespace std;
using os = ostream;

template<typename T, bool hs> os& operator<<(os& o, vec<T const, hs> v) {
    for (size_t i = 0; i < v.len(); i++) o << setw(6) << v[i];
    return o;
}

template os& operator<<<f64 , false>(os&, vec<f64  const, false>);
template os& operator<<<f64 ,  true>(os&, vec<f64  const,  true>);
template os& operator<<<u64 , false>(os&, vec<u64  const, false>);
template os& operator<<<u64 ,  true>(os&, vec<u64  const,  true>);
template os& operator<<<i64 , false>(os&, vec<i64  const, false>);
template os& operator<<<i64 ,  true>(os&, vec<i64  const,  true>);
template os& operator<<<frac, false>(os&, vec<frac const, false>);
template os& operator<<<frac,  true>(os&, vec<frac const,  true>);
