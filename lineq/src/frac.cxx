#include "frac.hxx"
#include "iosutil.hxx"
#include "checked_arith.hxx"
#include "vec.hxx"
#include <iostream>
#include <stdexcept>
using namespace std;

template<bool ihs, bool ohs>
void equalize_and_drop_row_denom(vec<frac const, ihs> in, vec<i64, ohs> out) {
    if (in.len() < out.len()) throw range_error("output storage too small");
    u64 lcm = in.denlcm();
    for (size_t i = 0; i < out.len(); i++) out[i] = checked_mul(in[i].n(), i64(lcm / in[i].d()));
}

ostream& operator<<(ostream& o, frac f) {
    o << f.n();
    if (!o) return o;
    if (f.d() != 1) o << '/' << f.d();
    return o;
}

static bool read_minus(istream& i) {
    eat_pad(i);
    char c = i.peek();
    if (i && c == '-') {
        i.get();
        eat_pad(i);
        return true;
    }
    return false;
}
static void read_part(istream& i, i64& o, i8& decexp) { // NOLINT
    auto failbit = istream::failbit;
    i64 t_o      = o      = 0;
    i8  t_decexp = decexp = 0;
    bool neg = read_minus(i);
    bool had_point = false;
    for (char c = i.peek(); i.good(); i.get(), c = i.peek()) {
        if (c == '.' || c == ',') {
            if (had_point) {
                i.setstate(failbit);
                return;
            }
            had_point = true;
            continue;
        }
        if (isdigit(c) == 0) break;
        if (!ret_checked_mul(t_o, t_o, i64(10)) || !ret_checked_add(t_o, t_o, i64(c - '0'))) {
            i.setstate(failbit);
            return;
        }
        if (had_point) decexp--;
    }
    o      = (neg) ? -t_o : t_o;
    decexp = t_decexp;
}
static u64 ten_to_the_power_of(u8 pow) {
    i64 rslt = 1;
    for (; pow != 0; pow--) rslt *= 10;
    return rslt;
}
static bool resolve_point(i64& n, i64& d, i8 nde, i8 dde) { // NOLINT
    i8 de = nde - dde;
    bool ok = true;
    if (de < 0) ok = ret_checked_mul(d, d, i64(ten_to_the_power_of(-de)));
    else        ok = ret_checked_mul(n, n, i64(ten_to_the_power_of( de)));
    return ok;
}
static bool read_solidus(istream& i) {
    throw_only_bad tob {i};
    char c = i.peek();
    bool ret = i && i.peek() == '/';
    if (ret) i.get();
    return ret;
}
static frac nodenom(i64 n, i8 nde) { return {n, ten_to_the_power_of(-nde)}; }

istream& operator>>(istream& i, frac& f) {
    f = {};
    i64 n   = 0, d   = 1;
    i8  nde = 0, dde = 0;
    read_part(i, n, nde);
    eat_pad(i);

    if (!i.good() || !read_solidus(i)) {
        if (!i.bad()) f = nodenom(n, nde);
        return i;
    }

    read_part(i, d, dde);
    if (!i.good()) return i;

    if (d < 0) {
        n = -n;
        d = -d;
    }
    if (!resolve_point(n, d, nde, dde)) {
        i.setstate(istream::failbit);
        return i;
    };

    f = frac(n, d);
    return i;
}

// Explicit instantiations
template void equalize_and_drop_row_denom<false, false>(vec<frac const, false>, vec<i64, false>);
template void equalize_and_drop_row_denom<false,  true>(vec<frac const, false>, vec<i64,  true>);
template void equalize_and_drop_row_denom< true, false>(vec<frac const,  true>, vec<i64, false>);
template void equalize_and_drop_row_denom< true,  true>(vec<frac const,  true>, vec<i64,  true>);
