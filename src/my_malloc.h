#pragma once

#include <stddef.h>

void my_malloc_init();

void *my_malloc(size_t sz);

void my_free(void *ptr);