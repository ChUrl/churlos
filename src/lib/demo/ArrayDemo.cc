#include "ArrayDemo.h"
#include "lib/util/System.h"

void ArrayDemo::run() {
    Container::Array<int, 10> arr1{};
    Container::Array<int, 10> arr2{};

    Util::System::out.lock();
    Util::System::out.clear();

    Util::System::out << "Adding..." << endl;
    for (int i = 0; i < 10; ++i) {
        arr1[i] = i;
    }

    Util::System::out << "Iterator printing arr1:" << endl;
    for (int i: arr1) {
        Util::System::out << i << " ";
    }
    Util::System::out << endl;

    Util::System::out << "Swapping arr1 and arr2..." << endl;
    arr1.swap(arr2);

    Util::System::out << "Iterator printing arr1:" << endl;
    for (int i: arr1) {
        Util::System::out << i << " ";
    }
    Util::System::out << endl;

    Util::System::out << "Iterator printing arr2:" << endl;
    for (int i: arr2) {
        Util::System::out << i << " ";
    }
    Util::System::out << endl;

    // arr1.swap(arr3);  // Not possible as type/size has to match

    Util::System::out.unlock();
    Kernel::scheduler.exit();
}
