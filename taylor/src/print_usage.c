#include "print_usage.h"

#include "argv0.h"
#include "output.h"
#include "series.h"
#include "util.h"

int print_usage(FILE * file) {
    try(fprintf(file, "usage: %s xstart xend xstep series num_terms\n", prognam));
    try(fputs("\nTo convert to CSV, pipe to:\n  tr '\\036\\037' '\\n,'\n", file));
    try(fputs("\nsupported series names:\n", file));
    for (const series * restrict ser = series_plural; ser < series_plural_end; ser++)
        try(fprintf(file, "%8s - %s\n", ser->nam, ser->desc));
    try(fputs("\ntable header [to standard output]\n", file));
    print_header();
    return 0;
}
