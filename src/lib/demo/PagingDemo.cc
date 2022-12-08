#include "PagingDemo.h"
#include "lib/util/System.h"

void PagingDemo::writeprotect_page() {
    Util::System::out << "Accessing a writeprotected page triggers bluescreen,\nif you can read this it didn't work"
                      << endl;

    // BlueScreen 1
    // asm("int $3");

    // BlueScreen 2
    log.info() << "Allocating page" << endl;
    uint32_t *page = Kernel::pg_alloc_page();
    *page = 42;
    log.info() << "Writeprotecting page..." << endl;
    Kernel::pg_write_protect_page(page);

    log.info() << "Accessing writeprotected page" << endl;
    *page = 42; // We map logical to physical 1:1 so no need to do any lookup

    // No free because bluescreen
}

void PagingDemo::notpresent_page() {
    Util::System::out << "Produces pagefault, if you can read this it didn't work" << endl;

    log.info() << "Allocating page" << endl;
    uint32_t *page = Kernel::pg_alloc_page();
    *page = 42;

    log.info() << "Marking page notpresent..." << endl;
    Kernel::pg_notpresent_page(page);

    log.info() << "Accessing page" << endl;
    Util::System::out << "Page not accessible: " << *page << endl;

    // No free because bluescreen
}

void PagingDemo::run() {
    Util::System::out << "Press w for writeprotect demo, n for notpresent demo" << endl;
    switch (listener.waitForKeyEvent()) {
        case 'w':
            writeprotect_page();
            break;
        case 'n':
            notpresent_page();
            break;
    }

    Kernel::scheduler.exit();
}
