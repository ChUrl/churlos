#ifndef CHURLOS_KERNEL_SYSTEM_H
#define CHURLOS_KERNEL_SYSTEM_H

#include "kernel/service/Service.h"
#include "lib/container/Array.h"

namespace Kernel {

class System {
public:
    template<typename T>
    static void registerService() {
        static_assert(std::is_base_of_v<Service, T>, "Tried to register invalid service!");

        if (isServiceRegistered<T>()) {
            // TODO: Exception
        }

        systemServices[T::ID] = new T();
    };

    template<typename T>
    static bool isServiceRegistered() {
        static_assert(std::is_base_of_v<Service, T>, "Tried to query invalid service!");

        return systemServices[T::ID] != nullptr;
    }

    template<typename T>
    static T &getService() {
        static_assert(std::is_base_of_v<Service, T>, "Tried to retrieve invalid service!");

        if (!isServiceRegistered<T>()) {
            // TODO: Exception
        }

        // Might be dangerous (?), but dynamic_cast needs runtime type information
        return *reinterpret_cast<T *>(systemServices[T::ID]);
    }

private:
    static Container::Array<Kernel::Service *, 256> systemServices; // Service ID determines array position
};

}

#endif //CHURLOS_KERNEL_SYSTEM_H
