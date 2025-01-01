#include "my_malloc.h"

#include <stdio.h>
#include <unistd.h>

int main()
{
    my_malloc_init();

    int *ptr = my_malloc(56);
    *ptr = 1;
    printf("The value of ptr is %d\n\n", *ptr);

    int *ptr2 = my_malloc(57);
    *ptr2 = 2;
    printf("The value of ptr2 is %d\n\n", *ptr2);

    int *ptr3 = my_malloc(1024);
    *ptr3 = 3;
    printf("The value of ptr3 is %d\n\n", *ptr3);

    int *ptr4 = my_malloc(1025);
    *ptr4 = 4;
    printf("The value of ptr4 is %d\n\n", *ptr3);

    printf("Freeing ptr\n");
    my_free(ptr);

    printf("\nFreeing ptr2\n");
    my_free(ptr2);

    printf("\nFreeing ptr3\n");
    my_free(ptr3);

    printf("\nFreeing ptr4\n");
    my_free(ptr4);

    return 0;
}