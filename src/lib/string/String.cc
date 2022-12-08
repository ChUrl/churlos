#include "String.h"
#include "lib/memory/Memory.h"

namespace String {

std::size_t strlen(const char *str) {
    const char *current = str;
    while (*current != '\0') { ++current; }
    return current - str;
}

void strncpy(char *destination, std::size_t n, const char *source) {
    Memory::memcpy<char>(destination, source, n);
}

// Only compares equal length strings
int strcmp(const char *a, const char *b) {
    std::size_t a_len = strlen(a);
    std::size_t b_len = strlen(b);

    if (a_len < b_len) {
        return -1;
    }
    if (b_len < a_len) {
        return 1;
    }

    for (std::size_t i = 0; i < a_len; ++i) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (b[i] < a[i]) {
            return 1;
        }
    }

    return 0;
}

}
