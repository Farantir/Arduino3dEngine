#include <triangle.h>
float a3de::mid_z(const a3de::triangle& t)
{
  return (t.p[0].z + t.p[1].z + t.p[2].z) / a3de::scalar(3.0f);
}