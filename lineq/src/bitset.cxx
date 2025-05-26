#include "bitset.hxx"
#include "checked_arith.hxx"
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

bitset::bitset(size_t num_bits, bool zero_mem)
    : arr(new u8[(checked_add(num_bits, size_t(7))) >> 3]), n_b(num_bits)
    { if (zero_mem) memset(arr, 0, n_bytes()); }
bitset::bitset(bitset const& o) {
    bitset n {o.n_b, false};
    memcpy(n.arr, o.arr, o.n_bytes());
    *this = std::move(n);
}

ostream& operator<<(ostream& o, bitset const& b) {
    for (size_t i = 0; o.good() && i < b.n_bits(); i++) o << unsigned(b[i]);
    return o;
}
