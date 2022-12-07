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

#include "LFBgraphics.h"

namespace Device {

/* Hilfsfunktionen */
void swap(uint32_t *a, uint32_t *b);

uint16_t abs(int32_t a);

/*****************************************************************************
 * Methode:         LFBgraphics::drawMonoBitmap                              *
 *---------------------------------------------------------------------------*
 * Parameter:       x,y     Startpunkt ab dem Text ausgegeben wird.          *
 *                  width   Breite in Pixel                                  *
 *                  height  Hoehe in Pixel                                   *
 *                  bitmap  Zeiger auf Pixel der monochromen Rastergrafik    *
 *                  col     Farbe der Pixel                                  *
 *                                                                           *
 * Beschreibung:    Gibt die gegebene monochrome Rastergrafik an der Position*
 *                  x,y zeilenweise aus. (x,y) ist der linke obere Punkt;    *
 *                  ist in der bitmap eine '1', so wird ein Pixel mit der    *
 *                  Farbe col ausgegeben, ansonsten bei '0' nichts.          *
 *                  Diese Funktion basiert auf dem Format der Fonts, welche  *
 *                  mit cpi2fnt (AmigaOS) erzeugt wurden. Das Format erklaert*
 *                  sich in den C-Dateien in fonts/ von selbst.              *
 *****************************************************************************/
inline void LFBgraphics::drawMonoBitmap(uint32_t x, uint32_t y,
                                        uint32_t width, uint32_t height,
                                        const uint8_t *bitmap, uint32_t color) const {
    // Breite in Bytes
    uint16_t width_byte = width / 8 + ((width % 8 != 0) ? 1 : 0);

    for (uint32_t yoff = 0; yoff < height; ++yoff) {
        uint32_t xpos = x;
        uint32_t ypos = y + yoff;
        for (uint32_t xb = 0; xb < width_byte; ++xb) {
            for (int32_t src = 7; src >= 0; --src) {
                if ((1 << src) & *bitmap) {
                    drawPixel(xpos, ypos, color);
                }
                xpos++;
            }
            bitmap++;
        }
    }
}

/*****************************************************************************
 * Methode:         LFBgraphics::drawString                                  *
 *---------------------------------------------------------------------------*
 * Parameter:       fnt     Schrift                                          *
 *                  x,y     Startpunkt ab dem Text ausgegeben wird.          *
 *                  col     Farbe des Textes                                 *
 *                  str     Zeiger auf Zeichenkette                          *
 *                  len     Laenge der Zeichenkette                          *
 *                                                                           *
 * Beschreibung:    Gibt eine Zeichenkette mit gewaehlter Schrift an der     *
 *                  Position x,y aus.                                        *
 *****************************************************************************/
void LFBgraphics::drawString(const Graphics::Font &fnt, uint32_t x, uint32_t y,
                             uint32_t col, const char *str, uint32_t len) const {
    for (uint32_t i = 0; i < len; ++i) {
        drawMonoBitmap(x, y, fnt.get_char_width(), fnt.get_char_height(), fnt.getChar(*(str + i)), col);
        x += fnt.get_char_width();
    }
}

/*****************************************************************************
 * Methode:         LFBgraphics::drawPixel                                   *
 *---------------------------------------------------------------------------*
 * Parameter:       x, y    Koordinaten des Pixels                           *
 *                  col     Farbe                                            *
 *                                                                           *
 * Beschreibung:    Zeichnen eines Pixels.                                   *
 *****************************************************************************/
void LFBgraphics::drawPixel(uint32_t x, uint32_t y, uint32_t col) const {
    auto *ptr = reinterpret_cast<uint8_t *>(lfb);

    if (hfb == 0 || lfb == 0) {
        return;
    }

    if (mode == BUFFER_INVISIBLE) {
        ptr = reinterpret_cast<uint8_t *>(hfb);
    }

    // Pixel ausserhalb des sichtbaren Bereichs?
    if (x < 0 || x >= xres || y < 0 || y > yres) {
        return;
    }

    // Adresse des Pixels berechnen und Inhalt schreiben
    switch (bpp) {
        case 8:
            ptr += (x + y * xres);
            *ptr = col;
            return;
        case 15:
        case 16:
            ptr += (2 * x + 2 * y * xres);
            *ptr = col;
            return;
        case 24:
            ptr += (3 * x + 3 * y * xres);
            *ptr = (col & 0xFF);
            ptr++;
            *ptr = ((col >> 8) & 0xFF);
            ptr++;
            *ptr = ((col >> 16) & 0xFF);
            ptr;
            return;
        case 32:
            ptr += (4 * x + 4 * y * xres);
            *ptr = (col & 0xFF);
            ptr++;
            *ptr = ((col >> 8) & 0xFF);
            ptr++;
            *ptr = ((col >> 16) & 0xFF);
            ptr;
            return;
    }
}

void LFBgraphics::drawStraightLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, unsigned int col) const {
    // Don't set mode inside the drawing function to use them in animations

    if (x1 == x2 && y2 > y1) {
        // Vertical line
        for (unsigned int i = y1; i <= y2; ++i) {
            drawPixel(x1, i, col);
        }
    } else if (y1 == y2 && x2 > x1) {
        // Horizontal line
        for (unsigned int i = x1; i <= x2; ++i) {
            drawPixel(i, y1, col);
        }
    } else {
        // Not straight
    }
}

