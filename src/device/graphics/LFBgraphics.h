/*****************************************************************************
 *                                                                           *
 *                            L F B G R A P H I C S                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zeichenfunktionen fuer Grafikmodi, die auf einem         *
 *                  linearen Framebuffer basieren. Verwendet in VESA und     *
 *                  QemuVGA.                                                 *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 19.9.2016                       *
 *                  Der Code fuer das Zeichnen der Linie ist von Alan Wolfe  *
 *         https://blog.demofox.org/2015/01/17/bresenhams-drawing-algorithms *
 *****************************************************************************/

#ifndef LFBgraphics_include__
#define LFBgraphics_include__

#include "Fonts.h"

// Hilfsfunktionen um Farbwerte fuer einen Pixel zu erzeugen
constexpr uint32_t RGB_24(uint8_t r, uint8_t g, uint8_t b) {
    return ((r << 16) + (g << 8) + b);
}

constexpr const bool BUFFER_INVISIBLE = false;
constexpr const bool BUFFER_VISIBLE  = true;

class LFBgraphics {
private:
    // Hilfsfunktion fuer drawString
    void drawMonoBitmap(uint32_t x, uint32_t y,
                        uint32_t width, uint32_t height,
                        const uint8_t* bitmap, uint32_t col) const;

public:
    LFBgraphics(const LFBgraphics& copy) = delete;  // Verhindere Kopieren

    LFBgraphics() : mode(BUFFER_VISIBLE) {};

    uint32_t xres, yres;  // Aufloesung in Pixel
    uint8_t bpp;         // Farbtiefe (Bits per Pixel)
    uint32_t lfb;         // Adresse des Linearen Framebuffers
    uint32_t hfb;         // Adresse des versteckten Buffers (optional, fuer Animationen)
    uint8_t mode;        // Zeichnen im sichtbaren = 1 oder unsichtbaren = 0 Puffer

    void clear() const;
    void drawPixel(uint32_t x, uint32_t y, uint32_t col) const;

    void drawString(const Font& fnt, uint32_t x, uint32_t y, uint32_t col, const char* str, uint32_t len) const;

    void drawCircle(uint32_t x, uint32_t y, uint32_t rad, uint32_t col) const;
    void drawStraightLine(uint32_t x1, uint32_t y1, uint32_t x2, unsigned int y2, unsigned int col) const;
    void drawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int col) const;

    void drawSprite(unsigned int width, unsigned int height, unsigned int bytes_pp, const uint8_t* pixel_data) const;

    // stellt ein, ob in den sichtbaren Puffer gezeichnet wird
    void setDrawingBuff(int v);

    // kopiert 'hfb' nach 'lfb'
    void copyHiddenToVisible() const;
};

#endif
