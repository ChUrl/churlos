#ifndef PCSPKdemo_INCLUDE_H_
#define PCSPKdemo_INCLUDE_H_

#include "kernel/system/Globals.h"
#include "kernel/process/Thread.h"

class PCSPKdemo : public Kernel::Thread {
private:
    void (*melody)();  // Allow to pass a melody to play when initializing the demo

public:
    PCSPKdemo(const PCSPKdemo& copy) = delete;

    PCSPKdemo(void (*melody)()) : Thread("PCSPKdemo"), melody(melody) {}

    ~PCSPKdemo() override {
        Device::PCSPK::off();
    }

    void run() override;
};

#endif
