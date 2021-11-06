#ifndef _A3DE_FIXP_MATH_H_
#define _A3DE_FIXP_MATH_H_
#include <stdint.h>

namespace a3de
{
    class fixed16_t 
    {
        // Constants for convenience. Should be evaluated at compile time.
        static constexpr int16_t c_scaling_exp = 4;
        static constexpr int16_t c_scaling_factor = 1 << c_scaling_exp;
        /*
            scaling factor used: 2^5
            number representation: 1/2^5 = 1/32
            error: < 0.016
            min possible value:	−1024.000 00
            max possible value:	+1023.968 75
        */
        public:            
            explicit constexpr fixed16_t(const int16_t& value);
            constexpr fixed16_t(const float& value);
            constexpr fixed16_t();
            constexpr operator double() const;
            constexpr operator float() const;
            constexpr operator int() const;

            // assignment operators
            void operator+=(const fixed16_t& rhs);
            void operator-=(const fixed16_t& rhs);
            void operator*=(const fixed16_t& rhs);
            void operator/=(const fixed16_t& rhs);

            // unary operators
            constexpr fixed16_t operator-() const;

            // binary operators
            constexpr fixed16_t operator+(const fixed16_t& rhs) const;           
            constexpr fixed16_t operator-(const fixed16_t& rhs) const;            
            constexpr fixed16_t operator*(const fixed16_t& rhs) const;           
            constexpr fixed16_t operator/(const fixed16_t& rhs) const;
            
        private:
            int16_t m_value;
    };

    constexpr fixed16_t operator"" _f16(long double value) noexcept;
    constexpr fixed16_t operator"" _f16(unsigned long long int value) noexcept;
}

using a3de::operator"" _f16;

#pragma region implementation
// constexpr functions must be defined in the header as it implies inline

constexpr a3de::fixed16_t::fixed16_t(const int16_t& value) :
    m_value(value)
{}

constexpr a3de::fixed16_t::fixed16_t(const float& value) :
    m_value(static_cast<int16_t>(value * c_scaling_factor + 0.5f))
{}

constexpr a3de::fixed16_t::fixed16_t() :
    m_value(0)
{}

constexpr a3de::fixed16_t::operator double() const { return (double)m_value/(double)c_scaling_factor; }
constexpr a3de::fixed16_t::operator float() const { return (float)m_value/(float)c_scaling_factor; }
constexpr a3de::fixed16_t::operator int() const { return (int)m_value/c_scaling_factor; }

constexpr a3de::fixed16_t a3de::fixed16_t::operator-() const
{
    return fixed16_t(static_cast<int16_t>(-m_value));
}

constexpr a3de::fixed16_t a3de::fixed16_t::operator+(const fixed16_t& n) const
{
    return fixed16_t(static_cast<int16_t>(m_value + n.m_value));
}

constexpr a3de::fixed16_t a3de::fixed16_t::operator-(const fixed16_t& n) const
{
    return fixed16_t(static_cast<float>(m_value - n.m_value));
}

constexpr a3de::fixed16_t a3de::fixed16_t::operator*(const fixed16_t& n) const
{
    /*
    To multiply two fixed-point numbers, 
    it suffices to multiply the two underlying integers, 
    and assume that the scaling factor of the result is the product of their scaling factors. 
    
    The result will be exact, with no rounding, provided that it does not overflow the receiving variable.

    For example, multiplying the numbers 123 scaled by 1/1000 (0.123) and 25 scaled by 1/10 (2.5) 
    yields the integer 123×25 = 3075 scaled by (1/1000)×(1/10) = 1/10000, that is 3075/10000 = 0.3075. 
    As another example, multiplying the first number by 155 implicitly scaled by 1/32 (155/32 = 4.84375) 
    yields the integer 123×155 = 19065 with implicit scaling factor (1/1000)×(1/32) = 1/32000, that is 19065/32000 = 0.59578125.

    In binary, it is common to use a scaling factor that is a power of two. 
    After the multiplication, the scaling factor can be divided away by shifting right. 
    Mechanically, this process is simple and fast in most computers. 
    Rounding is possible by adding a 'rounding addend' of half of the scaling factor before shifting; 
    The proof: round(x/y) = floor(x/y + 0.5) = floor((x + y/2)/y) = shift-of-n(x + 2^(n-1)) 
    A similar method is usable in any scaling. 

    --wikipedia
    */

    //the used scalingfactors are booth 2^5 -> therefore the result needs to be divided by 2^5
    return fixed16_t(static_cast<int16_t>((static_cast<int32_t>(m_value) * n.m_value) / c_scaling_factor));
}

constexpr a3de::fixed16_t a3de::fixed16_t::operator/(const fixed16_t& n) const
{
    /*
    To divide two fixed-point numbers, 
    one takes the integer quotient of their underlying integers, 
    and assumes that the scaling factor is the quotient of their scaling factors. 
    In general, the first division requires rounding and therefore the result is not exact.

    For example, division of 3456 scaled by 1/100 (34.56) and 1234 scaled by 1/1000 (1.234) 
    yields the integer 3456÷1234 = 3 (rounded) with scale factor (1/100)/(1/1000) = 10, that is, 30. 
    
    As another example, the division of the first number by 155 implicitly scaled by 1/32 (155/32 = 4.84375) 
    yields the integer 3456÷155 = 22 (rounded) with implicit scaling factor (1/100)/(1/32) = 32/100 = 8/25, 
    that is 22×32/100 = 7.04.

    If the result is not exact, the error introduced by the rounding can be reduced or even eliminated 
    by converting the dividend to a smaller scaling factor. For example, if r = 1.23 is represented as 123 
    with scaling 1/100, and s = 6.25 is represented as 6250 with scaling 1/1000, 
    then simple division of the integers yields 123÷6250 = 0 (rounded) 
    with scaling factor (1/100)/(1/1000) = 10. 
    If r is first converted to 1,230,000 with scaling factor 1/1000000, 
    the result will be 1,230,000÷6250 = 197 (rounded) with scale factor 1/1000 (0.197). The exact value 1.23/6.25 is 0.1968. 

    --wikipedia
    */

    //the used scalingfactors are booth 2^5 -> therefore the result needs to be multiplyed by 2^5
    //int32_t intermediate = m_value * c_scaling_factor;
    return fixed16_t(static_cast<int16_t>((static_cast<int32_t>(m_value) * c_scaling_factor) / n.m_value));
}

constexpr a3de::fixed16_t a3de::operator"" _f16(long double value) noexcept
{
    return fixed16_t(static_cast<float>(value));
}

constexpr a3de::fixed16_t a3de::operator"" _f16(unsigned long long int value) noexcept
{
    return fixed16_t(static_cast<int16_t>(value));
}
#pragma endregion

#endif