#ifndef ArrayDemo_include__
#define ArrayDemo_include__

#include "kernel/system/Globals.h"
#include "lib/container/Array.h"

class ArrayDemo : public Kernel::Thread {
public:
    ArrayDemo(const ArrayDemo &copy) = delete;

    ArrayDemo() = default;

    void run() override;
};

#endif
