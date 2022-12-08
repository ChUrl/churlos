#include "InterruptService.h"
#include "device/cpu/CPU.h"
#include "kernel/exception/Bluescreen.h"

namespace Kernel {

NamedLogger InterruptService::log = NamedLogger("InterruptService");

void InterruptService::assignInterrupt(IntDispatcher::Vector vector, ISR &isr) {
    intDispatcher.assign(vector, isr);
    log.info() << "Assigned ISR for vector " << dec << vector << endl;
}

void InterruptService::dispatchInterrupt(IntDispatcher::Vector vector) {
    if (isException(vector)) {
        bs_dump(vector);
        Device::CPU::halt();

        // TODO: Exception
    }

    if (isSpurious(vector)) {
        ++spuriousCounter;
        log.info() << "Intercepted Spurious Interrupt" << endl;
        return;
    }

    sendEndOfInterrupt(); // TODO: Check when to send EOI with the PIC

    intDispatcher.dispatch(vector);
}

bool InterruptService::isException(IntDispatcher::Vector vector) {
    return vector < IntDispatcher::TIMER;
}

bool InterruptService::isSpurious(IntDispatcher::Vector vector) {
    // TODO
    return false;
}

void InterruptService::allowInterrupt(Device::PIC::Irq irq) {
    Device::PIC::allow(irq);
    log.info() << "Allowed IRQ" << dec << irq << endl;
}

void InterruptService::forbidInterrupt(Device::PIC::Irq irq) {
    Device::PIC::forbid(irq);
}

bool InterruptService::status(Device::PIC::Irq irq) {
    return Device::PIC::status(irq);
}

void InterruptService::sendEndOfInterrupt() {
    // TODO
}

}