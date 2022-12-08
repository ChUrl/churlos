#ifndef CHURLOS_INTERRUPTSERVICE_H
#define CHURLOS_INTERRUPTSERVICE_H

#include "Service.h"
#include "kernel/interrupt/IntDispatcher.h"
#include "device/interrupt/PIC.h"
#include "lib/stream/Logger.h"
#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

// NOTE: I mainly have this to be able to implement additional interrupt controllers easily

/**
 * This class implements the interrupt system service.
 */
class InterruptService : public Service {
public:
    static const constexpr uint8_t ID = Service::INTERRUPT;

public:
    MakeDefault(InterruptService)

    MakeUncopyable(InterruptService)

    MakeUnmovable(InterruptService)

    void assignInterrupt(IntDispatcher::Vector vector, ISR &isr);

    void dispatchInterrupt(IntDispatcher::Vector vector);

    bool isException(IntDispatcher::Vector vector);

    bool isSpurious(IntDispatcher::Vector vector);

    void allowInterrupt(Device::PIC::Irq irq);

    void forbidInterrupt(Device::PIC::Irq irq);

    bool status(Device::PIC::Irq irq);

    void sendEndOfInterrupt();

private:
    IntDispatcher intDispatcher;

    uint32_t spuriousCounter = 0;

    static NamedLogger log;
};

}

#endif //CHURLOS_INTERRUPTSERVICE_H
