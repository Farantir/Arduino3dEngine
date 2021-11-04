#include <fixp_math.h>

a3de::fixed16_t::fixed16_t(const int16_t& value) :
    m_value(value)
{
}

a3de::fixed16_t::fixed16_t(const float& value) :
    m_value(static_cast<int16_t>(value * c_scaling_factor + 0.5f))
{
}

a3de::fixed16_t::fixed16_t() :
    m_value(0)
{
}

a3de::fixed16_t a3de::fixed16_t::operator+(const fixed16_t& n) const
{
    return fixed16_t(m_value + n.m_value);
}

a3de::fixed16_t a3de::fixed16_t::operator-(const fixed16_t& n) const
{
    return fixed16_t(m_value - n.m_value);
}

void a3de::fixed16_t::operator+=(const fixed16_t& n)
{
    m_value = (m_value + n.m_value);
}

a3de::fixed16_t::operator double() const { return (float)m_value/(float)c_scaling_factor; }
a3de::fixed16_t::operator int() const { return (int)m_value/c_scaling_factor;}

a3de::fixed16_t a3de::fixed16_t::operator*(const fixed16_t& n) const
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
    return fixed16_t((m_value * n.m_value) / c_scaling_factor);
}

void a3de::fixed16_t::operator*=(const fixed16_t& n)
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
    m_value = (m_value * n.m_value) / c_scaling_factor;
}

a3de::fixed16_t a3de::fixed16_t::operator/(const fixed16_t& n) const
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
    return fixed16_t((m_value / n.m_value) * c_scaling_factor);
}

void a3de::fixed16_t::operator/=(const fixed16_t& n)
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
    m_value = (m_value / n.m_value) * c_scaling_factor;
}