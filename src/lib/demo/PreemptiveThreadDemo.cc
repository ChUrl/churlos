#include "PreemptiveThreadDemo.h"
#include "lib/util/System.h"
#include "kernel/system/System.h"
#include "kernel/service/SchedulerService.h"

void PreemptiveLoopThread::run() {
    int cnt = 0;

    while (running) {
        // Basic synchronization by semaphore
        Util::System::out.lock();

        // Saving + restoring Util::System::out position doesn't help much as preemption still occurs
        CGA_Stream::setpos(55, id);
        Util::System::out << fillw(3) << id << fillw(0) << ": " << dec << cnt++ << endl;

        Util::System::out.unlock();
    }

    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    schedulerService.exit();
}

void PreemptiveThreadDemo::run() {
    Util::System::out.lock();
    Util::System::out.clear();

    Util::System::out << "Preemptive Thread Demo:" << endl;

    Util::System::out << "Readying LoopThreads" << endl;
    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    for (unsigned int i = 0; i < number_of_threads; ++i) {
        schedulerService.ready<PreemptiveLoopThread>(i);
    }

    Util::System::out << "Exiting main thread" << endl;
    Util::System::out.unlock();
    schedulerService.exit();
}
