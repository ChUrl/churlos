#include "System.h"

namespace Kernel {

// TODO: This initializer ({nullptr}) isn't implemented yet
Container::Array<Kernel::Service *, 256> System::systemServices = {nullptr};

}