// (x1, y1)---(x2, y1)
//    |          |
// (x1, y2)---(x2, y2)
void
LFBgraphics::drawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int col) const {
    drawStraightLine(x1, y1, x2, y1, col);
    drawStraightLine(x2, y1, x2, y2, col);
    drawStraightLine(x1, y2, x2, y2, col);
    drawStraightLine(x1, y1, x1, y2, col);
}

void LFBgraphics::drawCircle(unsigned int x, unsigned int y, unsigned int rad, unsigned int col) const {
    // TODO
}

void LFBgraphics::drawSprite(unsigned int width, unsigned int height, unsigned int bytes_pp,
                             const uint8_t *pixel_data) const {
    const uint8_t *ptr;
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            ptr = pixel_data + (x + y * width) * bytes_pp;

            switch (bytes_pp) {
                case 2:
                    // TODO: Never tested, probably doesn't work
                    drawPixel(x, y, RGB_24(*ptr & 0b11111000, ((*ptr & 0b111) << 3) | (*(ptr + 1) >> 5),
                                           *(ptr + 1) & 0b11111));  // RGB 565
                    break;
                case 3:
                case 4:
                    // Alpha gets ignored anyway
                    drawPixel(x, y, RGB_24(*ptr, *(ptr + 1), *(ptr + 2)));
                    break;
            }
        }
    }
}

/*****************************************************************************
 * Methode:         LFBgraphics::clear                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Bildschirm loeschen.                                     *
 *****************************************************************************/
void LFBgraphics::clear() const {
    auto *ptr = reinterpret_cast<uint32_t *>(lfb);
    unsigned int i;

    if (hfb == 0 || lfb == 0) {
        return;
    }

    if (mode == 0) {
        ptr = reinterpret_cast<uint32_t *>(hfb);
    }

    switch (bpp) {
        case 8:
            for (i = 0; i < ((xres / 4) * yres); i++) {
                *(ptr++) = 0;
            }
            return;
        case 15:
        case 16:
            for (i = 0; i < (2 * (xres / 4) * yres); i++) {
                *(ptr++) = 0;
            }
            return;
        case 24:
            for (i = 0; i < (3 * (xres / 4) * yres); i++) {
                *(ptr++) = 0;
            }
            return;
        case 32:
            for (i = 0; i < (4 * (xres / 4) * yres); i++) {
                *(ptr++) = 0;
            }
            return;
    }
}

/*****************************************************************************
 * Methode:         LFBgraphics::setDrawingBuff                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Stellt ein, ob in den sichtbaren Puffer gezeichnet wird. *
 *****************************************************************************/
void LFBgraphics::setDrawingBuff(int v) {
    mode = v;
}

/*****************************************************************************
 * Methode:         LFBgraphics::copyHiddenToVisible                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Kopiert den versteckten Puffer in den sichtbaren LFB.    *
 *****************************************************************************/
void LFBgraphics::copyHiddenToVisible() const {
    auto *sptr = reinterpret_cast<uint32_t *>(hfb);
    auto *dptr = reinterpret_cast<uint32_t *>(lfb);
    uint32_t i;

    if (hfb == 0 || lfb == 0) {
        return;
    }

    switch (bpp) {
        case 8:
            for (i = 0; i < ((xres / 4) * yres); i++) {
                *(dptr++) = *(sptr++);
            }
            return;
        case 15:
        case 16:
            for (i = 0; i < (2 * (xres / 4) * yres); i++) {
                *(dptr++) = *(sptr++);
            }
            return;
        case 24:
            for (i = 0; i < (3 * (xres / 4) * yres); i++) {
                *(dptr++) = *(sptr++);
            }
            return;
        case 32:
            for (i = 0; i < (4 * (xres / 4) * yres); i++) {
                *(dptr++) = *(sptr++);
            }
            return;
    }
}

void swap(uint32_t *a, uint32_t *b) {
    uint32_t h = *a;

    *a = *b;
    *b = h;
}

uint16_t abs(int32_t a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

}
