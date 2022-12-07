#include "PCSPKdemo.h"

void PCSPKdemo::run() {
    Kernel::kout.lock();
    Kernel::kout.clear();
    Kernel::kout << "Playing..." << endl;
    Kernel::kout.unlock();

    (*melody)();  // This syntax is confusing as hell

    Kernel::kout.lock();
    Kernel::kout << "Finished" << endl;
    Kernel::kout.unlock();

    Kernel::scheduler.exit();
}
