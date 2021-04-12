#include <config.h>
#include <renderer.h>
#include <display.h>

void a3de::DrawTriangle(const scalar& x1, const scalar& y1, const scalar& x2, const scalar& y2, const scalar& x3, const scalar& y3)
{
    writeLine((int)x1, (int)y1, (int)x2, (int)y2);
    writeLine((int)x1, (int)y1, (int)x3, (int)y3);
    writeLine((int)x3, (int)y3, (int)x2, (int)y2);
}