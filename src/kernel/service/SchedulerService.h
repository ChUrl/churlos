#ifndef CHURLOS_SCHEDULERSERVICE_H
#define CHURLOS_SCHEDULERSERVICE_H

#include "Service.h"
#include "lib/memory/UniquePointer.h"
#include "kernel/process/Thread.h"
#include "kernel/process/Scheduler.h"

namespace Kernel {

/**
 * This class implements the scheduling system service.
 */
class SchedulerService : public Service {
public:
    static const constexpr uint8_t ID = Service::SCHEDULER;

public:
    SchedulerService() = default;

    // TODO: Rest of constructors

    // Helper that directly constructs the thread, then readys it
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

    [[nodiscard]] uint16_t active() const;

    /**
     * Interrupts current thread execution and switch to the next thread.
     */
    void yield();

    void block();

    void deblock(uint16_t tid);

    void exit();

    void suicide(uint16_t tid);

    void kill(uint16_t tid);

    // TODO: Thread that cleans up exited threads

private:
    Scheduler scheduler;
};

}

#endif //CHURLOS_SCHEDULERSERVICE_H
