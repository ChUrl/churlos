#include "System.h"

namespace Kernel {

Container::Array<Kernel::Service *, 256> System::systemServices = {nullptr};

}