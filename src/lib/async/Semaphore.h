/*****************************************************************************
 *                                                                           *
 *                             S E M A P H O R E                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung von Sempahor-Objekten.                   *
 *                                                                           *
 * Autor:           Michael Schoettner, 2.9.2016                             *
 *****************************************************************************/

#ifndef Semaphore_include__
#define Semaphore_include__

#include "kernel/process/Thread.h"
#include "SpinLock.h"
#include "lib/container//Vector.h"

namespace Async {

class Semaphore {
private:
    // Queue fuer wartende Threads.
    Container::vector<unsigned int> wait_queue;
    SpinLock lock;

    int counter;

public:
    Semaphore(const Semaphore &copy) = delete;  // Verhindere Kopieren

    // Konstruktor: Initialisieren des Semaphorzaehlers
    Semaphore(int c) : wait_queue(true), counter(c) {}

    // 'Passieren': Warten auf das Freiwerden eines kritischen Abschnitts.
    void p();

    // 'Vreigeben': Freigeben des kritischen Abschnitts.
    void v();
};

}

#endif
