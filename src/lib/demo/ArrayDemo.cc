#include "ArrayDemo.h"

void ArrayDemo::run() {
    Container::Array<int, 10> arr1 {};
    Container::Array<int, 10> arr2 {};

    Kernel::kout.lock();
    Kernel::kout.clear();

    Kernel::kout << "Adding..." << endl;
    for (int i = 0; i < 10; ++i) {
        arr1[i] = i;
    }

    Kernel::kout << "Iterator printing arr1:" << endl;
    for (int i : arr1) {
        Kernel::kout << i << " ";
    }
    Kernel::kout << endl;

    Kernel::kout << "Swapping arr1 and arr2..." << endl;
    arr1.swap(arr2);

    Kernel::kout << "Iterator printing arr1:" << endl;
    for (int i : arr1) {
        Kernel::kout << i << " ";
    }
    Kernel::kout << endl;

    Kernel::kout << "Iterator printing arr2:" << endl;
    for (int i : arr2) {
        Kernel::kout << i << " ";
    }
    Kernel::kout << endl;

    // arr1.swap(arr3);  // Not possible as type/size has to match

    Kernel::kout.unlock();
    Kernel::scheduler.exit();
}
