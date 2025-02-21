#include <stdlib.h>
// #include <string.h>

int stringStat(const char *string, size_t multiplier, int *count) {
    ++*count;
    const char* end = string;
    while (*end != 0) end++;
    return multiplier * (end - string);
}
