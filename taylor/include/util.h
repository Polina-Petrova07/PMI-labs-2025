#pragma once

#include <stdbool.h>

const char * trim_nongraph_start  (const char * str);
char *       trim_nongraph_end    (char       * str);
char *       trim_nongraph        (char       * str);
bool         str_entirely_nongraph(const char * str);
bool str_to_ulong (char * str, unsigned long  * restrict out, const char ** restrict oerr);
bool str_to_double(char * str, double         * restrict out, const char ** restrict oerr);
