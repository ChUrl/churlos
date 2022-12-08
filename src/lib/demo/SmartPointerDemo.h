#ifndef SmartPointerDemo_include__
#define SmartPointerDemo_include__

#include "kernel/system/Globals.h"

class SmartPointerDemo : public Kernel::Thread {
public:
    SmartPointerDemo(const SmartPointerDemo &copy) = delete;

    SmartPointerDemo() = default;

    void run() override;

private:
    static NamedLogger log;
};

#endif
