/*****************************************************************************
 *                                                                           *
 *                     C G A _ S T R E A M                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Die Klasse CGA_Stream ermoeglicht die Ausgabe verschied. *
 *                  Datentypen als Zeichenketten auf dem CGA-Bildschirm eines*
 *                  PCs. Fuer weitergehende Formatierung oder spezielle      *
 *                  Effekte stehen die Methoden der Klasse CGA zur           *
 *                  Verfuegung.                                              *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 06.04.20        *
 *****************************************************************************/
#ifndef CGA_Stream_include_H_
#define CGA_Stream_include_H_

#include "device/graphics/CGA.h"
#include "lib/stream/OutStream.h"
#include "lib/async/Semaphore.h"

// Allow for easier stream-like color changing
class fgc {
public:
    constexpr explicit fgc(const Device::CGA::color fg) : fg(fg) {}

    const Device::CGA::color fg;
};

class bgc {
public:
    constexpr explicit bgc(const Device::CGA::color bg) : bg(bg) {}

    const Device::CGA::color bg;
};

constexpr const fgc white = fgc(Device::CGA::WHITE);
constexpr const fgc black = fgc(Device::CGA::BLACK);
constexpr const fgc green = fgc(Device::CGA::GREEN);
constexpr const fgc red = fgc(Device::CGA::RED);
constexpr const fgc lgrey = fgc(Device::CGA::LIGHT_GREY);

class CGA_Stream : public OutStream, public Device::CGA {
private:
    // Allow for synchronization of output text, needed when running something in parallel to
    // the PreemptiveThreadDemo for example
    // NOTE: Should only be used by threads (like the demos) to not lock the system
    Async::Semaphore sem;

    CGA::color color_fg;
    CGA::color color_bg;
    bool blink;

public:
    CGA_Stream(CGA_Stream &copy) = delete;  // Verhindere Kopieren

    CGA_Stream() : sem(1), color_fg(CGA::LIGHT_GREY), color_bg(CGA::BLACK), blink(false) {
        pos = 0;
    }

    // Can't make singleton because atexit

    // ~CGA_Stream() override = default;

    void lock() { sem.acquire(); }

    void unlock() { sem.release(); }

    // Methode zur Ausgabe des Pufferinhalts der Basisklasse StringBuffer.
    void flush() override;

    // Change stream color
    template<typename T>
    friend T &operator<<(T &os, const fgc &fg) {
        CGA::color old_bg = os.color_bg;
        os.flush();
        os.color_bg = old_bg;
        os.color_fg = fg.fg;
        return os;
    }

    template<typename T>
    friend T &operator<<(T &os, const bgc &bg) {
        CGA::color old_fg = os.color_fg;
        os.flush();
        os.color_fg = old_fg;
        os.color_bg = bg.bg;
        return os;
    }
};

#endif
