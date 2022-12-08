#include "Memory.h"

namespace Memory {

void memset(uint8_t *destination, const uint8_t value, std::size_t bytes) {
    for (std::size_t byte = 0; byte < bytes; ++byte) {
        *(destination + byte) = value;
    }
}

}
