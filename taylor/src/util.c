#include "util.h"


#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

const char * trim_nongraph_start(const char * str) {
    for (; *str && !isgraph(*str); str++);
    return str;
}
char * trim_nongraph_end(char * str) {
    char * end = str + strlen(str);
    for (; (end > str) && !isgraph(*(end-1)); end--);
    *end = 0;
    return str;
}
char * trim_nongraph(char * str) { return trim_nongraph_end((char *) trim_nongraph_start(str)); }
bool str_entirely_nongraph(const char *str) { return *trim_nongraph_start(str) == 0; }

#define str_to(tyfnam, ty, strtocal)                                                   \
    bool str_to_##tyfnam(char * str, ty * restrict out, const char ** restrict oerr) { \
        errno = 0;                                                                     \
        char * iend;                                                                   \
        ty rslt = strtocal;                                                 \
        if (errno) {                                                                   \
            *oerr = strerror(errno);                                                   \
            return false;                                                              \
        }                                                                              \
        if (!str_entirely_nongraph(iend)) *oerr = "invalid input";                     \
        *out = rslt;                                                                   \
        return true;                                                                   \
    }

str_to(ulong , unsigned long, strtoul(str, &iend, 10));
str_to(double, double       , strtod (str, &iend    ));
