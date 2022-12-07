/*****************************************************************************
 *                                                                           *
 *                             V B E D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo zu VESA.                                            *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.12.2016                      *
 *****************************************************************************/

#include "VBEdemo.h"
#include "bmp_hhu.cc"

/*****************************************************************************
 * Methode:         VBEdemo::linInterPol1D                                   *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Farbwert in einer Dimension interpoliert berechnen.      *
 *****************************************************************************/
int VBEdemo::linInterPol1D(int x, int xr, int l, int r) {
    return ((((l >> 16) * (xr - x) + (r >> 16) * x) / xr) << 16) | (((((l >> 8) & 0xFF) * (xr - x) + ((r >> 8) & 0xFF) * x) / xr) << 8) | (((l & 0xFF) * (xr - x) + (r & 0xFF) * x) / xr);
}

/*****************************************************************************
 * Methode:         VBEdemo::linInterPol2D                                   *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Farbwert in zwei Dimensionen interpoliert berechnen.     *
 *****************************************************************************/
int VBEdemo::linInterPol2D(int x, int y, int lt, int rt, int lb, int rb) {
    return linInterPol1D(y, Kernel::vesa.yres,
                         linInterPol1D(x, Kernel::vesa.xres, lt, rt),
                         linInterPol1D(x, Kernel::vesa.xres, lb, rb));
}

/*****************************************************************************
 * Methode:         VBEdemo::drawColors                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Pixel-Demo.                                              *
 *****************************************************************************/
void VBEdemo::drawColors() {
    int x_res = 640;
    int y_res = 480;

    for (int y = 0; y < y_res; y++) {
        for (int x = 0; x < x_res; x++) {
            Kernel::vesa.drawPixel(x, y, linInterPol2D(x, y, 0x0000FF, 0x00FF00, 0xFF0000, 0xFFFF00));
        }
    }
}

/*****************************************************************************
 * Methode:         VBEdemo::drawBitmap                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Bitmap aus GIMP ausgeben.                                *
 *****************************************************************************/
void VBEdemo::drawBitmap() {
    unsigned int sprite_width = hhu.width;
    unsigned int sprite_height = hhu.height;
    unsigned int sprite_bpp = hhu.bytes_per_pixel;
    const uint8_t* sprite_pixel = reinterpret_cast<const uint8_t*>(hhu.pixel_data);

    /* Hier muss Code eingefuegt werden */

    Kernel::vesa.drawSprite(sprite_width, sprite_height, sprite_bpp, sprite_pixel);
}

/*****************************************************************************
 * Methode:         VBEdemo::drawFonts                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Fonts ausgeben.                                          *
 *****************************************************************************/
void VBEdemo::drawFonts() {

    /* Hier muss Code eingefuegt werden */

    Kernel::vesa.drawString(Graphics::std_font_8x8, 0, 300, 0, "STD FONT 8x8", 12);
    Kernel::vesa.drawString(Graphics::std_font_8x16, 0, 320, 0, "STD FONT 8x16", 13);
}

/*****************************************************************************
 * Methode:         VBEdemo::run                                             *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Der Anwendungsthread erzeugt drei Threads die Zaehler    *
 *                  ausgeben und terminiert sich selbst.                     *
 *****************************************************************************/
void VBEdemo::run() {

    // In den Grafikmodus schalten (32-Bit Farbtiefe)
    Kernel::vesa.initGraphicMode(Device::MODE_640_480_24BITS);
    Kernel::vesa.setDrawingBuff(Device::BUFFER_VISIBLE);

    drawColors();

    /* Hier muss Code eingefuegt werden */
    Kernel::vesa.drawRectangle(100, 100, 300, 300, 0);
    drawBitmap();
    drawFonts();

    while (running) {}

    // selbst terminieren
    Kernel::scheduler.exit();
}
