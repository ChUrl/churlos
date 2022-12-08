#ifndef Thread_include__
#define Thread_include__

#include <cstdint>
#include "lib/util/RestrictedConstructors.h"

namespace Kernel {

class Thread {
    friend class Scheduler;

public:
    uint16_t tid;

    /**
     * Reserved thread ids.
     */
    enum Threads : uint16_t {
        IDLE = 0,
        CLEANUP = 1 // TODO: Can cleanup be done in a thread?
    };

public:
    Thread();

    MakeUncopyable(Thread)

    MakeUnmovable(Thread)

    virtual ~Thread() {
        delete[] stack;
    }

    virtual void run() = 0;

private:
    /**
     * Start or continue this thread.
     * The thread's state will be restored by loading the stack pointer saved
     * in the "esp" member variable.
     */
    void start() const;

    /**
     * Switch from this thread to another thread.
     *
     * @param next The thread to switch to
     */
    void switchTo(Thread &next);

    void suicide() { running = false; }

protected:
    bool running = true; // TODO: Remove

private:
    /**
     * This function will be called when the thread is executed for the first time.
     * It's address is manually placed as return address on the thread's stack.
     *
     * @param thread The thread containing the "run" member function that will be called
     */
    [[noreturn]] static void kickoff(Thread *thread);

private:
    static const constexpr uint16_t STACK_SIZE = 1024;

    uint32_t *stack; // Pointer to the thread's stack
    uint32_t esp; // Store the stack pointer to allow interrupting/resuming thread execution
};

}

#endif
