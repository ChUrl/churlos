#ifndef MainMenu_Inlucde_H_
#define MainMenu_Inlucde_H_

#include "kernel/system/Globals.h"
#include "kernel/process/Thread.h"
#include "kernel/event/KeyEventListener.h"

class MainMenu : public Thread {
private:
    KeyEventListener listener;

public:
    MainMenu(const MainMenu& copy) = delete;

    MainMenu() : Thread("MainMenu"), listener(tid) {
        kevman.subscribe(listener);
    }

    ~MainMenu() override {
        kevman.unsubscribe(listener);
    }

    void run() override;
};

#endif
