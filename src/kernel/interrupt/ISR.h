#ifndef ISR_include__
#define ISR_include__

#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

/**
 * This class implements an interrupt service routine.
 */
class ISR {
    friend class IntDispatcher;

public:
    MakeDefault(ISR)

    MakeUncopyable(ISR)

    MakeUnmovable(ISR)

protected:
    /**
     * This function gets called when an interrupt occurs and
     * an interrupt handler is registered for the vector number.
     */
    virtual void trigger() = 0;
};

}

#endif
