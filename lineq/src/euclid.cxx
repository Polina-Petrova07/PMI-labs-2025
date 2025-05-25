#include "euclid.hxx"
#include "checked_arith.hxx"
#include <stdexcept>
#include <utility>
using namespace std;

u64 gcd(u64 a, u64 b) {
    if (a < b) swap(a, b);
    while (b != 0) {
        uint64_t nxt = a % b;
        a = b;
        b = nxt;
    }
    return a;
}

i64 gcd(i64 a, i64 b) {
    if (a < b) swap(a, b);
    if (b == INT64_MIN) {
        if (a == INT64_MIN) return a;
        return gcd(u64(INT64_MAX/2), u64(abs(a)));
    }
    return gcd(u64(abs(a)), u64(abs(b)));
}

void reduce_by_gcd(u64& a, u64& b) {
    u64 cd = gcd(a, b);
    a /= cd;
    b /= cd;
}
void reduce_by_gcd(i64& a, i64& b) {
    i64 cd = gcd(a, b);
    a /= cd;
    b /= cd;
}

bool lcm(u64& out, u64 a, u64 b) {
    reduce_by_gcd(a, b);
    return ret_checked_mul(out, a, b);
}
bool lcm(i64& out, i64 a, i64 b) {
    reduce_by_gcd(a, b);
    return ret_checked_mul(out, a, b);
}
u64 lcm(u64 a, u64 b) {
    u64 out;
    if (!lcm(out, a, b)) throw overflow_error("least common multiple overflow");
    return out;
}
i64 lcm(i64 a, i64 b) {
    i64 out;
    if (!lcm(out, a, b)) throw overflow_error("least common multiple overflow");
    return out;
}
