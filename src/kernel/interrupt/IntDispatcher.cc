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
#include "kernel/exception//Bluescreen.h"

extern "C" void int_disp(uint8_t vector);

/*****************************************************************************
 * Prozedur:        int_disp                                                 *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Low-Level Interrupt-Behandlung.                          *
 *                  Diese Funktion ist in der IDT fuer alle Eintraege einge- *
 *                  tragen. Dies geschieht bereits im Bootloader.            *
 *                  Sie wird also fuer alle Interrupts aufgerufen. Von hier  *
 *                  aus sollen die passenden ISR-Routinen der Treiber-Objekte*
 *                  mithilfe von 'IntDispatcher::report' aufgerufen werden.  *
 * Parameter:                                                                *
 *      vector:     Vektor-Nummer der Unterbrechung                          *
 *****************************************************************************/
void int_disp(uint8_t vector) {

    /* hier muss Code eingefuegt werden */

    if (vector < 32) {
        bs_dump(vector);
        Device::CPU::halt();
    }

    if (Kernel::intdis.report(vector) < 0) {
        Kernel::kout << "Panic: unexpected interrupt " << vector;
        Kernel::kout << " - processor halted." << endl;
        Device::CPU::halt();
    }
}

namespace Kernel {

/*****************************************************************************
 * Methode:         IntDispatcher::assign                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Registrierung einer ISR.                                 *
 *                                                                           *
 * Parameter:                                                                *
 *      vector:     Vektor-Nummer der Unterbrechung                          *
 *      isr:        ISR die registriert werden soll                          *
 *                                                                           *
 * Rueckgabewert:   0 = Erfolg, -1 = Fehler                                  *
 *****************************************************************************/
int IntDispatcher::assign(uint8_t vector, ISR &isr) {

    /* hier muss Code eingefuegt werden */

    if (vector >= size) {
        log.error() << "Invalid vector number when assigning" << endl;
        return -1;
    }

    map[vector] = &isr;
    log.info() << "Registered ISR for vector " << dec << vector << endl;

    return 0;
}

/*****************************************************************************
 * Methode:         IntDispatcher::report                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Eingetragene ISR ausfuehren.                             *
 *                                                                           *
 * Parameter:                                                                *
 *      vector:     Gesuchtes ISR-Objekt fuer diese Vektor-Nummer.           *
 *                                                                           *
 * Rueckgabewert:   0 = ISR wurde aufgerufen, -1 = unbekannte Vektor-Nummer  *
 *****************************************************************************/
int IntDispatcher::report(uint8_t vector) {

    /* hier muss Code eingefuegt werden */

    if (vector >= size) {
        return -1;
    }

    ISR *isr = map[vector];

    if (isr == nullptr) {
        log.error() << "No ISR registered for vector " << vector << endl;
        return -1;
    }

    // 32 = Timer
    // 33 = Keyboard
    // log.trace() << "Interrupt: " << dec << vector << endl;
    if (vector == 33) {
        log.debug() << "Keyboard Interrupt" << endl;
    }

    isr->trigger();

    return 0;
}

}
