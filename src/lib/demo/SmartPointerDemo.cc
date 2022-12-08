#include "SmartPointerDemo.h"
#include "kernel/process/IdleThread.h"
#include "lib/util/System.h"

NamedLogger SmartPointerDemo::log = NamedLogger("SmartPointerDemo");

void SmartPointerDemo::run() {
    Util::System::out.lock();
    Util::System::out.clear();

    Util::System::out << "Output is written to log to be able to trace memory allocations/deallocations" << endl;

    {
        log.info() << "Allocating new unique_ptr<int>..." << endl;
        Memory::unique_ptr<int> ptr = Memory::make_unique<int>(1);
        log.info() << "Leaving scope..." << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    {
        log.info() << "Allocating new unique_ptr<int>..." << endl;
        Memory::unique_ptr<int> ptr1 = Memory::make_unique<int>(1);
        Memory::unique_ptr<int> ptr2;

        log.info() << "*ptr1 == " << *ptr1 << ", (bool)ptr2 == " << static_cast<bool>(ptr2) << endl;
        log.info() << "Moving ptr1 => ptr2 (no allocations should happen)..." << endl;
        ptr2 = std::move(ptr1);
        log.info() << "(bool)ptr1 == " << static_cast<bool>(ptr1) << ", *ptr2 == " << *ptr2 << endl;

        log.info() << "Leaving scope..." << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    {
        log.info() << "Allocating (2) new unique_ptr<int>..." << endl;
        Memory::unique_ptr<int> ptr1 = Memory::make_unique<int>(1);
        Memory::unique_ptr<int> ptr2 = Memory::make_unique<int>(1);

        log.info() << "Moving ptr1 => ptr2 (ptr1 should be freed)..." << endl;
        ptr2 = std::move(ptr1);

        log.info() << "Leaving scope..." << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    // =====================================================================

    {
        log.info() << "Allocating new unique_ptr<int[]>..." << endl;
        Memory::unique_ptr<int[]> ptr = Memory::make_unique<int[]>(10);
        ptr[0] = 1;
        log.info() << "ptr[0] == " << ptr[0] << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    {
        log.info() << "Allocating new unique_ptr<int[10]>..." << endl;
        Memory::unique_ptr<int[]> ptr1 = Memory::make_unique<int[]>(10);
        Memory::unique_ptr<int[]> ptr2;

        log.info() << "Moving ptr1 => ptr2 (no allocations should happen)..." << endl;
        ptr2 = std::move(ptr1);

        log.info() << "Leaving scope..." << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    {
        log.info() << "Allocating (2) new unique_ptr<int[10]>..." << endl;
        Memory::unique_ptr<int> ptr1 = Memory::make_unique<int>(10);
        Memory::unique_ptr<int> ptr2 = Memory::make_unique<int>(10);

        log.info() << "Moving ptr1 => ptr2 (ptr1 should be freed)..." << endl;
        ptr2 = std::move(ptr1);

        log.info() << "Leaving scope..." << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    // NOTE: This wasn't working because of a missing operator[] delete in the allocator
    log.info() << "Allocating unique_ptr<int>*..." << endl;
    Memory::unique_ptr<int> *ptrptr = new Memory::unique_ptr<int>[10];
    delete[] ptrptr;
    log.info() << "Should be deleted by now..." << endl;

    // =====================================================================

    {
        log.info() << "Stackallocating Array<bse::unique_ptr<int>, 10>..." << endl;
        Container::Array<Memory::unique_ptr<int>, 10> arr;
        log.info() << "Populating slot 0..." << endl;
        arr[0] = Memory::make_unique<int>(1);
        log.info() << "Moving slot 0 to slot 1..." << endl;
        arr[1] = std::move(arr[0]);
        log.info() << "Leaving scope" << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    {
        log.info() << "Heapallocating Array<bse::unique_ptr<int>, 10>..." << endl;
        Container::Array<Memory::unique_ptr<int>, 10> *arr = new Container::Array<Memory::unique_ptr<int>, 10>;
        log.info() << "Populating slot 0..." << endl;
        (*arr)[0] = Memory::make_unique<int>(1);
        log.info() << "Moving slot 0 to slot 1..." << endl;
        (*arr)[1] = std::move((*arr)[0]);
        log.info() << "Deleting" << endl;
        delete arr;
        log.info() << "Leaving scope" << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    {
        log.info() << "ArrayList<bse::unique_ptr<int>>..." << endl;
        Container::Vector<Memory::unique_ptr<int>> vec;
        log.info() << "2x insertion" << endl;
        vec.push_back(Memory::make_unique<int>(1));
        vec.push_back(Memory::make_unique<int>(2));

        log.info() << "Leaving scope" << endl;
    }
    log.info() << "Should be deleted by now..." << endl;

    Util::System::out.unlock();
    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    schedulerService.exit();
}
