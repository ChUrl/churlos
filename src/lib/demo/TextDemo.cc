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

void TextDemo::run() {

    /* Hier muess Code eingefuegt werden */

    Kernel::kout.lock();
    Kernel::kout.clear();
    Kernel::kout << "TextDemo\n"
         << endl;

    Kernel::kout << "Attribut (GREEN on WHITE): "
         << bgc(Device::CGA::WHITE) << green << "GREEN on WHITE" << endl
         << "Attribut (WHITE on BLACK): "
         << bgc(Device::CGA::BLACK) << white << "WHITE on BLACK" << endl;
    Kernel::kout << endl;

    Kernel::kout << "Test der Zahlenausgabefunktion:" << endl
         << "|  dec  |  hex  |  bin  |" << endl
         << "+-------+-------+-------+" << endl;

    for (uint16_t num = 0; num < 17; ++num) {
        Kernel::kout << fillw(0) << "| " << fillw(6) << dec << num
             << fillw(0) << "| " << fillw(6) << hex << num
             << fillw(0) << "| " << fillw(6) << bin << num
             << fillw(0) << "|" << endl;
    }

    Kernel::kout << endl;

    Kernel::kout.unlock();
    Kernel::scheduler.exit();
}
