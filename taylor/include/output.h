#pragma once

#include "series.h"

int print_header(void);
int print_per_row(
    const series *restrict ser          ,
    double                 x            ,
    unsigned               num_terms    ,
    double                 ref          ,
    double                 first_sum    ,
    double                 first_abs_err
);
int print_per_sumfn(double sum, double rel_err);
