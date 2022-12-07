/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef Globals_include__
#define Globals_include__

#include "lib/stream/CGA_Stream.h"
#include "device/hid/Keyboard.h"
#include "device/sound/PCSPK.h"
#include "device/time/PIT.h"
#include "device/graphics/VESA.h"
#include "kernel/memory/BumpAllocator.h"
#include "kernel/memory/LinkedListAllocator.h"
#include "kernel/memory/TreeAllocator.h"
#include "device/bios/BIOS.h"
#include "device/cpu/CPU.h"
#include "kernel/interrupt/IntDispatcher.h"
#include "device/interrupt/PIC.h"
#include "kernel/memory/Paging.h"
#include "kernel/process/Scheduler.h"
#include "device/port/SerialOut.h"
#include "kernel/event/KeyEventManager.h"

namespace Kernel {

// I wanted to make more of these singletons but there were problems with atexit missing because of nostdlib I guess

extern CGA_Stream kout;  // Ausgabe-Strom fuer Kernel
extern const Device::BIOS &bios;        // Schnittstelle zum 16-Bit BIOS
extern Device::VESA vesa;        // VESA-Treiber

extern Device::PIC pic;               // Interrupt-Controller
extern IntDispatcher intdis;  // Unterbrechungsverteilung
extern Device::PIT pit;               // Zeitgeber
extern Device::PCSPK pcspk;           // PC-Lautsprecher
extern Device::Keyboard kb;           // Tastatur

// extern BumpAllocator allocator;
extern LinkedListAllocator allocator;
// extern TreeAllocator allocator;

extern Scheduler scheduler;

extern KeyEventManager kevman;
extern Device::SerialOut serial;

extern uint32_t total_mem;  // RAM total
extern uint64_t systime;   // wird all 10ms hochgezaehlt

}

#endif
