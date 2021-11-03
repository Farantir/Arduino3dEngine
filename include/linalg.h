#ifndef _A3DE_LINALG_H_
#define _A3DE_LINALG_H_

namespace a3de
{
    // TODO: replace with some fancy fixed point type
    using scalar = float;

    struct vec3d
    {
        scalar x, y, z;
    };

    struct mat4x4
    {
        scalar m[4][4] = {};
    };

    // math functions
    void MultiplyMatrixVector(const vec3d &i, const mat4x4 &m, vec3d &o);    
}

#endif