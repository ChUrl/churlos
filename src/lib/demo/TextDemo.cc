/*****************************************************************************
 *                                                                           *
 *                           T E X T D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                       *
 *****************************************************************************/

#include "TextDemo.h"
#include "lib/util/System.h"

void TextDemo::run() {

    /* Hier muess Code eingefuegt werden */

    Util::System::out.lock();
    Util::System::out.clear();
    Util::System::out << "TextDemo\n"
                      << endl;

    Util::System::out << "Attribut (GREEN on WHITE): "
                      << bgc(Device::CGA::WHITE) << green << "GREEN on WHITE" << endl
                      << "Attribut (WHITE on BLACK): "
                      << bgc(Device::CGA::BLACK) << white << "WHITE on BLACK" << endl;
    Util::System::out << endl;

    Util::System::out << "Test der Zahlenausgabefunktion:" << endl
                      << "|  dec  |  hex  |  bin  |" << endl
                      << "+-------+-------+-------+" << endl;

    for (uint16_t num = 0; num < 17; ++num) {
        Util::System::out << fillw(0) << "| " << fillw(6) << dec << num
                          << fillw(0) << "| " << fillw(6) << hex << num
                          << fillw(0) << "| " << fillw(6) << bin << num
                          << fillw(0) << "|" << endl;
    }

    Util::System::out << endl;

    Util::System::out.unlock();
    Kernel::scheduler.exit();
}
