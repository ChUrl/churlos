#ifndef IdleThread_include__
#define IdleThread_include__

#include "kernel/system/Globals.h"
#include "Thread.h"
#include "kernel/service/SchedulerService.h"
#include "kernel/system/System.h"

namespace Kernel {

class IdleThread : public Thread {
public:
    IdleThread(const Thread &copy) = delete;  // Verhindere Kopieren

    IdleThread() {
        tid = Thread::IDLE; // The IdleThread gets a fixed id for convenience
    }

    [[noreturn]] void run() override {
        auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
        while (true) {
            schedulerService.yield();
        }
    }
};

}

#endif
