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
#include "kernel/system/System.h"
#include "kernel/service/SchedulerService.h"

void KeyboardDemo::run() {

    /* Hier muess Code eingefuegt werden */

    Util::System::out << "Keyboard Demo: " << endl;

    Util::System::out.lock();
    Util::System::out.clear();
    Util::System::out << "Info: Die Keyboard Demo sperrt den Output Stream:\n"
                      << "      Wenn die Preemption Demo laeuft wird diese also erst\n"
                      << "      fortfahren wenn die Keyboard Demo wieder beendet ist." << endl;
    Util::System::out << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nInput: ";
    Util::System::out.flush();

    while (running) {
        Util::System::out << listener.waitForKeyEvent();
        Util::System::out.flush();
    }

    Util::System::out.unlock();
    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    schedulerService.exit();
}
