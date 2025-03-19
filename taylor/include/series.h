#pragma once

#include <stddef.h>

typedef void   (*pfn_series_gen)(double x, double * restrict out, unsigned num_terms);
typedef double (*pfn_series_ref)(double x                                           );
typedef struct {
    pfn_series_gen gen ;
    pfn_series_ref ref ;
    const char *   nam ;
    const char *   desc;
} series;

extern const series series_plural[];
extern const size_t num_series;
#define series_plural_end (series_plural + num_series)

unsigned short str2idx_series(const char * str);
