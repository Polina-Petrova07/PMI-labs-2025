#pragma once
#include "frac.hxx"

void read_mat(std::istream& i, mat_mem<frac, mat_maj::row>& o, size_t& split);
