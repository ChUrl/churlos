/*****************************************************************************
 *                                                                           *
 *                        B U M P A L L O C A T O R                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Eine sehr einfache Heap-Verwaltung, welche freigegebenen *
 *                  Speicher nicht mehr nutzen kann.                         *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 3.3.2022                        *
 *****************************************************************************/

#include "BumpAllocator.h"
#include "kernel/system/Globals.h"

/*****************************************************************************
 * Methode:         BumpAllocator::init                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    BumpAllokartor intitialisieren.                          *
 *****************************************************************************/
void BumpAllocator::init() {

    /* Hier muess Code eingefuegt werden */

    allocations = 0;
    next = reinterpret_cast<uint8_t*>(heap_start);

    log.info() << "Initialized Bump Allocator" << endl;
}

/*****************************************************************************
 * Methode:         BumpAllocator::dump_free_memory                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherinfos. Zu Debuggingzwecken.      *
 *****************************************************************************/
void BumpAllocator::dump_free_memory() {

    /* Hier muess Code eingefuegt werden */

    kout << "Freier Speicher:" << endl
         << " - Next: " << hex << reinterpret_cast<uint32_t>(next)
         << ", Allocations: " << dec << allocations << endl;
}

/*****************************************************************************
 * Methode:         BumpAllocator::alloc                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void* BumpAllocator::alloc(uint32_t req_size) {

    /* Hier muess Code eingefuegt werden */

    log.debug() << "Requested " << hex << req_size << " Bytes" << endl;

    if (req_size + reinterpret_cast<uint32_t>(next) > heap_end) {
        log.error() << " - More memory requested than available :(" << endl;
        return nullptr;
    }

    void* allocated = next;
    next = reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(next) + req_size);
    allocations = allocations + 1;

    log.trace() << " - Allocated " << hex << req_size << " Bytes." << endl;

    return allocated;
}

/*****************************************************************************
 * Methode:         BumpAllocator::free                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Nicht implementiert.                                     *
 *****************************************************************************/
void BumpAllocator::free(void* ptr) {
    log.error() << "   mm_free: ptr= " << hex << reinterpret_cast<uint32_t>(ptr) << ", not supported" << endl;
}
