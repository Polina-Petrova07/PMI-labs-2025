#include "prognam.hxx"

const char * prognam = "lineq";

__attribute__((constructor)) static void init_prognam(int argc, char ** argv) {
    if (argc != 0) prognam = argv[0];
}

cerrprog_t cerrprog = cerrprog_t();
