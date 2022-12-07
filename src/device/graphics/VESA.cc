/*****************************************************************************
 *                                                                           *
 *                                 V E S A                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    VESA-Treiber ueber 16-Bit BIOS.                          *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 18.3.2017                       *
 *****************************************************************************/

#include "VESA.h"
#include "device/bios/BIOS.h"

// Informationen ueber einen VESA-Grafikmodus
// (siehe http://wiki.osdev.org/VESA_Video_Modes)
struct VbeModeInfoBlock {
    uint16_t attributes;
    uint8_t winA, winB;
    uint16_t granularity;
    uint16_t winsize;
    uint16_t segmentA, segmentB;
    uint16_t realFctPtr[2];
    uint16_t pitch;  // Bytes pro Scanline

    uint16_t Xres, Yres;
    uint8_t Wchar, Ychar, planes, bpp, banks;
    uint8_t memory_model, bank_size, image_pages;
    uint8_t reserved0;

    uint8_t red_mask, red_position;
    uint8_t green_mask, green_position;
    uint8_t blue_mask, blue_position;
    uint8_t rsv_mask, rsv_position;
    uint8_t directcolor_attributes;

    uint32_t physbase;  // Adresse des Linear-Framebuffers
    uint32_t OffScreenMemOffset;
    uint32_t OffScreenMemSize;
} __attribute__((packed));

// Informationen ueber die Grafikkarte
// (siehe http://wiki.osdev.org/VESA_Video_Modes)
struct VbeInfoBlock {
    char VbeSignature[4];            // == "VESA"
    uint16_t VbeVersion;       // == 0x0300 for VBE 3.0
    uint16_t OemStringPtr[2];  // isa vbeFarPtr
    uint8_t Capabilities[4];
    uint16_t VideoModePtr[2];  // isa vbeFarPtr
    uint16_t TotalMemory;      // as # of 64KB blocks
} __attribute__((packed));

/*****************************************************************************
 * Methode:         VESA::initTextMode                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Schalter in den Text-Modus 80x25 Zeichen.                *
 *****************************************************************************/
void VESA::initTextMode() {
    BC_params->AX = 0x4f02;      // SVFA BIOS, init mode
    BC_params->BX = 0x4003;      // 80x25
    BIOS::Int(0x10);
}

/*****************************************************************************
 * Methode:         VESA::initGraphicMode                                    *
 *---------------------------------------------------------------------------*
 * Parameter:       Nummer des Grafikmodus (siehe VESA.h)                    *
 *                                                                           *
 * Beschreibung:    Bestimmten Grafikmodus einschalten. Dies wird durch      *
 *                  einen Aufruf des BIOS gemacht.                           *
 *****************************************************************************/
bool VESA::initGraphicMode(uint16_t mode) {

    // Alle Grafikmodi abfragen
    BC_params->AX = 0x4F00;
    BC_params->ES = RETURN_MEM >> 4;
    BC_params->DI = RETURN_MEM & 0xF;
    BIOS::Int(0x10);

    VbeInfoBlock* ib = reinterpret_cast<VbeInfoBlock*>(RETURN_MEM);

    // Signaturen pruefen
    if (BC_params->AX != 0x004F) {
        log.error() << "VESA wird nicht unterstuetzt." << endl;
        return false;
    }
    if (ib->VbeSignature[0] != 'V' || ib->VbeSignature[1] != 'E' ||
        ib->VbeSignature[2] != 'S' || ib->VbeSignature[3] != 'A') {
        log.error() << "VESA wird nicht unterstuetzt." << endl;
        return false;
    }

    //    kout << "TotalVideoMemory:  " << ((ib->TotalMemory*65536) / (1024*1024)) << " MB" << endl;

    // Gewuenschten Grafikmodus aus Antwort suchen
    auto* modePtr = reinterpret_cast<uint16_t*>((ib->VideoModePtr[1] << 4) + ib->VideoModePtr[0]);
    for (uint32_t i = 0; modePtr[i] != 0xFFFF; ++i) {
        // Gewuenschter Grafikmodus gefunden?
        if (modePtr[i] == mode) {
            VbeModeInfoBlock* minf = reinterpret_cast<VbeModeInfoBlock*>(RETURN_MEM);

            // Weitere Infos ueber diesen Grafikmodus abfragen
            BC_params->AX = 0x4F01;
            BC_params->CX = mode;
            BC_params->ES = RETURN_MEM >> 4;
            BC_params->DI = RETURN_MEM & 0xF;
            BIOS::Int(0x10);

            // Text-Modi 0-3 haben keinen LFB
            if (mode > 3 && (minf->attributes & 0x90) == 0) {
                log.error() << "Grafikmodus bietet keinen linearen Framebuffer." << endl;
                return false;
            }

            mode_nr = mode;
            xres = minf->Xres;
            yres = minf->Yres;
            bpp = static_cast<uint8_t>(minf->bpp);
            lfb = minf->physbase;

            hfb = reinterpret_cast<uint32_t>(new char[xres * yres * bpp / 8]);

            // Grafikmodus einschalten
            BC_params->AX = 0x4f02;  // SVFA BIOS, init mode
            BC_params->BX = mode;
            BIOS::Int(0x10);
            return true;
        }
    }
    log.error() << "Grafikmodus nicht gefunden." << endl;
    return false;
}
