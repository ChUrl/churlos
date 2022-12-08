#include <cstdint>

// Implemented in Thread.asm
extern "C" {

/**
 * Start or continue a thread.
 *
 * @param esp The stack pointer of the thread to start/continue
 */
void Thread_start(uint32_t esp);

/**
 * Switch from the current thread to another thread.
 * The stack pointer member variable of the current stack will be updated.
 *
 * @param esp_prev The address where the current thread's stack pointer will be saved
 * @param esp_next The stack pointer of the thread to switch to
 */
void Thread_switch(uint32_t *esp_prev, uint32_t esp_next);

}

