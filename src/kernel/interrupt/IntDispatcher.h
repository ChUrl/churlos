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

class IntDispatcher {
    friend class InterruptService;

public:
    /**
     * Vector numbers (slots in the IDT)
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
    void assign(uint8_t vector, ISR &isr);

    void dispatch(uint8_t vector);

private:
    Container::Array<ISR *, 256> handlerMap = {nullptr};
};

}

#endif
