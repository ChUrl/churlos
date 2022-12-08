#ifndef StringDemo_include__
#define StringDemo_include__

#include "kernel/system/Globals.h"

class StringDemo : public Kernel::Thread {
private:
    static NamedLogger log;

public:
    StringDemo(const StringDemo &copy) = delete;

    StringDemo() = default;

    void run() override;
};

#endif
