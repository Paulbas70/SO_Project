#include <stdio.h>

#include "my_malloc.h"

int main() {
    my_malloc_init();

    int *ptrs[9];
    for (int i = 0; i < 9; i++) {
        printf("%d\n", i);
        ptrs[i] = (int *)my_malloc(1);
    }

    for (int i = 0; i < 9; i++) {
        my_free(ptrs[i]);
    }

    return 0;
}