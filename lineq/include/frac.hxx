#pragma once
#include "euclid.hxx"
#include "fwd.hxx"
#include <stdexcept>

struct frac final {
private:
    i64 fn;
    u64 fd;
public:
    frac(i64 n = 0, u64 d = 1) : fn(n), fd(d) // NOLINT obvious
        { if (d == 0) throw std::range_error("denominator may not be zero"); }

    [[nodiscard]] u64 denlcm(frac o) const          { return lcm(fd, o.fd); }
    [[nodiscard]] i64 n     ()       const noexcept { return fn           ; }
    [[nodiscard]] u64 d     ()       const noexcept { return fd           ; }
};

template<bool ihs, bool ohs>
void equalize_and_drop_row_denom(vec<frac const, ihs> in, vec<i64, ohs> out);

std::ostream& operator<<(std::ostream& o, frac  f);
std::istream& operator>>(std::istream& i, frac& f);
