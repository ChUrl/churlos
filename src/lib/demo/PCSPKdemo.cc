#include "PCSPKdemo.h"
#include "lib/util/System.h"
#include "kernel/system/System.h"
#include "kernel/service/SchedulerService.h"

void PCSPKdemo::run() {
    Util::System::out.lock();
    Util::System::out.clear();
    Util::System::out << "Playing..." << endl;
    Util::System::out.unlock();

    (*melody)();  // This syntax is confusing as hell

    Util::System::out.lock();
    Util::System::out << "Finished" << endl;
    Util::System::out.unlock();

    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    schedulerService.exit();
}
