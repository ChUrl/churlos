#include "StringDemo.h"
#include "lib/util/System.h"
#include "kernel/system/System.h"
#include "kernel/service/SchedulerService.h"

NamedLogger StringDemo::log = NamedLogger("StringDemo");

void StringDemo::run() {
    Util::System::out.lock();
    Util::System::out.clear();

    log.info() << "Allocating new string" << endl;
    String::string str1 = "This is a dynamically allocated string!";
    Util::System::out << str1 << endl;

    log.info() << "Reassign string" << endl;
    str1 = "Hello";
    Util::System::out << str1 << " has length " << dec << str1.size() << endl;
    Util::System::out << "Again with strlen: Hello has length " << dec << String::strlen("Hello") << endl;

    Util::System::out << "Adding strings: " << str1 << " + World" << endl;
    log.info() << "Adding strings" << endl;
    str1 = str1 + " World";
    Util::System::out << str1 << endl;

    Util::System::out << "Hello += World" << endl;
    log.info() << "Hello += World" << endl;
    String::string str3 = "Hello";
    str3 += " World";
    Util::System::out << str3 << endl;

    Util::System::out << "Hello World *= 3" << endl;
    str3 *= 3;
    Util::System::out << str3 << endl;

    Util::System::out << "String iterator!" << endl;
    for (const char c: str1) {
        Util::System::out << c << " ";
    }
    Util::System::out << endl;

    log.info() << "Allocating new string" << endl;
    String::string str2 = "Hello World";
    Util::System::out << "str1 == str2: " << static_cast<int>(str1 == str2) << endl;
    Util::System::out << "strcmp(Hello, Hello): " << String::strcmp("Hello", "Hello") << endl;

    log.info() << "Reassign str2" << endl;
    str2 = "Hello";

    Container::Array<char, 5> arr{};
    arr[0] = 'H';
    arr[1] = 'e';
    arr[2] = 'l';
    arr[3] = 'l';
    arr[4] = 'o';
    Util::System::out << "bse::array<char, 5> to bse::string: " << static_cast<String::string>(arr) << ", size: "
                      << (String::string(arr)).size() << endl;
    Util::System::out << "(bse::string)arr (" << static_cast<String::string>(arr) << ") == str2 (" << str2 << "): "
                      << static_cast<int>(String::string(arr) == str2) << endl;

    Util::System::out.unlock();
    auto &schedulerService = Kernel::System::getService<Kernel::SchedulerService>();
    schedulerService.exit();
}
