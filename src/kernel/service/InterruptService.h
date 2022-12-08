#ifndef CHURLOS_INTERRUPTSERVICE_H
#define CHURLOS_INTERRUPTSERVICE_H

#include "Service.h"
#include "kernel/interrupt/IntDispatcher.h"
#include "device/interrupt/PIC.h"

namespace Kernel {

class InterruptService : public Service {
public:
    static const constexpr uint8_t ID = 0;

public:
    InterruptService() = default;

    // TODO: Rest of constructors

    void assignInterrupt(IntDispatcher::Vector vector, ISR &isr);

    void dispatchInterrupt(IntDispatcher::Vector vector);

    bool isSpurious(IntDispatcher::Vector vector);

    void allowInterrupt(Device::PIC::Irq irq);

    void forbidInterrupt(Device::PIC::Irq irq);

    bool status(Device::PIC::Irq irq);

    void sendEndOfInterrupt();

private:
    IntDispatcher intDispatcher;
};

}

#endif //CHURLOS_INTERRUPTSERVICE_H
