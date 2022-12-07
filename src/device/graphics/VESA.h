/*****************************************************************************
 *                                                                           *
 *                                 V E S A                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    VESA-Treiber ueber 16-Bit BIOS.                          *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 19.5.2022                       *
 *****************************************************************************/

#ifndef VESA_include__
#define VESA_include__

#include "LFBgraphics.h"
#include "lib/stream/Logger.h"

namespace Device {

// Ausgewaehlte Grafikmodi mit Mode-Nummer
constexpr const uint16_t MODE_640_480_16BITS = 0x111;
constexpr const uint16_t MODE_640_480_24BITS = 0x112;
constexpr const uint16_t MODE_800_600_16BITS = 0x114;
constexpr const uint16_t MODE_800_600_24BITS = 0x115;
constexpr const uint16_t MODE_1024_768_16BITS = 0x117;
constexpr const uint16_t MODE_1024_768_24BITS = 0x118;

class VESA : public LFBgraphics {
private:
    int mode_nr;  // Nummer des Modus
    NamedLogger log;

public:
    VESA(const VESA &copy) = delete;  // Verhindere Kopieren

    VESA() : log("VESA") {}

    // Can't make singleton because atexit

    // Bestimmten Grafikmodus einschalten
    bool initGraphicMode(uint16_t mode);

    static void initTextMode();
};

}

#endif
