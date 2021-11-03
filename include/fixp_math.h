#ifndef _A3DE_FIXP_MATH_H_
#define _A3DE_FIXP_MATH_H_
#include <stdint.h>

namespace a3de
{
    class fixed16_t 
    {
        public:
            int16_t value;
            explicit fixed16_t(int16_t);
            //explicit fixed16_t(float);

            fixed16_t operator+(const fixed16_t&);
            fixed16_t operator-(const fixed16_t&);
            fixed16_t operator*(const fixed16_t&);
            fixed16_t operator/(const fixed16_t&);
    };
}

#endif