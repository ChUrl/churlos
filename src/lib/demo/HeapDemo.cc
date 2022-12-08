/*****************************************************************************
 *                                                                           *
 *                            H E A P D E M O                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demonstration der dynamischen Speicherverwaltung.        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 27.12.2016                      *
 *****************************************************************************/

#include "HeapDemo.h"
#include "lib/util/System.h"

void HeapDemo::run() {
    Util::System::out.lock();
    Util::System::out.clear();
    Util::System::out << "HEAP_DEMO ===================================================================" << endl;

    /* hier muss Code eingefuegt werden */

    Kernel::allocator.dump_free_memory();

    // Rounding to word border
    Util::System::out << "ROUNDING ====================================================================" << endl;
    void *alloc = Kernel::allocator.alloc(1);  // 1 Byte
    Kernel::allocator.dump_free_memory();
    Kernel::allocator.free(alloc);
    Kernel::allocator.dump_free_memory();

    // Some objects and forward/backward merging
    Util::System::out << "SOME OBJECTS ================================================================" << endl;
    MyObj *a = new MyObj(5);
    Kernel::allocator.dump_free_memory();
    MyObj *b = new MyObj(10);
    Kernel::allocator.dump_free_memory();
    MyObj *c = new MyObj(15);
    Kernel::allocator.dump_free_memory();
    delete b;  // No merge
    Kernel::allocator.dump_free_memory();
    delete a;  // Merge forward BUG: Bluescreen
    Kernel::allocator.dump_free_memory();
    delete c;
    Kernel::allocator.dump_free_memory();

    // Allocate too whole heap
    // void* ptr = allocator.alloc(1024 * 1024 - 24);
    // allocator.dump_free_memory();
    // allocator.free(ptr);
    // allocator.dump_free_memory();

    // Allocate too much
    Util::System::out << "TOO MUCH ====================================================================" << endl;
    Kernel::allocator.alloc(1024 * 1024);  // should fail as only 1024 * 1024 - Headersize bytes are available
    Kernel::allocator.dump_free_memory();

    // A lot of allocations
    // MyObj* objs[1024];
    // for (unsigned int i = 0; i < 1024; ++i) {
    //     objs[i] = new MyObj(5);
    // }
    // allocator.dump_free_memory();
    // waitForReturn();
    // for (unsigned int i = 0; i < 1024; ++i) {
    //     delete objs[i];
    // }
    // allocator.dump_free_memory();

    // Array allocation
    Util::System::out << "ARRAY =======================================================================" << endl;
    MyObj *objs = new MyObj[1024];
    Kernel::allocator.dump_free_memory();
    delete[] objs;
    Kernel::allocator.dump_free_memory();

    Util::System::out << "HEAP_DEMO END ===============================================================" << endl;

    Util::System::out.unlock();
    Kernel::scheduler.exit();
}
