/*****************************************************************************
 *                                                                           *
 *                        K E Y B O A R D D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#ifndef KeyboardDemo_include__
#define KeyboardDemo_include__

#include "kernel/system/Globals.h"
#include "kernel/process/Thread.h"
#include "kernel/event/KeyEventListener.h"

class KeyboardDemo : public Kernel::Thread {
private:
    Kernel::KeyEventListener listener;

public:
    KeyboardDemo(const KeyboardDemo& copy) = delete;

    KeyboardDemo() : Thread("KeyboardDemo"), listener(tid) {
        Kernel::kevman.subscribe(listener);
    }

    // Base class destructor will be called automatically
    ~KeyboardDemo() override {
        if (running) {
            // NOTE: If the thread was exited nicely it can unlock before destructor,
            //       but on forced kill Kernel::kout has to be unlocked in the destructor.
            //       This is bad since it could release the lock although some other
            //       thread set it (so use nice_kill)
            Kernel::kout.unlock();
        }
        Kernel::kevman.unsubscribe(listener);
    }

    void run() override;
};

#endif
