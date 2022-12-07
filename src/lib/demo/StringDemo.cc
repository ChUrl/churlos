#include "StringDemo.h"

void StringDemo::run() {
    Kernel::kout.lock();
    Kernel::kout.clear();

    log.info() << "Allocating new string" << endl;
    String::string str1 = "This is a dynamically allocated string!";
    Kernel::kout << str1 << endl;

    log.info() << "Reassign string" << endl;
    str1 = "Hello";
    Kernel::kout << str1 << " has length " << dec << str1.size() << endl;
    Kernel::kout << "Again with strlen: Hello has length " << dec << String::strlen("Hello") << endl;

    Kernel::kout << "Adding strings: " << str1 << " + World" << endl;
    log.info() << "Adding strings" << endl;
    str1 = str1 + " World";
    Kernel::kout << str1 << endl;

    Kernel::kout << "Hello += World" << endl;
    log.info() << "Hello += World" << endl;
    String::string str3 = "Hello";
    str3 += " World";
    Kernel::kout << str3 << endl;

    Kernel::kout << "Hello World *= 3" << endl;
    str3 *= 3;
    Kernel::kout << str3 << endl;

    Kernel::kout << "String iterator!" << endl;
    for (const char c : str1) {
        Kernel::kout << c << " ";
    }
    Kernel::kout << endl;

    log.info() << "Allocating new string" << endl;
    String::string str2 = "Hello World";
    Kernel::kout << "str1 == str2: " << static_cast<int>(str1 == str2) << endl;
    Kernel::kout << "strcmp(Hello, Hello): " << String::strcmp("Hello", "Hello") << endl;

    log.info() << "Reassign str2" << endl;
    str2 = "Hello";

    Container::array<char, 5> arr{};
    arr[0] = 'H';
    arr[1] = 'e';
    arr[2] = 'l';
    arr[3] = 'l';
    arr[4] = 'o';
    Kernel::kout << "bse::array<char, 5> to bse::string: " << static_cast<String::string>(arr) << ", size: " << (String::string(arr)).size() << endl;
    Kernel::kout << "(bse::string)arr (" << static_cast<String::string>(arr) << ") == str2 (" << str2 << "): " << static_cast<int>(String::string(arr) == str2) << endl;

    Kernel::kout.unlock();
    Kernel::scheduler.exit();
}
