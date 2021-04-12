#include <demo.h>
#include <math.h>
#include <config.h>
#include <display.h>
#include <renderer.h>

// globals

a3de::triangle meshCube[] = {
  
      // SOUTH
      { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
      { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },
  
      // EAST                                                      
      { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
      { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },
  
      // NORTH                                                     
      { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
      { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },
  
      // WEST                                                      
      { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
      { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },
  
      // TOP                                                       
      { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
      { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },
  
      // BOTTOM                                                    
      { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
      { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
  
    };

    a3de::mat4x4 matProj;

    a3de::scalar fTheta;

void demo::demo_init()
{
    // initialize display
    a3de::display_init();

    // Projection Matrix
    a3de::scalar fNear = 0.1f;
    a3de::scalar fFar = 1000.0f;
    a3de::scalar fFov = 90.0f;
    a3de::scalar fAspectRatio = (float)DISPLAY_HEIGHT / (float)DISPLAY_WIDTH;
    a3de::scalar fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    matProj.m[2][3] = 1.0f;
    matProj.m[3][3] = 0.0f;
}

void demo::demo_run()
{
    a3de::display.clearDisplay();
  // Set up rotation matrices
    a3de::mat4x4 matRotZ, matRotX;
    fTheta += 0.02f;

    // Rotation Z
    matRotZ.m[0][0] = cosf(fTheta);
    matRotZ.m[0][1] = sinf(fTheta);
    matRotZ.m[1][0] = -sinf(fTheta);
    matRotZ.m[1][1] = cosf(fTheta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    // Rotation X
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cosf(fTheta * 0.5f);
    matRotX.m[1][2] = sinf(fTheta * 0.5f);
    matRotX.m[2][1] = -sinf(fTheta * 0.5f);
    matRotX.m[2][2] = cosf(fTheta * 0.5f);
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
      triTranslated.p[0].z = triRotatedZX.p[0].z + 2.5f;
      triTranslated.p[1].z = triRotatedZX.p[1].z + 2.5f;
      triTranslated.p[2].z = triRotatedZX.p[2].z + 2.5f;

      // Project triangles from 3D --> 2D
      MultiplyMatrixVector(triTranslated.p[0], matProj, triProjected.p[0]);
      MultiplyMatrixVector(triTranslated.p[1], matProj, triProjected.p[1]);
      MultiplyMatrixVector(triTranslated.p[2], matProj, triProjected.p[2]);

      // Scale into view
      triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
      triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
      triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
      triProjected.p[0].x *= 0.5f * (float)DISPLAY_WIDTH;
      triProjected.p[0].y *= 0.5f * (float)DISPLAY_HEIGHT;
      triProjected.p[1].x *= 0.5f * (float)DISPLAY_WIDTH;
      triProjected.p[1].y *= 0.5f * (float)DISPLAY_HEIGHT;
      triProjected.p[2].x *= 0.5f * (float)DISPLAY_WIDTH;
      triProjected.p[2].y *= 0.5f * (float)DISPLAY_HEIGHT;

      // Rasterize triangle
      a3de::DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
        triProjected.p[1].x, triProjected.p[1].y,
        triProjected.p[2].x, triProjected.p[2].y);

    }
    
  a3de::display.display();
}