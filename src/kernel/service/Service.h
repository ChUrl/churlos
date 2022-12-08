#ifndef CHURLOS_SERVICE_H
#define CHURLOS_SERVICE_H

#include <cstdint>

namespace Kernel {

class Service {
public:
    Service() = default;

    // TODO: Macros for unmovable, uncopyable

    Service(const Service &copy) = delete;

    Service(Service &&move) = delete;

    Service operator=(const Service &copy) = delete;

    Service &operator=(Service &&move) = delete;

    virtual ~Service() = default;
};

}

#endif //CHURLOS_SERVICE_H
