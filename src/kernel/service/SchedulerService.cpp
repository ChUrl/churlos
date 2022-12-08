#include "SchedulerService.h"

namespace Kernel {

void SchedulerService::startScheduling() {
    scheduler.start(scheduler.ready_queue.begin());
}

uint16_t SchedulerService::active() const {
    return scheduler.get_active();
}

void SchedulerService::yield() {
    scheduler.yield();
}

void SchedulerService::block() {
    scheduler.block();
}

void SchedulerService::deblock(uint16_t tid) {
    scheduler.deblock(tid);
}

void SchedulerService::exit() {
    scheduler.exit();
}

void SchedulerService::suicide(uint16_t tid) {
    scheduler.nice_kill(tid);
}

void SchedulerService::kill(uint16_t tid) {
    scheduler.kill(tid);
}

}
