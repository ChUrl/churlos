// Jakob Falke, oostubs
// Github: https://gitlab.cs.fau.de/um15ebek/oostubs

// Schriften in Form von Rastergrafiken (separate Datein)
// Generiert mit cpi2fnt
// Keine Proportionalschriften
// Monochrome Speicherung: 1 Bit pro Pixel
// Je nach Breite wird auf Bytegrenzen aufgerundet:
//  8 Pixel -> 1 Byte; 12 Pixel -> 2 Byte

#ifndef FONTS_H__
#define FONTS_H__

#include <cstdint>
#include "lib/container//Array.h"

namespace Graphics {

class Font {
public:
    virtual ~Font() = default;

    virtual const uint8_t *getChar(uint32_t c) const = 0;

    virtual uint32_t get_char_width() const = 0;

    virtual uint32_t get_char_height() const = 0;
};

template<uint32_t width, uint32_t height, const uint8_t *data>
class FontInstance : public Font {
    const uint32_t char_width;
    const uint32_t char_height;
    const uint32_t char_mem_size;
    const uint8_t *font_data;

public:
    FontInstance() : char_width(width), char_height(height),
                     char_mem_size((((char_width + (8 >> 1)) / 8) * char_height)), font_data(data) {}

    inline const uint8_t *getChar(uint32_t c) const override {
        return &font_data[char_mem_size * c];
    }

    inline uint32_t get_char_width() const override {
        return char_width;
    }

    inline uint32_t get_char_height() const override {
        return char_height;
    }
};

extern const uint8_t fontdata_8x16[];
extern const uint8_t fontdata_8x8[];

using Font_8x16 = FontInstance<8, 16, fontdata_8x16>;
using Font_8x8 = FontInstance<8, 8, fontdata_8x8>;

extern const Font_8x16 std_font_8x16;
extern const Font_8x8 std_font_8x8;

}

#endif
