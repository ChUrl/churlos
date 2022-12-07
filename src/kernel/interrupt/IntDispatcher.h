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

#include "ISR.h"
#include "lib/container//Array.h"
#include "lib/stream/Logger.h"

namespace Kernel {

class IntDispatcher {
private:
    NamedLogger log;

    enum {
        size = 256
    };
    Container::Array<ISR *, size> map;

public:
    IntDispatcher(const IntDispatcher &copy) = delete;  // Verhindere Kopieren

    // Vektor-Nummern
    enum {
        timer = 32,
        keyboard = 33,
        com1 = 36
    };

    // Initialisierung der ISR map mit einer Default-ISR.
    IntDispatcher() : log("IntDis") {
        for (ISR *&slot: map) {
            slot = nullptr;
        }
    }

    // Registrierung einer ISR. (Rueckgabewert: 0 = Erfolg, -1 = Fehler)
    int assign(uint8_t vector, ISR &isr);

    // ISR fuer 'vector' ausfuehren
    int report(uint8_t vector);
};

}

#endif
