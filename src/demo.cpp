#include <demo.h>
#include <math.h>
#include <config.h>
#include <display.h>
#include <renderer.h>
#include <fixp_math.h>

// globals

constexpr a3de::triangle meshCube[] = {
  
      // SOUTH
      { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f, B00000101 },
      { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f, B00000110 },
  
      // EAST                                                      
      { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f, B00000100 },
      { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f, B00000110 },
  
      // NORTH                                                     
      { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f, B00000100 },
      { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f, B00000110 },
  
      // WEST                                                      
      { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f, B00000100 },
      { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f, B00000110 },
  
      // TOP                                                       
      { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f, B00000000 },
      { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f, B00000000 },
  
      // BOTTOM                                                    
      { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, B00000000 },
      { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f, B00000000 },
  
    };

    a3de::mat4x4 matProj;

    a3de::scalar fTheta;

  constexpr a3de::scalar halve = 0.5_f16;
  constexpr a3de::scalar twpointfive = 0.5_f16;
  constexpr a3de::scalar one = 1.0_f16;
  constexpr a3de::scalar fix_displayheight = DISPLAY_HEIGHT;
  constexpr a3de::scalar fix_displaywidth = DISPLAY_WIDTH;

void demo::demo_init()
{
    // initialize display
    a3de::display_init();

    // Projection Matrix
    constexpr a3de::scalar fNear = 0.1f;
    constexpr a3de::scalar fFar = 1000.0f;
    constexpr a3de::scalar fFov = 90.0f;
    constexpr a3de::scalar fAspectRatio = fix_displayheight / fix_displaywidth;
    a3de::scalar fFovRad = 1.0_f16 / a3de::scalar((float)tanf(fFov * halve / 180.0_f16 * 3.14159_f16));

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (fFar * fNear * -1_f16) / (fFar - fNear);
    matProj.m[2][3] = 1.0f;
    matProj.m[3][3] = 0.0f;
}

constexpr a3de::scalar angle = 0.02f;

void demo::demo_run()
{
    a3de::display.clearDisplay();
  // Set up rotation matrices
    a3de::mat4x4 matRotZ, matRotX;
    fTheta += angle;

    // Rotation Z
    matRotZ.m[0][0] = cosf(fTheta);
    matRotZ.m[0][1] = sinf(fTheta);
    matRotZ.m[1][0] = -sinf(fTheta);
    matRotZ.m[1][1] = cosf(fTheta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    // Rotation X
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cosf(fTheta * halve);
    matRotX.m[1][2] = sinf(fTheta * halve);
    matRotX.m[2][1] = -sinf(fTheta * halve);
    matRotX.m[2][2] = cosf(fTheta * halve);
    matRotX.m[3][3] = 1;

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
      triTranslated.p[0].z = triRotatedZX.p[0].z + twpointfive;
      triTranslated.p[1].z = triRotatedZX.p[1].z + twpointfive;
      triTranslated.p[2].z = triRotatedZX.p[2].z + twpointfive;

      // Project triangles from 3D --> 2D
      MultiplyMatrixVector(triTranslated.p[0], matProj, triProjected.p[0]);
      MultiplyMatrixVector(triTranslated.p[1], matProj, triProjected.p[1]);
      MultiplyMatrixVector(triTranslated.p[2], matProj, triProjected.p[2]);

      // Scale into view
      triProjected.p[0].x += one; triProjected.p[0].y += one;
      triProjected.p[1].x += one; triProjected.p[1].y += one;
      triProjected.p[2].x += one; triProjected.p[2].y += one;
      triProjected.p[0].x *= halve * fix_displaywidth;
      triProjected.p[0].y *= halve * fix_displayheight;
      triProjected.p[1].x *= halve * fix_displaywidth;
      triProjected.p[1].y *= halve * fix_displayheight;
      triProjected.p[2].x *= halve * fix_displaywidth;
      triProjected.p[2].y *= halve * fix_displayheight;

      //copy over display information
      triProjected.display_flags = tri.display_flags;

      // Rasterize triangle
      a3de::DrawTriangle(triProjected);

    }
    
  a3de::display.display();
}