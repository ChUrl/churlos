#include "Scheduler.h"
#include "IdleThread.h"
#include "device/cpu/CPU.h"
#include <utility>

namespace Kernel {

Scheduler::Scheduler() {
    ready_queue.push_back(Memory::make_unique<IdleThread>());
    // TODO: Cleanup thread
}

void Scheduler::ready(Memory::unique_ptr<Thread> &&thread) {
    Device::CPU::disable_int();
    ready_queue.push_back(std::move(thread));
    Device::CPU::enable_int();
}

void Scheduler::start(Container::Vector<Memory::unique_ptr<Thread>>::iterator next) {
    active = next;
    if (active >= ready_queue.end()) {
        // By jumping to the start of the queue we can always start the next ready thread by
        // incrementing the "active" iterator
        active = ready_queue.begin();
    }
    (*active)->start(); // First dereference the Iterator, then the unique_ptr to get the Thread
}

// Use a raw pointer for the previous thread because the unique_ptr of that thread is still in the ready_queue,
// this way we don't need to take care of moving it to this function and then back to the ready_queue
void Scheduler::start(Thread *prev_raw, Container::Vector<Memory::unique_ptr<Thread>>::iterator next) {
    active = next;
    if (active >= ready_queue.end()) {
        active = ready_queue.begin();
    }
    prev_raw->switchTo(**active); // First dereference the Iterator, then the unique_ptr to get the Thread
}

void Scheduler::yield() {
    Device::CPU::disable_int();

    if (ready_queue.size() == 1) {
        Device::CPU::enable_int();
        return;
    }

    start((*active).get(), active + 1); // prev_raw is valid since no thread was killed/deleted
}

void Scheduler::block() {
    Device::CPU::disable_int();

    if (ready_queue.size() == 1) {
        Device::CPU::enable_int();
        return;
    }

    Thread *prev_raw = (*active).get(); // Has to be done before erasing/adding the thread to the block_queue
    std::size_t pos = distance(ready_queue.begin(), active); // Current thread's index in ready_queue
    block_queue.push_back(std::move(ready_queue[pos])); // Leaves an "empty shell" in the ready_queue

    start(prev_raw, ready_queue.erase(active)); // prev_raw is valid as it was taken before vector move/erase
}

void Scheduler::deblock(uint16_t tid) {
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

void Scheduler::exit() {
    Device::CPU::disable_int();

    if (ready_queue.size() == 1) {
        Device::CPU::enable_int();
        return;
    }

    start(ready_queue.erase(active)); // erase returns the next iterator after the erased element
    // cannot use switch_to here as the previous thread no longer
    // exists (was deleted by erase)

    // Interrupts werden in Thread_switch in Thread.asm wieder zugelassen
    // dispatch kehrt nicht zurueck
}

void Scheduler::kill(uint16_t tid, Memory::unique_ptr<Thread> *ptr) {
    Device::CPU::disable_int();

    uint16_t prev_tid = (*active)->tid;

    // Block queue, can always kill
    for (auto it = block_queue.begin(); it != block_queue.end(); ++it) {
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

void Scheduler::kill(uint16_t tid) {
    kill(tid, nullptr);
}

// TODO: Can't retrieve the thread right now because it's not clear when it's finished,
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

void Scheduler::nice_kill(uint16_t tid) {
    nice_kill(tid, nullptr);
}

}
