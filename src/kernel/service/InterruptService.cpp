#include "InterruptService.h"
#include "kernel/exception/Bluescreen.h"
#include "device/cpu/CPU.h"
#include "kernel/system/System.h"

// TODO: Move to interrupt_interface or sth.
extern "C" void int_disp(uint8_t vector);

void int_disp(uint8_t vector) {

    /* hier muss Code eingefuegt werden */

    // Exception
    if (vector < 32) {
        bs_dump(vector);
        Device::CPU::halt();

        // TODO: Exception
    }

    Kernel::System::getService<Kernel::InterruptService>()
            .dispatchInterrupt(static_cast<Kernel::IntDispatcher::Vector>(vector));
}

namespace Kernel {

void InterruptService::assignInterrupt(IntDispatcher::Vector vector, ISR &isr) {
    intDispatcher.assign(vector, isr);
}

void InterruptService::dispatchInterrupt(IntDispatcher::Vector vector) {
    intDispatcher.dispatch(vector);
}

void InterruptService::allowInterrupt(Device::PIC::Irq irq) {
    Device::PIC::allow(irq);
}

void InterruptService::forbidInterrupt(Device::PIC::Irq irq) {
    Device::PIC::forbid(irq);
}

bool InterruptService::status(Device::PIC::Irq irq) {
    return Device::PIC::status(irq);
}

}