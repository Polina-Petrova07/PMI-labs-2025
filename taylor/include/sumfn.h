#pragma once

#include "double4.h"
#include <stddef.h>

typedef double (*pfn_sum_arr)(const double4 * restrict vecs, size_t len);

inline static double sum4_pair(double4 v) { return (v.v[3] + v.v[2]) + (v.v[1] + v.v[0]); }
inline static double sum4_bwd (double4 v) { return  v.v[3] + v.v[2]  +  v.v[1] + v.v[0] ; }
inline static double sum4_fwd (double4 v) { return  v.v[0] + v.v[1]  +  v.v[2] + v.v[3] ; }

typedef struct {
    pfn_sum_arr  pfn ;
    const char * nam ;
    const char * desc;
} sum_alg;

extern const sum_alg sum_algs[];
extern const size_t num_sum_algs;
#define sum_algs_end (sum_algs + num_sum_algs)

unsigned short str2idx_sum_alg(const char * str);
double calc_sum(const double4 *restrict terms, unsigned num_terms, const sum_alg *restrict sumfn);
