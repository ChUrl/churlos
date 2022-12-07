#ifndef ArrayDemo_include__
#define ArrayDemo_include__

#include "kernel/system/Globals.h"
#include "lib/util/Array.h"

class ArrayDemo : public Thread {
public:
    ArrayDemo(const ArrayDemo& copy) = delete;

    ArrayDemo() : Thread("ArrayDemo") {}

    void run() override;
};

#endif
