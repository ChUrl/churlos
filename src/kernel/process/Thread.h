/*****************************************************************************
 *                                                                           *
 *                                 T H R E A D                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines kooperativen Thread-Konzepts.      *
 *                  Thread-Objekte werden vom Scheduler in einer verketteten *
 *                  Liste 'readylist' verwaltet.                             *
 *                                                                           *
 *                  Im Konstruktor wird der initialie Kontext des Threads    *
 *                  eingerichtet. Mit 'start' wird ein Thread aktiviert.     *
 *                  Die CPU sollte mit 'yield' freiwillig abgegeben werden.  *
 *                  Um bei einem Threadwechsel den Kontext sichern zu        *
 *                  koennen, enthaelt jedes Threadobjekt eine Struktur       *
 *                  ThreadState, in dem die Werte der nicht-fluechtigen      *
 *                  Register gesichert werden koennen.                       *
 *                                                                           *
 *                  Zusaetzlich zum vorhandenen freiwilligen Umschalten der  *
 *                  CPU mit 'Thread_switch' gibt es nun ein forciertes Um-   *
 *                  durch den Zeitgeber-Interrupt ausgeloest wird und in     *
 *                  Assembler in startup.asm implementiert ist. Fuer das     *
 *                  Zusammenspiel mit dem Scheduler ist die Methode          *
 *                  'prepare_preemption' in Scheduler.cc wichtig.            *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 16.12.2016                     *
 *****************************************************************************/

#ifndef Thread_include__
#define Thread_include__

#include "lib/stream/Logger.h"

namespace Kernel {

class Thread {
    friend class SchedulerService;

    friend class Scheduler;

protected:
    // TODO: Remove this
    bool running = true; // For soft exit, if thread uses infinite loop inside run(), use this as condition

    // TODO: Public this
    uint16_t tid; // Thread-ID (wird im Konstruktor vergeben)

public:
    // TODO: Is this a good idea?
    enum Threads : uint16_t {
        IDLE = 0,
        CLEANUP = 1 // TODO: Can cleanup be done in a thread?
    };

public:
    Thread();

    Thread(const Thread &copy) = delete; // Verhindere Kopieren

    // TODO: Rest of constructors

    // TODO: Investigate this
    virtual ~Thread() {
        delete[] stack;
    }

    // Thread aktivieren
    void start() const;

    // Umschalten auf Thread 'next'
    void switchTo(Thread &next);

    // Ask thread to terminate itself
    void suicide() { running = false; }

    // Methode des Threads, muss in Sub-Klasse implementiert werden
    virtual void run() = 0;

private:
    uint32_t *stack;
    uint32_t esp;
};

}

#endif
