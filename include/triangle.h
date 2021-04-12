#ifndef _A3DE_TRIANGLE_H_
#define _A3DE_TRIANGLE_H_
#include <linalg.h>

namespace a3de
{
    struct triangle
    {
        vec3d p[3];
    };

    float mid_z(const a3de::triangle& t);
}

#endif