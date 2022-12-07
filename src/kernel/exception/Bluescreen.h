/*****************************************************************************
 *                                                                           *
 *                          B L U E S C R E E N                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ein Bluescreen, falls eine x86 Exception auftritt. Evt.  *
 *                  ist der Stack und oder Heap kaputt, weswegen hier nicht  *
 *                  Kernel::kout etc. verwendet wird.                                *
 *                                                                           *
 * Autor:           Michael Schoettner, 2.2.2017                             *
 *****************************************************************************/

#ifndef Bluescreen_include__
#define Bluescreen_include__

#include <cstdint>

// dump blue screen (will not return)
void bs_dump(uint8_t exceptionNr);


#endif