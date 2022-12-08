/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/

#include "Globals.h"

namespace Kernel {

const Device::BIOS &bios = Device::BIOS::instance();
Device::VESA vesa;

Device::PIT pit(10000); // 10000
Device::PCSPK pcspk; // PC-Lautsprecher
Device::Keyboard kb; // Tastatur

// BumpAllocator allocator;
LinkedListAllocator allocator;
// TreeAllocator allocator;

Scheduler scheduler;

KeyEventManager kevman;
Device::SerialOut serial;

unsigned int total_mem; // RAM total
uint64_t systime = 0;

}
