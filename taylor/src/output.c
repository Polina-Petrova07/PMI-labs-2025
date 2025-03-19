#include "output.h"

#include "sumfn.h"
#include "util.h"
#include <stdio.h>

int print_header(void) {
    try(fputs("Series name,x,Number of terms,libm value,", stdout));
    const char * algdesc = sum_algs[0].desc;
    try(printf("%s sum,%s abs. error", algdesc, algdesc));
    for (const sum_alg *restrict al = sum_algs; al < sum_algs_end; al++) {
        try(printf(",%s sum,%s error rel. to first", al->desc, al->desc));
    }
    try(putchar('\n'));
    return 0;
}
int print_per_row(
    const series *restrict ser          ,
    double                 x            ,
    unsigned               num_terms    ,
    double                 ref          ,
    double                 first_sum    ,
    double                 first_abs_err
) {
    try(printf(
        "%s"CS PRECDBL CS "%u"CS PRECDBL CS PRECDBL CS PRECDBL,
        ser->desc, x, num_terms, ref, first_sum, first_abs_err));
    return 0;
}
int print_per_sumfn(double sum, double rel_err) {
    try(printf(CS PRECDBL CS PRECDBL, sum, rel_err));
    return 0;
}
