/*****************************************************************************
 *                                                                           *
 *                                B I O S                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zugriff auf das 16-Bit BIOS. Fuer VESA-Funktionen.       *
 *                                                                           *
 * Autor:           Michael Schoettner, 13.9.2016                            *
 *****************************************************************************/
#ifndef BIOS_include__
#define BIOS_include__

#include <cstdint>

namespace Device {

// Speicherseite fuer Rueckgabewerte von BIOS-Aufrufen
constexpr const unsigned int RETURN_MEM = 0x9F000;

// Struktur fuer Parameteruebergabe fuer einen BIOS-Aufruf
struct BIOScall_params {
    uint16_t DS;
    uint16_t ES;
    uint16_t FS;
    uint16_t Flags;
    uint32_t DI;
    uint32_t SI;
    uint32_t BP;
    uint32_t SP;
    uint32_t BX;
    uint32_t DX;
    uint32_t CX;
    uint32_t AX;
} __attribute__((packed));
// kein Auffuellen von bytes auf Wortgrenzen

// Zeiger auf Speichbereich fuer Parameter fuer BIOS-Aufruf
extern  BIOScall_params* BC_params;

class BIOS {
private:
    // Initialisierung: manuelles Anlegen einer Funktion
    BIOS();

public:
    BIOS(const BIOS& copy) = delete;  // Verhindere Kopieren

    static BIOS& instance() {
        static BIOS bios;
        return bios;
    }

    // BIOS-Aufruf, per Software-Interrupt
    static void Int(uint8_t inter);
};

}

#endif
