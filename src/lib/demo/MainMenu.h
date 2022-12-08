#ifndef MainMenu_Inlucde_H_
#define MainMenu_Inlucde_H_

#include "kernel/system/Globals.h"
#include "kernel/process/Thread.h"
#include "kernel/event/KeyEventListener.h"

class MainMenu : public Kernel::Thread {
private:
    Kernel::KeyEventListener listener;

public:
    MainMenu(const MainMenu &copy) = delete;

    MainMenu() : listener(tid) {
        Kernel::kevman.subscribe(listener);
    }

    ~MainMenu() override {
        Kernel::kevman.unsubscribe(listener);
    }

    void run() override;
};

#endif
