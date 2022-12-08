/*****************************************************************************
 *                                                                           *
 *                         I N T D I S P A T C H E R                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zentrale Unterbrechungsbehandlungsroutine des Systems.   *
 *                  Der Parameter gibt die Nummer des aufgetretenen          *
 *                  Interrupts an. Wenn eine Interrupt Service Routine (ISR) *
 *                  in der Map registriert ist, so wird diese aufgerufen.    *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef IntDispatcher_include__
#define IntDispatcher_include__

#include <cstdint>
#include "ISR.h"
#include "lib/container/Array.h"
#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

/**
 * This class implements a simple interrupt dispatcher.
 * It is part of the 2-step interrupt handling: Instead of registering ISRs
 * in the IDT directly, the "dispatch" function is called with the vector number.
 */
class IntDispatcher {
    friend class InterruptService;

public:
    /**
     * Vector numbers (slots in the IDT).
     * Every IRQ corresponds to one vector number.
     */
    enum Vector {
        TIMER = 32,
        KEYBOARD = 33,
        COM1 = 36
    };

public:
    MakeDefault(IntDispatcher)

    MakeUnmovable(IntDispatcher)

    MakeUncopyable(IntDispatcher)

private:
    /**
     * Assign an interrupt handler to a vector number.
     *
     * @param vector The vector number
     * @param isr The interrupt handler
     */
    void assign(Vector vector, ISR &isr);

    /**
     * Call a registered interrupt handler.
     *
     * @param vector The vector number of the occured interrupt
     */
    void dispatch(Vector vector);

private:
    Container::Array<ISR *, 256> handlerMap = {nullptr};
};

}

#endif
