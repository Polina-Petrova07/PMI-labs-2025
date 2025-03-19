#include "argv0.h"
#include "print_usage.h"
#include "output.h"
#include "series.h"
#include "sumfn.h"
#include "util.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int for_x(cdbl x, const series *exc ser, const double4 *exc terms, cuns num_terms) {
    cdbl ref = ser->ref(x);
    const sum_alg *exc al = sum_algs;
    cdbl first_sum     = calc_sum(terms, num_terms, al);
    cdbl first_abs_err = first_sum - ref;
    try(print_per_row(ser, x, num_terms, ref, first_sum, first_abs_err));

    for (al++; al < sum_algs_end; al++) {
        cdbl sum     = calc_sum(terms, num_terms, al);
        cdbl rel_err = fabs((sum - ref) / first_abs_err);
        try(print_per_sumfn(sum, rel_err));
    }

    try(putchar(*RS));
    return 0;
}

static int main_inner(cdbl xstart, cdbl xend, cdbl xstep, const series *exc ser, cuns num_terms) {
    cuns num_terms_align = align_to_lane(num_terms);

    double4 *exc terms = NULL;
    if (num_terms_align < ALLOCA_CUTOFF_TERMS) terms = alloca(num_terms_align * sizeof(dbl));
    else if (!(terms = reallocarray(NULL, num_terms_align, sizeof(dbl)))) return -1;

    dbl x = xstart;
    do {
        fill_terms(x, ser, terms, num_terms);
#ifdef DEBUG_SERIES
        for (cdbl *exc d = (cdbl *) terms; d < (cdbl *) terms + num_terms_align; d++)
            fprintf(stderr, "%p " PRECDBL "\n", d, *d);
        putchar('\n');
#endif
        for_x(x, ser, terms, num_terms);
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

    if (num_terms > UINT_MAX - (LANE_WIDTH - 1))
        bail("%lu terms is entirely too many terms", num_terms);

    if (main_inner(xstart, xend, xstep, &series_plural[ser_idx], num_terms) < 0 && errno != 0) {
        if (errno != 0) {
            perror(prognam);
            return 2;
        } else return 1;
    };
    return 0;
}
