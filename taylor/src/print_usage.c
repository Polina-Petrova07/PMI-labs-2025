#include "print_usage.h"

#include "argv0.h"
#include "output.h"
#include "series.h"
#include "util.h"

int print_usage(FILE * file) {
    tryprintf("usage: %s xstart xend xstep series num_terms\n", prognam);
    tryputs("\nTo convert to CSV, pipe to:\n  tr '\\036\\037' '\\n,'\n");
    tryputs("\nsupported series names:\n");
    for (const series * restrict ser = series_plural; ser < series_plural_end; ser++)
        tryprintf("%8s - %s\n", ser->nam, ser->desc);
    tryputs("\ntable header [to standard output]\n");
    print_header();
    return 0;
}
