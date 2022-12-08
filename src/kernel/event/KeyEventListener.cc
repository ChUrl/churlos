#include "kernel/event/KeyEventListener.h"
#include "kernel/system/Globals.h"
#include "kernel/service/SchedulerService.h"
#include "kernel/system/System.h"

namespace Kernel {

void KeyEventListener::trigger(char c) {
    lastChar = c;
}

char KeyEventListener::waitForKeyEvent() const {
    Logger::instance() << DEBUG << "KEvLis:: Thread with id: " << tid << " waiting for key event" << endl;
    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    schedulerService.block();
    return lastChar;  // This is only executed after thread is woken up by manager
}

}
