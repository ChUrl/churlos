#ifndef VectorDemo_include__
#define VectorDemo_include__

#include "kernel/system/Globals.h"
#include "kernel/process/Thread.h"
#include "lib/container//Vector.h"

class VectorDemo : public Kernel::Thread {
public:
    VectorDemo(const VectorDemo &copy) = delete;

    VectorDemo() = default;

    void run() override;

private:
    static NamedLogger log;
};

#endif
