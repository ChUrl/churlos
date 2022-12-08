#include "SpinLock.h"

namespace Async {

// TODO: Outsource to Atomic lib
static inline uint32_t CAS(const uint32_t *ptr) {
    uint32_t prev;

    asm volatile("lock;" // prevent race conditions with other cores
                 "cmpxchg %1, %2;" // %1 = _new; %2 = *ptr
            : "=a"(prev) // output: =a: RAX -> prev (%0))
            : "r"(1), "m"(*ptr), "a"(0) // input = %1, %2, %3 (r=register, m=memory, a=accumlator = eax
            : "memory"); // ensures assembly block will not be moved by gcc

    return prev; // return pointer instead of prev to prevent unnecessary second call
}

SpinLock::SpinLock() : lock(0), ptr(&lock) {}

void SpinLock::acquire() {
    // If lock == 0 the SpinLock can be aquired without waiting
    // If lock == 1 the  while loop blocks until aquired
    while (CAS(ptr) != 0) {}
}

void SpinLock::release() {
    lock = 0;
}

}
