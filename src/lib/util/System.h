#ifndef CHURLOS_LIB_SYSTEM_H
#define CHURLOS_LIB_SYSTEM_H

#include "lib/stream/CGA_Stream.h"

namespace Util {

/**
 * This class implements the system utility class that provides streams and other global objects.
 */
class System {
public:
    // TODO: Something like "CGA_Stream" shouldn't exists, the stream should not be coupled to the output device
    // TODO: There should be an "in" and "error" stream
    static CGA_Stream out;

};

}

#endif //CHURLOS_LIB_SYSTEM_H
