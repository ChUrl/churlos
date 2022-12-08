/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers. *
 *                  Rechenbereite Threads werden in 'readQueue' verwaltet.   *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 22.8.2016                      *
 *****************************************************************************/

#ifndef Scheduler_include__
#define Scheduler_include__

#include "Thread.h"
#include "lib/memory/UniquePointer.h"
#include "lib/stream/Logger.h"
#include "lib/container/Vector.h"

namespace Kernel {

class Scheduler {
    friend class SchedulerService;

    friend class IdleThread;

public:
    /**
     * Constructor. Initializes the IdleThread.
     */
    Scheduler();

    Scheduler(const Scheduler &copy) = delete;  // Verhindere Kopieren

    // TODO: Rest of constructors

private:
    [[nodiscard]] uint16_t get_active() const {
        return (*active)->tid;
    }

    void ready(Memory::unique_ptr<Thread> &&thread);

    // Roughly the old dispatcher functionality
    void start(Container::Vector<Memory::unique_ptr<Thread>>::iterator next); // Start next without prev

    // Switch from prev to next
    void switch_to(Thread *prev_raw, Container::Vector<Memory::unique_ptr<Thread>>::iterator next);

    // CPU freiwillig abgeben und Auswahl des naechsten Threads
    void yield(); // Returns when only the idle thread runs

    // Blocks current thread (move to block_queue)
    void block(); // Returns on error because we don't have exceptions

    // Deblock by tid (move to ready_queue)
    void deblock(uint16_t tid);

    // Thread terminiert sich selbst
    // NOTE: When a thread exits itself it will disappear...
    //       Maybe put exited threads in an exited queue?
    //       Then they would have to be acquired from there to exit...
    void exit();  // Returns on error because we don't have exceptions

    // Thread mit 'Gewalt' terminieren
    void kill(uint16_t tid, Memory::unique_ptr<Thread> *ptr);

    void kill(uint16_t tid) { kill(tid, nullptr); }

    // Asks thread to exit
    // NOTE: I had many problems with killing threads that were stuck in some semaphore
    //       or were involved in any locking mechanisms, so with this a thread can make sure
    //       to "set things right" before exiting itself (but could also be ignored)
    void nice_kill(uint16_t tid, Memory::unique_ptr<Thread> *ptr);

    void nice_kill(uint16_t tid) { nice_kill(tid, nullptr); }

private:
    Container::Vector<Memory::unique_ptr<Thread>> ready_queue;
    Container::Vector<Memory::unique_ptr<Thread>> block_queue;
    Container::Vector<Memory::unique_ptr<Thread>> exited; // TODO: Manage exited threads

    // It makes sense to keep track of the active thread through this as it makes handling the
    // unique_ptr easier and reduces the copying in the vector when cycling through the threads
    // as we don't have to keep the active thread at the front (would only make sense with a queue)
    Container::Vector<Memory::unique_ptr<Thread>>::iterator active = nullptr;

    // TODO: Synchronization
};

}

#endif
