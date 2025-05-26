#pragma once
#include <cctype>
#include <iostream>

static bool is_nl(char c)        { return c == '\n' || c == '\r'      ; }
static bool is_num_start(char c) { return c == '-'  || isdigit(c) != 0; }
void eat_pad(std::istream& i);
void setstate_noexcept(std::istream& i, std::istream::iostate sta) noexcept;

struct throw_only_bad final {
    throw_only_bad(std::basic_ios<char>& ios);
    throw_only_bad(throw_only_bad const&)            = delete;
    throw_only_bad(throw_only_bad&&)                 = delete;
    throw_only_bad& operator=(throw_only_bad const&) = delete;
    throw_only_bad& operator=(throw_only_bad&&)      = delete;
    ~throw_only_bad();
private:
    std::basic_ios<char>& ios;
    std::ios_base::iostate prev_exc;
};
