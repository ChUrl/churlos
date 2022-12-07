#include "PreemptiveThreadDemo.h"

void PreemptiveLoopThread::run() {
    int cnt = 0;

    while (running) {
        // Basic synchronization by semaphore
        Kernel::kout.lock();

        // Saving + restoring Kernel::kout position doesn't help much as preemption still occurs
        CGA_Stream::setpos(55, id);
        Kernel::kout << fillw(3) << id << fillw(0) << ": " << dec << cnt++ << endl;

        Kernel::kout.unlock();
    }

    Kernel::scheduler.exit();
}

void PreemptiveThreadDemo::run() {
    Kernel::kout.lock();
    Kernel::kout.clear();

    Kernel::kout << "Preemptive Thread Demo:" << endl;

    Kernel::kout << "Readying LoopThreads" << endl;
    for (unsigned int i = 0; i < number_of_threads; ++i) {
        Kernel::scheduler.ready<PreemptiveLoopThread>(i);
    }

    Kernel::kout << "Exiting main thread" << endl;
    Kernel::kout.unlock();
    Kernel::scheduler.exit();
}
