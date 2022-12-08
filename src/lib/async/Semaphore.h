#ifndef Semaphore_include__
#define Semaphore_include__

#include "SpinLock.h"
#include "kernel/process/Thread.h"
#include "lib/container/Vector.h"
#include "lib/util/RestrictedConstructors.h"

namespace Async {

class Semaphore {
public:
    /**
     * Initialize the semaphore and it's counter.
     *
     * @param c The semaphore counter
     */
    explicit Semaphore(uint32_t c);

    MakeUncopyable(Semaphore)

    MakeUnmovable(Semaphore)

    ~Semaphore() = default;

    /**
     * Wait in queue until the semaphore can be acquired.
     */
    void acquire();

    /**
     * Release the semaphore.
     */
    void release();

private:
    SpinLock lock;
    Container::Vector<unsigned int> wait_queue; // TODO: Replace with a queue (linked list)

    uint32_t counter;
};

}

#endif
