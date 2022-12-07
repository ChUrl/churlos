/*****************************************************************************
 *                                                                           *
 *                        K E Y B O A R D D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "KeyboardDemo.h"

void KeyboardDemo::run() {

    /* Hier muess Code eingefuegt werden */

    Kernel::kout << "Keyboard Demo: " << endl;

    Kernel::kout.lock();
    Kernel::kout.clear();
    Kernel::kout << "Info: Die Keyboard Demo sperrt den Output Stream:\n"
         << "      Wenn die Preemption Demo laeuft wird diese also erst\n"
         << "      fortfahren wenn die Keyboard Demo wieder beendet ist." << endl;
    Kernel::kout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nInput: ";
    Kernel::kout.flush();

    while (running) {
        Kernel::kout << listener.waitForKeyEvent();
        Kernel::kout.flush();
    }

    Kernel::kout.unlock();
    Kernel::scheduler.exit();
}
