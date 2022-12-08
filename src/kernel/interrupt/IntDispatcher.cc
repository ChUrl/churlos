#include "IntDispatcher.h"
#include "device/cpu/CPU.h"
#include "kernel/exception/Bluescreen.h"
#include "lib/util/System.h"

namespace Kernel {

void IntDispatcher::assign(uint8_t vector, ISR &isr) {
    handlerMap[vector] = &isr;
}

void IntDispatcher::dispatch(uint8_t vector) {
    ISR *isr = handlerMap[vector];

    if (isr == nullptr) {
        // TODO: Throw exception

        Util::System::out << "Panic: unexpected interrupt " << vector;
        Util::System::out << " - processor halted." << endl;
        Device::CPU::halt();
    }

    isr->trigger();
}

}
