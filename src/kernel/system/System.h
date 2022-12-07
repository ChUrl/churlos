#ifndef CHURLOS_SYSTEM_H
#define CHURLOS_SYSTEM_H

#include "kernel/service/Service.h"
#include "lib/stream/CGA_Stream.h"
#include "lib/container/Vector.h"

namespace Util {

class System {
public:
    static CGA_Stream out;

private:
    static Container::Vector<Kernel::Service> systemServices;
};

}

#endif //CHURLOS_SYSTEM_H
