/*****************************************************************************
 *                                                                           *
 *                         I N T D I S P A T C H E R                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zentrale Unterbrechungsbehandlungsroutine des Systems.   *
 *                  Der Parameter gibt die Nummer des aufgetretenen          *
 *                  Interrupts an. Wenn eine Interrupt Service Routine       *
 *                  registriert ist, wird diese aufgerufen.                  *
 *                                                                           *
 * Autor:           Michael Schoettner, 31.8.2016                            *
 *****************************************************************************/
#include "IntDispatcher.h"
#include "device/cpu/CPU.h"
#include "kernel/system/Globals.h"
#include "kernel/exception/Bluescreen.h"
#include "lib/util/System.h"

namespace Kernel {

NamedLogger IntDispatcher::log = NamedLogger("IntDispatcher");

int IntDispatcher::assign(uint8_t vector, ISR &isr) {

    /* hier muss Code eingefuegt werden */

    handlerMap[vector] = &isr;
    log.info() << "Registered ISR for vector " << dec << vector << endl; // TODO: Numbers don't show up in log

    return 0;
}

int IntDispatcher::dispatch(uint8_t vector) {

    /* hier muss Code eingefuegt werden */

    ISR *isr = handlerMap[vector];

    if (isr == nullptr) {
        log.error() << "No ISR registered for vector " << vector << endl; // TODO: Numbers don't show up in log

        // TODO: Throw exception

        Util::System::out << "Panic: unexpected interrupt " << vector;
        Util::System::out << " - processor halted." << endl;
        Device::CPU::halt();
    }

    isr->trigger();

    return 0;
}

}
