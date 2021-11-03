#ifndef _A3DE_FIXP_MATH_H_
#define _A3DE_FIXP_MATH_H_
#include <stdint.h>

namespace a3de
{
    class fixed16_t 
    {
        // Constants for convenience. Should be evaluated at compile time.
        static constexpr int16_t c_scaling_exp = 5;
        static constexpr int16_t c_scaling_factor = 1 << c_scaling_exp;
        /*
            scaling factor used: 2^5
            number representation: 1/2^5 = 1/32
            error: < 0.016
            min possible value:	−1024.000 00
            max possible value:	+1023.968 75
        */
        public:            
            explicit fixed16_t(const int16_t& value);
            explicit fixed16_t(const float& value);

            fixed16_t operator+(const fixed16_t& rhs) const;
            fixed16_t operator-(const fixed16_t& rhs) const;
            fixed16_t operator*(const fixed16_t& rhs) const;
            fixed16_t operator/(const fixed16_t& rhs) const;
        private:
            int16_t m_value;
    };
}

#endif