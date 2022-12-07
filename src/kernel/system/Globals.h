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

#include "device/graphics/CGA_Stream.h"
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

// I wanted to make more of these singletons but there were problems with atexit missing because of nostdlib I guess

extern CGA_Stream kout;  // Ausgabe-Strom fuer Kernel
extern const BIOS& bios;        // Schnittstelle zum 16-Bit BIOS
extern VESA vesa;        // VESA-Treiber

extern PIC pic;               // Interrupt-Controller
extern IntDispatcher intdis;  // Unterbrechungsverteilung
extern PIT pit;               // Zeitgeber
extern PCSPK pcspk;           // PC-Lautsprecher
extern Keyboard kb;           // Tastatur

// extern BumpAllocator allocator;
extern LinkedListAllocator allocator;
// extern TreeAllocator allocator;

extern Scheduler scheduler;

extern KeyEventManager kevman;
extern SerialOut serial;

extern unsigned int total_mem;  // RAM total
extern unsigned long systime;   // wird all 10ms hochgezaehlt

#endif
