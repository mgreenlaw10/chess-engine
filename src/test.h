#pragma once

#include <time.h>
#include <stdio.h>
#include <inttypes.h>

#define TIME_CLOCK(expr) do { \
    clock_t start_time = clock(); \
    expr; \
    clock_t end_time = clock(); \
    printf("Time spent in func: %f seconds\n", \
           (double)(end_time - start_time) / CLOCKS_PER_SEC); \
} while (0)

