#include "KeyEventManager.h"
#include "kernel/system/Globals.h"
#include "kernel/service/SchedulerService.h"
#include "kernel/system/System.h"

namespace Kernel {

void KeyEventManager::subscribe(KeyEventListener &sub) {
    log.debug() << "Subscribe, Thread ID: " << dec << sub.tid << endl;
    listeners.push_back(&sub);
}

void KeyEventManager::unsubscribe(KeyEventListener &unsub) {
    log.debug() << "Unsubscribe, Thread ID: " << dec << unsub.tid << endl;
    for (Container::Vector<KeyEventListener *>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        if ((*it)->tid == unsub.tid) {
            listeners.erase(it);
            return;
        }
    }
}

void KeyEventManager::broadcast(char c) {
    log.trace() << "Beginning Broadcast" << endl;
    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    for (KeyEventListener *listener: listeners) {
        log.trace() << "Broadcasting " << c << " to Thread ID: " << dec << listener->tid << endl;
        listener->trigger(c);
        schedulerService.deblock(listener->tid);
    }
}

}
