/*****************************************************************************
 *                                                                           *
 *                              S P I N L O C K                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Spinlocks mithilfe der cmpxchg     *
 *                  Instruktion.                                             *
 *                                                                           *
 * Autor:           Michael Schoettner, 2.2.2018                             *
 *****************************************************************************/

#ifndef SpinLock_include__
#define SpinLock_include__

#include <cstdint>
#include "lib/util/RestrictedConstructors.h"

namespace Async {

class SpinLock {
public:
    SpinLock();

    MakeUncopyable(SpinLock)

    MakeUnmovable(SpinLock)

    ~SpinLock() = default;

    /**
     * Acquire the spin lock.
     */
    void acquire();

    /**
     * Release the spin lock.
     */
    void release();

private:
    uint32_t lock;
    uint32_t *ptr;
};

}

#endif
