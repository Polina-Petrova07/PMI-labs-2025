#pragma once
#include "abbrev.hxx"
#include <iosfwd>
#include <new>
#include <utility>

struct bit_ref_mut;
struct bit_ref final {
    bit_ref(bool const* ptr) : ptr(reinterpret_cast<u8 const*>(ptr)), offset(0) {}
    bit_ref(u8 const* bitset, size_t bit) : ptr(bitset + (bit >> 3U)), offset(bit & 7U) {}

    bit_ref(bit_ref const& o)            = delete;
    bit_ref(bit_ref&&      o)            = delete;
    bit_ref& operator=(bit_ref const& o) = delete;
    bit_ref& operator=(bit_ref&&      o) = delete;
    ~bit_ref() = default;

    [[nodiscard]] operator bool() const noexcept { return bool(((*ptr) >> offset) & 1); }
private:
    bit_ref(u8 const* ptr, size_t offset, bool) : ptr(ptr), offset(offset) {}
    friend bit_ref_mut;

    u8 const* ptr;
    u8        offset;
};
struct bit_ref_mut final {
    bit_ref_mut(bool* ptr) : ptr(reinterpret_cast<u8*>(ptr)), offset(0) {}
    bit_ref_mut(u8* bitset, size_t bit) : ptr(bitset + (bit >> 3U)), offset(bit & 7U) {}

    bit_ref_mut(bit_ref_mut const& o) = delete;
    bit_ref_mut(bit_ref_mut&& o) = delete;
    ~bit_ref_mut() = default;

    [[nodiscard]] operator bool() const noexcept { return bool(((*ptr) >> offset) & 1); }
    bit_ref_mut& operator=(bool val) noexcept {
        *ptr = (*ptr & ~(1 << offset)) | (u8(val) << offset);
        return *this;
    }

    bit_ref_mut& operator=(bit_ref_mut const& o) noexcept
        { if (&o == this) return *this; return *this = bool(o); }
    bit_ref_mut& operator=(bit_ref_mut&& o) noexcept { return *this = o; }

    [[nodiscard]] operator bit_ref() const noexcept { return {ptr, offset, true}; } // priv ctor
private:
    u8* ptr;
    u8  offset;
};

struct bitset final {
private:
    u8*    arr = nullptr;
    size_t n_b = 0;

public:
    bitset() noexcept = default;
    bitset(size_t num_bits, bool zero_mem = true);

    bitset(bitset const& o);
    bitset(bitset&& o) noexcept : arr(o.arr), n_b(o.n_b) { o.arr = nullptr; o.n_b = 0; };
    bitset& operator=(bitset const& o)
        { if(&o==this)return *this; this->~bitset();new(this)bitset(o)           ; return *this; }
    bitset& operator=(bitset&& o) noexcept
        { if(&o==this)return *this; this->~bitset();new(this)bitset(std::move(o)); return *this; }
    ~bitset() { delete[] arr; arr = nullptr; n_b = 0; }

    [[nodiscard]] bit_ref     operator[](size_t bit) const noexcept { return {arr, bit}    ; }
    [[nodiscard]] bit_ref_mut operator[](size_t bit)       noexcept { return {arr, bit}    ; }
    [[nodiscard]] u8 const*   raw_arr   ()           const noexcept { return arr           ; }
    [[nodiscard]] u8*         raw_arr   ()                 noexcept { return arr           ; }
    [[nodiscard]] size_t      n_bits    ()           const noexcept { return n_b           ; }
    [[nodiscard]] size_t      n_bytes   ()           const noexcept { return (n_b + 7) >> 3; }
};

std::ostream& operator<<(std::ostream& o, bitset const& b);
