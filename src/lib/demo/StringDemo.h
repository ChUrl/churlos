#ifndef StringDemo_include__
#define StringDemo_include__

#include "kernel/system/Globals.h"

class StringDemo : public Kernel::Thread {
public:
    StringDemo(const StringDemo& copy) = delete;

    StringDemo() : Thread("StringDemo") {}

    void run() override;
};

#endif
