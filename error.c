#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void mrc_error(const char *msg) {
    printf("ERROR: %s\n", msg);
    exit(1);
}