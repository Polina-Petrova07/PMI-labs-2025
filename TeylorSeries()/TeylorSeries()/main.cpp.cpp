#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
int main() {
    srand(time(NULL));
    locat();
    vvod();
    char choice;
    scanf(" %c", &choice);
    tablichka(choice);
}