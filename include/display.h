#ifndef _A3DE_DISPLAY_H_
#define _A3DE_DISPLAY_H_

#include <config.h>
#include <SPI.h>
#include <Adafruit_PCD8544.h>
#include <stdint.h>

// --- CONFIGURATION OPTIONS
// DISPLAY_WIDTH    Display width in pixels
// DISPLAY_HEIGHT   Display height in pixels
// DISPLAY_PIN_SCLK Serial clock out (SCLK)
// DISPLAY_PIN_DIN  Serial data out (DIN)
// DISPLAY_PIN_DC   Data/Command select (D/C)
// DISPLAY_PIN_CS   LCD chip select (CS/CE)
// DISPLAY_PIN_RST  LCD reset (RST)

namespace a3de
{
    // Display instance
    extern Adafruit_PCD8544 display;

    // display coordinate type
    using display_coord = int16_t;

    // initialization
    void display_init();

    // --- drawing functions

    // uses bresenham's algorithm to draw a line onto the screen
    void writeLine(display_coord x0, display_coord y0, display_coord x1, display_coord y1);
}

#endif