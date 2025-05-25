#pragma once
#include "abbrev.hxx"

[[nodiscard]] u64  gcd          (u64  a, u64  b);
[[nodiscard]] i64  gcd          (i64  a, i64  b);
              void reduce_by_gcd(u64& a, u64& b);
              void reduce_by_gcd(i64& a, i64& b);
              bool lcm          (u64& out, u64 a, u64 b);
              bool lcm          (i64& out, i64 a, i64 b);
[[nodiscard]] u64  lcm          (u64 a, u64 b);
[[nodiscard]] i64  lcm          (i64 a, i64 b);
