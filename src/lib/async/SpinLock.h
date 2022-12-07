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

namespace Async {

class SpinLock {
private:
    uint32_t lock;
    uint32_t *ptr;

public:
    SpinLock(const SpinLock &copy) = delete;  // Verhindere Kopieren

    SpinLock() : lock(0), ptr(&lock) {}

    void acquire();

    void release();
};

}

#endif
