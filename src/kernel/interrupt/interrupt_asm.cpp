#include "IntDispatcher.h"
#include "kernel/system/System.h"
#include "kernel/service/InterruptService.h"

extern "C" void int_disp(uint8_t vector);

void int_disp(uint8_t vector) {
    auto &interruptService = Kernel::System::getService<Kernel::InterruptService>();
    interruptService.dispatchInterrupt(static_cast<Kernel::IntDispatcher::Vector>(vector));
}

