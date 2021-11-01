#include <config.h>
#include <renderer.h>
#include <display.h>
#include <triangle.h>

void a3de::DrawTriangle(const triangle& t)
{
    if(t.display_flags & B00000001) writeLine((int)t.p[0].x, (int)t.p[0].y, (int)t.p[1].x, (int)t.p[1].y);
    if(t.display_flags & B00000010) writeLine((int)t.p[0].x, (int)t.p[0].y, (int)t.p[2].x, (int)t.p[2].y);
    if(t.display_flags & B00000100) writeLine((int)t.p[2].x, (int)t.p[2].y, (int)t.p[1].x, (int)t.p[1].y);
}