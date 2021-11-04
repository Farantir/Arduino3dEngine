#include <triangle.h>
float a3de::mid_z(const a3de::triangle& t)
{
  return static_cast<float>((t.p[0].z + t.p[1].z + t.p[2].z) / 3.0_f16);
}