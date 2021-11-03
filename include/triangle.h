#ifndef _A3DE_TRIANGLE_H_
#define _A3DE_TRIANGLE_H_
#include <linalg.h>
#include <stdint.h>

namespace a3de
{
    struct triangle
    {
        vec3d p[3];
        /**
         * Denotes the drawing instructions for the triangle.
         * the first 3 bits denote the visibility of the individual edges, the other bytes are not specifyed by now.
         * could be used for opacity or effekts
         */
        uint8_t display_flags;
    };

    float mid_z(const a3de::triangle& t);
}

#endif