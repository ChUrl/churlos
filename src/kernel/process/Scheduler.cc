#include "Scheduler.h"
#include "IdleThread.h"
#include <utility>

namespace Kernel {

Scheduler::Scheduler() {
    ready_queue.push_back(Memory::make_unique<IdleThread>());
    // TODO: Cleanup thread
}

void Scheduler::start(Container::Vector<Memory::unique_ptr<Thread>>::iterator next) {
    active = next;
    if (active >= ready_queue.end()) {
        active = ready_queue.begin();
    }
    (*active)->start();  // First dereference the Iterator, then the unique_ptr to get Thread
}

void Scheduler::switch_to(Thread *prev_raw, Container::Vector<Memory::unique_ptr<Thread>>::iterator next) {
    active = next;
    if (active >= ready_queue.end()) {
        active = ready_queue.begin();
        // log.debug() << "Scheduler::switch_to started different thread than passed" << endl;
    }
    prev_raw->switchTo(**active);
}

/*****************************************************************************
 * Methode:         Scheduler::ready                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread in readyQueue eintragen.                          *
 *****************************************************************************/
void Scheduler::ready(Memory::unique_ptr<Thread> &&thread) {
    Device::CPU::disable_int();
    ready_queue.push_back(std::move(thread));
    Device::CPU::enable_int();
}

/*****************************************************************************
 * Methode:         Scheduler::exit                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread ist fertig und terminiert sich selbst. Hier muss  *
 *                  nur auf den naechsten Thread mithilfe des Dispatchers    *
 *                  umgeschaltet werden. Der aktuell laufende Thread ist     *
 *                  nicht in der readyQueue.                                 *
 *****************************************************************************/
void Scheduler::exit() {

    /* hier muss Code eingefuegt werden */

    // Thread-Wechsel durch PIT verhindern
    Device::CPU::disable_int();

    if (ready_queue.size() == 1) {
        Device::CPU::enable_int();
        return;
    }

    start(ready_queue.erase(active));  // erase returns the next iterator after the erased element
    // cannot use switch_to here as the previous thread no longer
    // exists (was deleted by erase)

    // Interrupts werden in Thread_switch in Thread.asm wieder zugelassen
    // dispatch kehrt nicht zurueck
}

/*****************************************************************************
 * Methode:         Scheduler::kill                                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread mit 'Gewalt' terminieren. Er wird aus der         *
 *                  readyQueue ausgetragen und wird dann nicht mehr aufge-   *
 *                  rufen. Der Aufrufer dieser Methode muss ein anderer      *
 *                  Thread sein.                                             *
 *                                                                           *
 * Parameter:                                                                *
 *      that        Zu terminierender Thread                                 *
 *****************************************************************************/
void Scheduler::kill(uint16_t tid, Memory::unique_ptr<Thread> *ptr) {
    Device::CPU::disable_int();

    uint16_t prev_tid = (*active)->tid;

    // Block queue, can always kill
    for (Container::Vector<Memory::unique_ptr<Thread>>::iterator it = block_queue.begin();
         it != block_queue.end(); ++it) {
        if ((*it)->tid == tid) {
            // Found thread to kill

            if (ptr != nullptr) {
                // Move old thread out of queue to return it
                uint16_t pos = distance(block_queue.begin(), it);
                *ptr = std::move(block_queue[pos]);  // Return the killed thread
            }

            // Just erase from queue, do not need to switch
            block_queue.erase(it);

            Device::CPU::enable_int();
            return;
        }
    }

    // Ready queue, can't kill last one
    if (ready_queue.size() == 1) {
        Device::CPU::enable_int();
        return;
    }

    for (Container::Vector<Memory::unique_ptr<Thread>>::iterator it = ready_queue.begin();
         it != ready_queue.end(); ++it) {
        if ((*it)->tid == tid) {
            // Found thread to kill

            if (ptr != nullptr) {
                // Move old thread out of queue to return it
                uint16_t pos = distance(ready_queue.begin(), it);
                *ptr = std::move(ready_queue[pos]);  // Return the killed thread
            }

            if (tid == prev_tid) {
                // If we killed the active thread we need to switch to another one

                // Switch to current active after old active was removed
                start(ready_queue.erase(it));
            }

            // Just erase from queue, do not need to switch
            ready_queue.erase(it);

            Device::CPU::enable_int();
            return;
        }
    }

    Device::CPU::enable_int();
}

// TODO: Can't retrive the thread right now because it's not clear when it's finished,
//       maybe introduce a exited_queue and get it from there
void Scheduler::nice_kill(uint16_t tid, Memory::unique_ptr<Thread> *ptr) {
    Device::CPU::disable_int();

    for (Memory::unique_ptr<Thread> &thread: block_queue) {
        if (thread->tid == tid) {
            thread->suicide();
            deblock(tid);
            Device::CPU::enable_int();
            return;
        }
    }

    for (Memory::unique_ptr<Thread> &thread: ready_queue) {
        if (thread->tid == tid) {
            thread->suicide();
            Device::CPU::enable_int();
            return;
        }
    }

    Device::CPU::enable_int();
}

/*****************************************************************************
 * Methode:         Scheduler::yield                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    CPU::freiwillig abgeben und Auswahl des naechsten Threads.*
 *                  Naechsten Thread aus der readyQueue holen, den aktuellen *
 *                  in die readyQueue wieder eintragen. Das Umschalten soll  *
 *                  mithilfe des Dispatchers erfolgen.                       *
 *                                                                           *
 *                  Achtung: Falls nur der Idle-Thread läuft, so ist die     *
 *                           readyQueue leer.                                *
 *****************************************************************************/
void Scheduler::yield() {

    /* hier muss Code eingefuegt werden */

    // Thread-Wechsel durch PIT verhindern
    Device::CPU::disable_int();

    if (ready_queue.size() == 1) {
        Device::CPU::enable_int();
        return;
    }
    switch_to((*active).get(), active + 1);  // prev_raw is valid since no thread was killed/deleted
}

/*****************************************************************************
 * Methode:         Scheduler::block                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Aufrufer ist blockiert. Es soll auf den naechsten Thread *
 *                  umgeschaltet werden. Der Aufrufer soll nicht in die      *
 *                  readyQueue eingefuegt werden und wird extern verwaltet.  *
 *                  Wird bei uns nur fuer Semaphore verwendet. Jede Semaphore*
 *                  hat eine Warteschlange wo der Thread dann verwaltet wird.*
 *                  Die Methode kehrt nicht zurueck, sondern schaltet um.    *
 *****************************************************************************/
void Scheduler::block() {

    /* hier muss Code eingefuegt werden */

    Device::CPU::disable_int();

    if (ready_queue.size() == 1) {
        Device::CPU::enable_int();
        return;
    }

    Thread *prev_raw = (*active).get();
    std::size_t pos = distance(ready_queue.begin(), active);
    block_queue.push_back(std::move(ready_queue[pos]));

    switch_to(prev_raw, ready_queue.erase(active));  // prev_raw is valid as thread was moved before vector erase
}

/*****************************************************************************
 * Methode:         Scheduler::deblock                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread 'that' deblockieren. 'that' wird nur in die       *
 *                  readyQueue eingefuegt und dann zurueckgekehrt. In der    *
 *                  einfachsten Form entspricht diese Funktion exakt 'ready' *
 *                  Man koennte alternativ aber den deblockierten Thread auch*
 *                  am Anfang der readyQueue einfuegen, um ihn zu beorzugen. *
 *                                                                           *
 * Parameter:       that:  Thread der deblockiert werden soll.               *
 *****************************************************************************/
void Scheduler::deblock(uint16_t tid) {

    /* hier muss Code eingefuegt werden */

    Device::CPU::disable_int();

    for (Container::Vector<Memory::unique_ptr<Thread>>::iterator it = block_queue.begin();
         it != block_queue.end(); ++it) {
        if ((*it)->tid == tid) {
            // Found thread with correct tid

            std::size_t pos = distance(block_queue.begin(), it);
            ready_queue.insert(active + 1, std::move(block_queue[pos]));  // We insert the thread after the active
            // thread to prefer deblocked threads
            block_queue.erase(it);
            Device::CPU::enable_int();
            return;
        }
    }

    Device::CPU::enable_int();
}

}
