#pragma once

#include "series.h"

int print_header(void);
int print_per_row(
    const series *restrict ser          ,
    double                 x            ,
    unsigned               num_terms    ,
    double                 ref
);
int print_per_sumfn(double sum);
