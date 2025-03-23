#include "sumfn.h"
#include "util.h"
#include <limits.h>
#include <string.h>

#define sumfn(kindnam, loop) \
    inline static double sum_arr_##kindnam(const double4 * restrict vecs, size_t len) { \
        double sum = 0.0;                                                               \
        loop;                                                                           \
        return sum;                                                                     \
    }
  sumfn(pair_bwd, for (size_t i = len; i > 0  ; i--) sum += sum4_pair(vecs[i-1]))
  sumfn(pair_fwd, for (size_t i = 0  ; i < len; i++) sum += sum4_pair(vecs[i  ]))
  sumfn( bwd    , for (size_t i = len; i > 0  ; i--) sum += sum4_bwd (vecs[i-1]))
  sumfn( fwd    , for (size_t i = 0  ; i < len; i++) sum += sum4_fwd (vecs[i  ]))

#define NUM_SUM_ALG 2
const size_t num_sum_algs = NUM_SUM_ALG;
const sum_alg sum_algs[NUM_SUM_ALG] = {
    { sum_arr_bwd, "bwd", "Backward" },
    { sum_arr_fwd, "fwd", "Forward"  },
};

unsigned short str2idx_sum_alg(const char * str) {
    for (unsigned short i = 0; i < num_sum_algs; i++)
        if (strcmp(str, sum_algs[i].nam) == 0) return i;
    return USHRT_MAX;
}

double calc_sum(const double4 *restrict terms, unsigned num_terms, const sum_alg *restrict sumfn) {
    return sumfn->pfn(terms, align_to_lane(num_terms) / LANE_WIDTH);
}
