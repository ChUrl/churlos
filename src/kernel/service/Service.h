#ifndef CHURLOS_SERVICE_H
#define CHURLOS_SERVICE_H

#include <cstdint>

namespace Kernel {

/**
 * Implements the super class of all system services.
 * Services abstract certain systems/devices so the used implementation
 * can be changed easily. Every subclass needs a constexpr member ID.
 */
class Service {
public:
    Service() = default;

    // TODO: Macros for unmovable, uncopyable

    Service(const Service &copy) = delete;

    Service(Service &&move) = delete;

    Service operator=(const Service &copy) = delete;

    Service &operator=(Service &&move) = delete;

    virtual ~Service() = default;

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
