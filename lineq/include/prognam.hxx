#pragma once

#include <iostream>

extern const char * prognam;
struct cerrprog_t {
    template<typename T>
    std::ostream& operator<<(const T& val) { return std::cerr << prognam << ": " << val; }
};
extern cerrprog_t cerrprog;
