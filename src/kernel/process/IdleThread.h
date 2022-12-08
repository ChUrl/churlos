#ifndef IdleThread_include__
#define IdleThread_include__

#include "Thread.h"
#include "kernel/service/SchedulerService.h"
#include "kernel/system/System.h"
#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

class IdleThread : public Thread {
public:
    IdleThread() {
        tid = Thread::IDLE; // The IdleThread gets a fixed id for convenience
    }

    MakeUncopyable(IdleThread)

    MakeUnmovable(IdleThread)

    ~IdleThread() override = default;

    [[noreturn]] void run() override {
        auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
        while (true) {
            schedulerService.yield();
        }
    }
};

}

#endif
