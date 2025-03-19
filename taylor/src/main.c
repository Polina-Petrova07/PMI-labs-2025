#include "argv0.h"
#include "print_usage.h"
#include "series.h"
#include "sumfn.h"
#include "util.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TERMS_ALIGN 4

typedef double         dbl  ;
typedef unsigned short shuns;
typedef unsigned       uns  ;
typedef unsigned long  lguns;
#define cdbl   const dbl
#define cshuns const shuns
#define cuns   const uns
#define clguns const lguns
#define exc restrict

#define ALLOCA_CUTOFF_TERMS 512

#define PREC "18"

#define CS "\037"
#define RS "\036"
#define PRECDBL "%#."PREC"lf"

static uns align_to_lane(cuns num_terms) {
    return (num_terms + (NUM_TERMS_ALIGN - 1)) & ~(NUM_TERMS_ALIGN - 1);
}

static int do_row(
    dbl x,
    const double4 *exc terms,
    cuns num_terms,
    const series * ser,
    const sum_alg *exc sumfn
) {
    cdbl sum = sumfn->pfn(terms, align_to_lane(num_terms) / NUM_TERMS_ALIGN);
    cdbl ref = ser->ref(x);
    cdbl abserr = sum - ref;
    #define ROW_F "%s" CS PRECDBL CS "%u" CS "%s" CS PRECDBL CS PRECDBL RS
    if (printf(ROW_F, ser->nam, x, num_terms, sumfn->nam, sum, abserr) == -1)
        return -1;
    return 0;
}

static void fill_terms(dbl x, const series *exc ser, double4 *exc terms, cuns num_terms) {
    cuns num_terms_align = align_to_lane(num_terms);
    ser->gen(x, (dbl *) terms, num_terms);
    for (size_t i = num_terms; i < num_terms_align; i++) ((dbl *) terms)[i] = 0.0;
#ifdef DEBUG_SERIES
        for (cdbl *exc d = (cdbl *) terms; d < (cdbl *) terms + num_terms_align; d++)
            fprintf(stderr, "%p " PRECDBL "\n", d, *d);
        putchar('\n');
#endif
}

static int main_inner(cdbl xstart, cdbl xend, cdbl xstep, const series *exc ser, cuns num_terms) {
    cuns num_terms_align = align_to_lane(num_terms);

    double4 *exc terms = NULL;
    if (num_terms_align < ALLOCA_CUTOFF_TERMS) terms = alloca(num_terms_align * sizeof(dbl));
    else if (!(terms = reallocarray(NULL, num_terms_align, sizeof(dbl)))) return -1;

    dbl x = xstart;
    do {
        fill_terms(x, ser, terms, num_terms);

        for (const sum_alg *exc al = sum_algs; al < sum_algs_end; al++)
            if (do_row(x, (const double4 *) terms, num_terms, ser, al) == -1) return -1;

        x += xstep;
    } while ((xstep > 0 && x < xend) || (xstep < 0 && x > xend));
    return 0;
}

#define bail(fstring, ...) {                                      \
        fprintf(stderr, "%s: "fstring"\n", prognam, __VA_ARGS__); \
        return 1;                                                 \
    }

int main(int argc, char ** argv) {
    if (argc != 6) {
        if (print_usage(stderr) < 0) return 2;
        return 1;
    }
    char * xstart_tx    = argv[1];
    char * xend_tx      = argv[2];
    char * xstep_tx     = argv[3];
    char * series_nam   = argv[4];
    char * num_terms_tx = argv[5];

    const char * serr;

    dbl xstart, xend, xstep;
    if (!str_to_double(xstart_tx, &xstart, &serr)) bail("failed to read xstart: %s", serr);
    if (!str_to_double(xend_tx  , &xend  , &serr)) bail("failed to read xend: %s"  , serr);
    if (!str_to_double(xstep_tx , &xstep , &serr)) bail("failed to read xstep: %s" , serr);

    if (xstep == 0.0 && xstart != xend) bail("xstart and xend differ, step must not be zero", 0);
    if (xstep < 0.0) bail("step sign is inferred from which of xstart and xend is bigger", 0);
    if (xstart > xend) xstep = -xstep;

    cshuns ser_idx = str2idx_series(trim_nongraph(series_nam));
    if (ser_idx == USHRT_MAX) bail("no such series: %s", series_nam);

    lguns num_terms;
    if (!str_to_ulong(num_terms_tx, &num_terms, &serr))
        bail("failed to determine requested number of terms: %s", serr);

    if (num_terms > UINT_MAX - (NUM_TERMS_ALIGN - 1))
        bail("%lu terms is entirely too many terms", num_terms);

    if (main_inner(xstart, xend, xstep, &series_plural[ser_idx], num_terms) < 0 && errno != 0) {
        if (errno != 0) {
            perror(prognam);
            return 2;
        } else return 1;
    };
    return 0;
}

static_assert(0 < NUM_TERMS_ALIGN && NUM_TERMS_ALIGN <= UINT_MAX, "invalid alignment");
static_assert(SIZE_MAX / sizeof(double4) > ALLOCA_CUTOFF_TERMS, "invalid alloca() cutoff");
