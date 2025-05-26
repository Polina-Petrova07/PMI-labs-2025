#pragma once
#include "solve.hxx"
#include <iosfwd>
template<typename T, mat_maj maj>
void print_results(std::ostream& o, solution_traces const& traces, mat<T, maj> m, size_t split);
