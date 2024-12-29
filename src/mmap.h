#pragma once

#include <stdlib.h>

void *mmap_malloc(size_t sz);

void mmap_free(void *ptr);