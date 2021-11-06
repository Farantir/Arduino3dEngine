#include <iostream>
#include <math.h>
#include <config.h>
#include <fixp_math.h>
#include <linalg.h>
#include <triangle.h>

constexpr a3de::triangle meshCube[] = {
  
      // SOUTH
      { 0.0_f16, 0.0_f16, 0.0_f16,    0.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 0.0_f16, 1 },
      { 0.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 0.0_f16, 0.0_f16, 1 },
  
      // EAST                                                      
      { 1.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 1.0_f16, 1 },
      { 1.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 1.0_f16,    1.0_f16, 0.0_f16, 1.0_f16, 1 },
  
      // NORTH                                                     
      { 1.0_f16, 0.0_f16, 1.0_f16,    1.0_f16, 1.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 1.0_f16, 1 },
      { 1.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 1.0_f16, 1 },
  
      // WEST                                                      
      { 0.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 0.0_f16, 1 },
      { 0.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 0.0_f16,    0.0_f16, 0.0_f16, 0.0_f16, 1 },
  
      // TOP                                                       
      { 0.0_f16, 1.0_f16, 0.0_f16,    0.0_f16, 1.0_f16, 1.0_f16,    1.0_f16, 1.0_f16, 1.0_f16, 1 },
      { 0.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 1.0_f16,    1.0_f16, 1.0_f16, 0.0_f16, 1 },
  
      // BOTTOM                                                    
      { 1.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 0.0_f16, 1 },
      { 1.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 0.0_f16, 0.0_f16, 1 },
  
    };

    a3de::mat4x4 matProj;

    a3de::scalar fTheta;

  constexpr a3de::scalar fix_displayheight = DISPLAY_HEIGHT;
  constexpr a3de::scalar fix_displaywidth = DISPLAY_WIDTH;

void demo_init()
{

    // Projection Matrix
    constexpr a3de::scalar fNear = 0.1_f16;
    constexpr a3de::scalar fFar = 1000.0_f16;
    constexpr a3de::scalar fFov = 90.0_f16;
    constexpr a3de::scalar fAspectRatio = static_cast<float>(fix_displayheight) / static_cast<float>(fix_displaywidth);
    a3de::scalar fFovRad = 1.0_f16 / a3de::scalar((float)tanf(fFov * 0.5_f16 / 180.0_f16 * 3.14159_f16));

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (fFar * fNear * -1.0_f16) / (fFar - fNear);
    matProj.m[2][3] = 1.0_f16;
    matProj.m[3][3] = 0.0_f16;


    std::cout << "fNear: " << (int)fNear << std::endl;
    std::cout << "fFar: " << (int)fFar << std::endl;
    std::cout << "fFov: " << (int)fFov << std::endl;
    std::cout << "fAspectRatio: " << (int)fAspectRatio << std::endl;
    std::cout << "fFovRad: " << (int)fFovRad << std::endl;
    std::cout << "matProj.m[0][0]: " << (int)matProj.m[0][0] << std::endl;
    std::cout << "matProj.m[1][1]: " << (int)matProj.m[1][1] << std::endl;
    std::cout << "matProj.m[2][2]: " << (int)matProj.m[2][2] << std::endl;
    std::cout << "matProj.m[3][2]: " << (int)matProj.m[3][2] << std::endl;
    std::cout << "matProj.m[2][3]: " << (int)matProj.m[2][3] << std::endl;
    std::cout << "matProj.m[3][3]: " << (int)matProj.m[3][3] << std::endl;

}

constexpr a3de::scalar angle = 0.02_f16;

void demo_run()
{
  // Set up rotation matrices
    a3de::mat4x4 matRotZ, matRotX;
    fTheta += angle;

    // Rotation Z
    matRotZ.m[0][0] = cosf(fTheta);
    matRotZ.m[0][1] = sinf(fTheta);
    matRotZ.m[1][0] = -sinf(fTheta);
    matRotZ.m[1][1] = cosf(fTheta);
    matRotZ.m[2][2] = 1.0_f16;
    matRotZ.m[3][3] = 1.0_f16;

    // Rotation X
    matRotX.m[0][0] = 1.0_f16;
    matRotX.m[1][1] = cosf(fTheta * 0.5_f16);
    matRotX.m[1][2] = sinf(fTheta * 0.5_f16);
    matRotX.m[2][1] = -sinf(fTheta * 0.5_f16);
    matRotX.m[2][2] = cosf(fTheta * 0.5_f16);
    matRotX.m[3][3] = 1.0_f16;

    // Draw Triangles
    for (auto tri : meshCube)
    {
     
      a3de::triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

      // Rotate in Z-Axis
      MultiplyMatrixVector(tri.p[0], matRotZ, triRotatedZ.p[0]);
      MultiplyMatrixVector(tri.p[1], matRotZ, triRotatedZ.p[1]);
      MultiplyMatrixVector(tri.p[2], matRotZ, triRotatedZ.p[2]);

      // Rotate in X-Axis
      MultiplyMatrixVector(triRotatedZ.p[0], matRotX, triRotatedZX.p[0]);
      MultiplyMatrixVector(triRotatedZ.p[1], matRotX, triRotatedZX.p[1]);
      MultiplyMatrixVector(triRotatedZ.p[2], matRotX, triRotatedZX.p[2]);

      // Offset into the screen
      triTranslated = triRotatedZX;
      triTranslated.p[0].z = triRotatedZX.p[0].z + 2.5_f16;;
      triTranslated.p[1].z = triRotatedZX.p[1].z + 2.5_f16;;
      triTranslated.p[2].z = triRotatedZX.p[2].z + 2.5_f16;;

      // Project triangles from 3D --> 2D
      MultiplyMatrixVector(triTranslated.p[0], matProj, triProjected.p[0]);
      MultiplyMatrixVector(triTranslated.p[1], matProj, triProjected.p[1]);
      MultiplyMatrixVector(triTranslated.p[2], matProj, triProjected.p[2]);

      // Scale into view
      triProjected.p[0].x += 1.0_f16; triProjected.p[0].y += 1.0_f16;
      triProjected.p[1].x += 1.0_f16; triProjected.p[1].y += 1.0_f16;
      triProjected.p[2].x += 1.0_f16; triProjected.p[2].y += 1.0_f16;
      triProjected.p[0].x *= 0.5_f16 * fix_displaywidth;
      triProjected.p[0].y *= 0.5_f16 * fix_displayheight;
      triProjected.p[1].x *= 0.5_f16 * fix_displaywidth;
      triProjected.p[1].y *= 0.5_f16 * fix_displayheight;
      triProjected.p[2].x *= 0.5_f16 * fix_displaywidth;
      triProjected.p[2].y *= 0.5_f16 * fix_displayheight;

      //copy over display information
      triProjected.display_flags = tri.display_flags;

    }

}

int main()
{
    demo_init();
    demo_run();
}