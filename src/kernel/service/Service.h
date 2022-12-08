#ifndef CHURLOS_SERVICE_H
#define CHURLOS_SERVICE_H

#include <cstdint>
#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

/**
 * Implements the super class of all system services.
 * Services abstract certain systems/devices so the used implementation
 * can be changed easily. Every subclass needs a constexpr member ID.
 */
class Service {
public:
    MakeDefault(Service)

    MakeUncopyable(Service)

    MakeUnmovable(Service)

protected:
    /**
     * Assigns each service implementation a unique ID.
     */
    enum Services : uint8_t {
        INTERRUPT = 0,
        SCHEDULER = 1,
        MEMORY = 2,
        EVENT = 3,
        TIME = 4
    };
};

}

#endif //CHURLOS_SERVICE_H
