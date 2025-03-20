#pragma once

#include "tune.h"

#include <stdbool.h>

typedef double         dbl  ;
typedef unsigned short shuns;
typedef unsigned       uns  ;
typedef unsigned long  lguns;
#define cdbl   const dbl
#define cshuns const shuns
#define cuns   const uns
#define clguns const lguns
#define exc restrict
#define try(expr) if ((expr) < 0) return -1
#define tryprintf(...) try(printf(__VA_ARGS__))
#define tryputs(str)   try(fputs(str, file))

#define CS "\037"
#define RS "\036"
#define PRECDBL "%#."PREC"lf"

const char * trim_nongraph_start  (const char * str);
char *       trim_nongraph_end    (char       * str);
char *       trim_nongraph        (char       * str);
bool         str_entirely_nongraph(const char * str);
bool str_to_ulong (char * str, unsigned long  * restrict out, const char ** restrict oerr);
bool str_to_double(char * str, double         * restrict out, const char ** restrict oerr);

static inline unsigned align_to_lane(unsigned x) {
    return (x + (LANE_WIDTH - 1)) & ~(LANE_WIDTH - 1);
}
