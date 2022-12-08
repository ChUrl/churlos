#include "IntDispatcher.h"
#include "kernel/system/System.h"
#include "kernel/service/InterruptService.h"

// Called from startup.asm
extern "C" {

/**
 * Call an ISR after an interrupt occured.
 *
 * @param vector The vector number of the occured interrupt
 */
void int_disp(uint8_t vector) {
    auto &interruptService = Kernel::System::getService<Kernel::InterruptService>();
    interruptService.dispatchInterrupt(static_cast<Kernel::IntDispatcher::Vector>(vector));
}

}

