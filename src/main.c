#include <stdio.h>

#include "my_malloc.h"

int main() {
    my_malloc_init();

    int x = 1;
    printf("\n\n\n\nrequesting %d bytes\n", x);
    void *ptr = my_malloc(x);

    return 0;
}