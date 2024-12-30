#pragma once

#include <stddef.h>

void *mmap_malloc(size_t sz);

void mmap_free(void *ptr);