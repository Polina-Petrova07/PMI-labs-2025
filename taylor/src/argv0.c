#include "argv0.h"
const char * prognam = "taylor";

__attribute__((constructor)) static void iniprognam(int argc, char ** argv) {
    if (argc) prognam = argv[0];
}
