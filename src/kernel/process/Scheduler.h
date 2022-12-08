#ifndef Scheduler_include__
#define Scheduler_include__

#include "Thread.h"
#include "lib/memory/UniquePointer.h"
#include "lib/container/Vector.h"
#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

/**
 * This class implements a simple round-robin scheduler.
 */
class Scheduler {
    friend class SchedulerService;

public:
    /**
     * Constructor. Initializes the IdleThread.
     */
    Scheduler();

    MakeUncopyable(Scheduler)

    MakeUnmovable(Scheduler)

    ~Scheduler() = default;

private:
    /**
     * Place a thread in the scheduler's ready_queue.
     *
     * @param thread The thread to add to the ready_queue
     */
    void ready(Memory::unique_ptr<Thread> &&thread);

    /**
     * Start/continue a thread independently of the previous running thread.
     * Is applicable when the previous thread terminated/was killed.
     *
     * @param next The next thread to run
     */
    void start(Container::Vector<Memory::unique_ptr<Thread>>::iterator next);

    /**
     * Start/continue a thread.
     * Is applicable when the previous thread wants to continue execution at a later point.
     *
     * @param prev_raw The raw pointer to the previous running thread
     * @param next The next thread to run
     */
    void start(Thread *prev_raw, Container::Vector<Memory::unique_ptr<Thread>>::iterator next);

    /**
     * Give CPU time to the next waiting thread from the ready_queue.
     */
    void yield();

    /**
     * Block a thread from receiving CPU time.
     * Blocked threads are managed in the block_queue.
     */
    void block();

    /**
     * Allow a blocked thread to receive CPU time again.
     *
     * @param tid
     */
    void deblock(uint16_t tid);

    /**
     * Remove a thread from the ready_queue and give CPU time to the next waiting thread.
     * Exited threads are managed in the exit_queue.
     */
    void exit();

    /**
     * Forcefully exit a thread and retrieve it.
     *
     * @param tid The thread to exit
     * @param ptr The pointer to the killed thread for external use
     */
    void kill(uint16_t tid, Memory::unique_ptr<Thread> *ptr);

    /**
     * Forcefully exit a thread and discard it.
     *
     * @param tid The thread to exit
     */
    void kill(uint16_t tid);

    // TODO: Remove this
    // Asks thread to exit
    // NOTE: I had many problems with killing threads that were stuck in some semaphore
    //       or were involved in any locking mechanisms, so with this a thread can make sure
    //       to "set things right" before exiting itself (but could also be ignored)
    // TODO: "Setting things right" should be done in the thread's destructor
    void nice_kill(uint16_t tid, Memory::unique_ptr<Thread> *ptr);

    void nice_kill(uint16_t tid);

private:
    Container::Vector<Memory::unique_ptr<Thread>> ready_queue;
    Container::Vector<Memory::unique_ptr<Thread>> block_queue;
    Container::Vector<Memory::unique_ptr<Thread>> exit_queue; // TODO: Manage exited threads

    // It makes sense to keep track of the active thread through this as it makes handling the
    // unique_ptr easier and reduces the copying in the vector when cycling through the threads
    // as we don't have to keep the active thread at the front (would only make sense with a queue)
    Container::Vector<Memory::unique_ptr<Thread>>::iterator active = nullptr;

    // TODO: Synchronization
};

}

#endif
