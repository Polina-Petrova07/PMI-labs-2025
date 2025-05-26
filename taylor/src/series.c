#include "series.h"
#include "util.h"
#include <limits.h>
#include <math.h>
#include <string.h>

static void ser_sin(double x, double * restrict out, unsigned num_terms) {
    if (!num_terms) return;
    double term = x;
    *out++ = term;
    num_terms--;
    double xsq = x * x;
    unsigned facd = 2; // factorial denominator factor
    for (unsigned facd = 2; num_terms; num_terms--) {
        unsigned denom = facd * (facd + 1);
        facd += 2;
        term *= -(xsq / denom);
        *out++ = term;
    }
}

static void ser_cos(double x, double * restrict out, unsigned num_terms) {
    if (!num_terms) return;
    double term = 1;
    *out++ = term;
    num_terms--;
    double xsq = x * x;
    for (unsigned facd = 1; num_terms; num_terms--) {
        unsigned denom = facd * (facd + 1);
        facd += 2;
        term *= -(xsq / denom);
        *out++ = term;
    }
}

static void ser_exp(double x, double * restrict out, unsigned num_terms) {
    if (!num_terms) return;
    double term = 1;
    *out++ = term;
    num_terms--;
    for (unsigned facd = 1; num_terms; num_terms--) *out++ = (term *= x / facd++);
}

static void ser_ln1p(double x, double * restrict out, unsigned num_terms) {
    if (!num_terms) return;
    double term = x;
    *out++ = term;
    num_terms--;
    for (unsigned i = 2; num_terms; num_terms--) *out++ = ((term *= -x) / i++);
}

#define NUM_SERIES 4
const size_t num_series = NUM_SERIES;
const series series_plural[NUM_SERIES] = {
    { ser_sin , sin  , "sin" , "sin(x)"  },
    { ser_cos , cos  , "cos" , "cos(x)"  },
    { ser_exp , exp  , "exp" , "exp(x)"  },
    { ser_ln1p, log1p, "ln1p", "ln(1+x)" },
};

unsigned short str2idx_series(const char * str) {
    for (unsigned short i = 0; i < num_series; i++)
        if (strcmp(str, series_plural[i].nam) == 0) return i;
    return USHRT_MAX;
}

void fill_terms(double x, const series *restrict ser, double4 *restrict terms, unsigned num_terms) {
    double *restrict d_terms = (double *) terms;
    unsigned num_terms_align = align_to_lane(num_terms);
    ser->gen(x, d_terms, num_terms);
    memset(&d_terms[num_terms], 0, (num_terms_align - num_terms) * sizeof(double));
}
