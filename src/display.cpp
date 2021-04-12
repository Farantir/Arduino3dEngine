#include <display.h>
#include <config.h>
#include <util.h>

// globals

Adafruit_PCD8544 a3de::display = Adafruit_PCD8544(
        DISPLAY_PIN_SCLK,
        DISPLAY_PIN_DIN,
        DISPLAY_PIN_DC,
        DISPLAY_PIN_CS,
        DISPLAY_PIN_RST);

void a3de::display_init()
{
    Serial.begin(DISPLAY_BAUD_RATE);
    display.begin();
}

// TODO: We could move the four locations to the data segment and save stack memory:
// static display_coord sx0, sx1, sy0, sy1;
// And pass the coordinate values by reference.
void a3de::writeLine(display_coord x0, display_coord y0, display_coord x1, display_coord y1)
{
  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep)
  {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1)
  {
    swap(x0, x1);
    swap(y0, y1);
  }

  display_coord dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  display_coord err = dx / 2;
  display_coord ystep;

  if (y0 < y1)
  {
    ystep = 1;
  }
  else
  {
    ystep = -1;
  }

  for (; x0 <= x1; x0++)
  {
    if (steep)
    {
      display.drawPixel(y0, x0, 1);
    } 
    else
    {
      display.drawPixel(x0, y0, 1);
    }
    err -= dy;
    if (err < 0)
    {
      y0 += ystep;
      err += dx;
    }
  }
}