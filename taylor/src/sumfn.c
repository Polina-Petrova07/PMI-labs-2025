#include "sumfn.h"
#include <limits.h>
#include <string.h>

#define sumfn(kindnam, loop) \
    inline static double sum_arr_##kindnam(const double4 * restrict vecs, size_t len) { \
        double sum = 0.0;                                                               \
        loop;                                                                           \
        return sum;                                                                     \
    }
  sumfn(pair_bwd, for (size_t i = len; i > 0  ; i--) sum += sum4_pair(vecs[i-1]))
//sumfn(pair_fwd, for (size_t i = 0  ; i < len; i++) sum += sum4_pair(vecs[i  ]))
  sumfn( bwd    , for (size_t i = len; i > 0  ; i--) sum += sum4_bwd (vecs[i-1]))
  sumfn( fwd    , for (size_t i = 0  ; i < len; i++) sum += sum4_fwd (vecs[i  ]))

#define NUM_SUM_ALG 3
const size_t num_sum_algs = NUM_SUM_ALG;
const sum_alg sum_algs[NUM_SUM_ALG] = {
    { sum_arr_pair_bwd, "pair_bwd" },
//  { sum_arr_pair_fwd, "pair_fwd" },
    { sum_arr_bwd     , "bwd"      },
    { sum_arr_fwd     , "fwd"      },
};

unsigned short str2idx_sum_alg(const char * str) {
    for (unsigned short i = 0; i < num_sum_algs; i++)
        if (strcmp(str, sum_algs[i].nam) == 0) return i;
    return USHRT_MAX;
}
