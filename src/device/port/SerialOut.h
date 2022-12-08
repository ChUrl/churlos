#ifndef SerialOut_Include_H_
#define SerialOut_Include_H_

#include "IOport.h"
#include "lib/string/String.h"
#include "lib/string/StringView.h"
#include "lib/util/RestrictedConstructors.h"

// NOTE: I took this code from https://wiki.osdev.org/Serial_Ports

namespace Device {

class SerialOut {
public:
    SerialOut();

    MakeUncopyable(SerialOut)

    MakeUnmovable(SerialOut)

    // Can't make singleton because atexit

    static char read();

    static void write(char a);

    static void write(String::StringView a);

private:
    static const IOport com1;

    static int serial_received();

    static int is_transmit_empty();
};

}

#endif
