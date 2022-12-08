#ifndef CHURLOS_SCHEDULERSERVICE_H
#define CHURLOS_SCHEDULERSERVICE_H

#include "Service.h"
#include "lib/memory/UniquePointer.h"
#include "kernel/process/Thread.h"
#include "kernel/process/Scheduler.h"
#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

// NOTE: I mainly have this to be able to implement additional schedulers easily

/**
 * This class implements the scheduling system service.
 */
class SchedulerService : public Service {
public:
    static const constexpr uint8_t ID = Service::SCHEDULER;

public:
    MakeDefault(SchedulerService)

    MakeUncopyable(SchedulerService)

    MakeUnmovable(SchedulerService)

    /**
     * Construct a thread inplace and add it to the schedulers ready queue.
     *
     * @tparam T The type of thread to construct
     * @param args The arguments for the thread's constructor
     * @return The constructed thread's id
     */
    template<typename T, typename... Args>
    uint32_t ready(Args... args) {
        Memory::unique_ptr<Thread> thread = Memory::make_unique<T>(std::forward<Args>(args)...);
        uint32_t tid = thread->tid;

        scheduler.ready(std::move(thread));

        return tid;
    }

    /**
     * Starts the first thread in the schedulers ready_queue.
     */
    void startScheduling();

    /**
     * Get the thread id of the currently running thread.
     *
     * @return The id of the active thread
     */
    [[nodiscard]] uint16_t active() const;

    /**
     * Interrupts current thread execution and switch to the next thread.
     */
    void yield();

    /**
     * Move a thread to from the schedulers ready queue to its block queue.
     */
    void block();

    /**
     * Move a thread from the schedulers block queue to its ready queue.
     *
     * @param tid The thread to unblock
     */
    void deblock(uint16_t tid);

    /**
     * Exit a thread.
     */
    void exit();

    void suicide(uint16_t tid); // TODO: Remove

    /**
     * Forcefully exit a thread.
     *
     * @param tid The thread to kill
     */
    void kill(uint16_t tid);

    // TODO: Thread that cleans up exited threads

private:
    Scheduler scheduler;
};

}

#endif //CHURLOS_SCHEDULERSERVICE_H
