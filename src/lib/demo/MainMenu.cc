#include "MainMenu.h"
#include "ArrayDemo.h"
#include "HeapDemo.h"
#include "KeyboardDemo.h"
#include "PagingDemo.h"
#include "PCSPKdemo.h"
#include "PreemptiveThreadDemo.h"
#include "SmartPointerDemo.h"
#include "StringDemo.h"
#include "TextDemo.h"
#include "VBEdemo.h"
#include "VectorDemo.h"

void print_demo_menu() {
    Util::System::out.lock();
    Util::System::out.clear();
    Util::System::out << "Demo Menu, press number to start, k/K to kill:\n"
                      << "1 - Text Demo\n"
                      << "2 - PCSPK Demo\n"
                      << "3 - Keyboard Demo\n"
                      << "4 - Heap Demo\n"
                      << "5 - VBE Demo\n"
                      << "6 - Paging Demo\n"
                      << "7 - Preemption Demo\n"
                      << "Extra demos:\n"
                      << "8 - bse::vector demo\n"
                      << "9 - bse::array demo\n"
                      << "0 - bse::unique_ptr demo\n"
                      << "! - bse::string demo\n"
                      << endl;
    Util::System::out.unlock();
}

void MainMenu::run() {
    print_demo_menu();

    char input = '\0';
    unsigned int running_demo = 0;
    while (running) {
        input = listener.waitForKeyEvent();

        if ((input >= '0' && input <= '9') || input == '!') {
            switch (input) {
                case '1':
                    running_demo = Kernel::scheduler.ready<TextDemo>();
                    break;
                case '2':
                    running_demo = Kernel::scheduler.ready<PCSPKdemo>(&Device::PCSPK::aerodynamic);
                    break;
                case '3':
                    running_demo = Kernel::scheduler.ready<KeyboardDemo>();
                    break;
                case '4':
                    running_demo = Kernel::scheduler.ready<HeapDemo>();
                    break;
                case '5':
                    running_demo = Kernel::scheduler.ready<VBEdemo>();
                    break;
                case '6':
                    running_demo = Kernel::scheduler.ready<PagingDemo>();
                    break;
                case '7':
                    running_demo = Kernel::scheduler.ready<PreemptiveThreadDemo>(3);
                    break;

                case '8':
                    running_demo = Kernel::scheduler.ready<VectorDemo>();
                    break;
                case '9':
                    running_demo = Kernel::scheduler.ready<ArrayDemo>();
                    break;
                case '0':
                    running_demo = Kernel::scheduler.ready<SmartPointerDemo>();
                    break;
                case '!':
                    running_demo = Kernel::scheduler.ready<StringDemo>();
                    break;
            }
        } else if (input == 'k') {
            Kernel::scheduler.nice_kill(running_demo);  // NOTE: If thread exits itself this will throw error
            print_demo_menu();
        } else if (input == 'K') {
            Kernel::scheduler.kill(running_demo);
            print_demo_menu();
        }
    }

    Kernel::scheduler.exit();
    // This thread won't be deleted...
}
