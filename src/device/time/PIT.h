/*****************************************************************************
 *                                                                           *
 *                                   P I T                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Programmable Interval Timer.                             * 
 *                                                                           *
 * Autor:           Michael Schoettner, 23.8.2016                            *
 *****************************************************************************/

#ifndef PIT_include__
#define PIT_include__

#include "kernel/interrupt/ISR.h"
#include "device/port/IOport.h"
#include "lib/util/Array.h"
#include <cstdint>

class PIT : public ISR {
private:
    const static IOport control;
    const static IOport data0;

    enum { time_base = 838 }; /* ns */
    uint32_t timer_interval;

    const bse::array<char, 4> indicator{'|', '/', '-', '\\'};
    uint8_t indicator_pos = 0;
    uint64_t last_indicator_refresh = 0;

public:
    PIT(const PIT& copy) = delete;  // Verhindere Kopieren

//    ~PIT() override = default;

    // Zeitgeber initialisieren.
    explicit PIT(uint32_t us) {
        PIT::interval(us);
    }

    // Konfiguriertes Zeitintervall auslesen.
    uint32_t interval() const { return timer_interval; }

    // Zeitintervall in Mikrosekunden, nachdem periodisch ein Interrupt
    //erzeugt werden soll.
    static void interval(uint32_t us);

    // Aktivierung der Unterbrechungen fuer den Zeitgeber
    void plugin();

    // Unterbrechnungsroutine des Zeitgebers.
    void trigger() override;
};

#endif
