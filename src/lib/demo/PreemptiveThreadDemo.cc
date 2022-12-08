#include "PreemptiveThreadDemo.h"
#include "lib/util/System.h"

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

    Kernel::scheduler.exit();
}

void PreemptiveThreadDemo::run() {
    Util::System::out.lock();
    Util::System::out.clear();

    Util::System::out << "Preemptive Thread Demo:" << endl;

    Util::System::out << "Readying LoopThreads" << endl;
    for (unsigned int i = 0; i < number_of_threads; ++i) {
        Kernel::scheduler.ready<PreemptiveLoopThread>(i);
    }

    Util::System::out << "Exiting main thread" << endl;
    Util::System::out.unlock();
    Kernel::scheduler.exit();
}
