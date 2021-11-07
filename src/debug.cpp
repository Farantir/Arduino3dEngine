#include <iostream>
#include <math.h>
#include <config.h>
#include <fixp_math.h>
#include <linalg.h>
#include <triangle.h>
int display[DISPLAY_HEIGHT][DISPLAY_WIDTH];
constexpr a3de::triangle meshCube[] = {
  
      // SOUTH
      { 0.0_f16, 0.0_f16, 0.0_f16,    0.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 0.0_f16, 5 },
      { 0.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 0.0_f16, 0.0_f16, 6 },
  
      // EAST                                                      
      { 1.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 1.0_f16, 4 },
      { 1.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 1.0_f16,    1.0_f16, 0.0_f16, 1.0_f16, 6 },
  
      // NORTH                                                     
      { 1.0_f16, 0.0_f16, 1.0_f16,    1.0_f16, 1.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 1.0_f16, 4 },
      { 1.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 1.0_f16, 6 },
  
      // WEST                                                      
      { 0.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 0.0_f16, 4 },
      { 0.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 1.0_f16, 0.0_f16,    0.0_f16, 0.0_f16, 0.0_f16, 6 },
  
      // TOP                                                       
      { 0.0_f16, 1.0_f16, 0.0_f16,    0.0_f16, 1.0_f16, 1.0_f16,    1.0_f16, 1.0_f16, 1.0_f16, 0 },
      { 0.0_f16, 1.0_f16, 0.0_f16,    1.0_f16, 1.0_f16, 1.0_f16,    1.0_f16, 1.0_f16, 0.0_f16, 0 },
  
      // BOTTOM                                                    
      { 1.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 0.0_f16, 0 },
      { 1.0_f16, 0.0_f16, 1.0_f16,    0.0_f16, 0.0_f16, 0.0_f16,    1.0_f16, 0.0_f16, 0.0_f16, 0 },
  
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
    constexpr a3de::scalar fAspectRatio = fix_displayheight / fix_displaywidth;
    a3de::scalar fFovRad = 1.0_f16 / a3de::scalar((float)tanf(fFov * 0.5_f16 / 180.0_f16 * 3.14159_f16));

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (fFar * fNear * -1.0_f16) / (fFar - fNear);
    matProj.m[2][3] = 1.0_f16;
    matProj.m[3][3] = 0.0_f16;


    std::cout << "fNear: " << (float)fNear << std::endl;
    std::cout << "fFar: " << (float)fFar << std::endl;
    std::cout << "fFov: " << (float)fFov << std::endl;
    std::cout << "fAspectRatio: " << (float)fAspectRatio << std::endl;
    std::cout << "fFovRad: " << (float)fFovRad << std::endl << std::endl;
    std::cout << "matProj.m[0][0]: " << (float)matProj.m[0][0] << std::endl;
    std::cout << "matProj.m[1][1]: " << (float)matProj.m[1][1] << std::endl;
    std::cout << "matProj.m[2][2]: " << (float)matProj.m[2][2] << std::endl;
    std::cout << "matProj.m[3][2]: " << (float)matProj.m[3][2] << std::endl;
    std::cout << "matProj.m[2][3]: " << (float)matProj.m[2][3] << std::endl;
    std::cout << "matProj.m[3][3]: " << (float)matProj.m[3][3] << std::endl <<std::endl;

}

//log a triangle
void logTriangle(a3de::triangle t)
{
  printf("x: %10f ",(float)t.p[0].x);
  printf("y: %10f ",(float)t.p[0].y);
  printf("z: %10f \n",(float)t.p[0].z);

  printf("x: %10f ",(float)t.p[1].x);
  printf("y: %10f ",(float)t.p[1].y);
  printf("z: %10f \n",(float)t.p[1].z);

  printf("x: %10f ",(float)t.p[2].x);
  printf("y: %10f ",(float)t.p[2].y);
  printf("z: %10f \n",(float)t.p[2].z);
}

constexpr a3de::scalar angle = 0.1_f16;

void renderDisplay()
{
  for(int j = 0; j < DISPLAY_WIDTH; j++)
  {
    std::cout << "__";
  }
  std::cout << "_" << std::endl;

  for(int i = 0; i < DISPLAY_HEIGHT; i++)
  {
    std::cout << "|";
    for(int j = 0; j < DISPLAY_WIDTH; j++)
    {
      if(display[i][j] == 1)
      {
        std::cout << "▒▒";
      }
      else
      {
        std::cout << "  ";
      }
    }
    std::cout << "|" << std::endl;
  }

  std::cout << "|";
  for(int j = 0; j < DISPLAY_WIDTH; j++)
  {
    std::cout << "__";
  }
  std::cout << "|" << std::endl;

}

void clearDisplay()
{
  
  for (int i = 0; i < DISPLAY_HEIGHT; i++)
  {
    for (int j = 0; j < DISPLAY_WIDTH; j++)
    {
      display[i][j] = 0;
    }
  }
}

//swaps two int values
void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

// TODO: We could move the four locations to the data segment and save stack memory:
// static display_coord sx0, sx1, sy0, sy1;
// And pass the coordinate values by reference.
void writeLine(int x0, int y0, int x1, int y1)
{
  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep)
  {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1)
  {
    swap(x0, x1);
    swap(y0, y1);
  }

  int dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int err = dx / 2;
  int ystep;

  if (y0 < y1)
  {
    ystep = 1;
  }
  else
  {
    ystep = -1;
  }

  for (; x0 <= x1; x0++)
  {
    if (steep)
    {
      display[y0][x0] = 1;
    } 
    else
    {
      display[x0][y0] = 1;
    }
    err -= dy;
    if (err < 0)
    {
      y0 += ystep;
      err += dx;
    }
  }
}

void DrawTriangle(const a3de::triangle& t)
{
    if(t.display_flags & 1) writeLine((int)t.p[0].x, (int)t.p[0].y, (int)t.p[1].x, (int)t.p[1].y);
    if(t.display_flags & 2) writeLine((int)t.p[0].x, (int)t.p[0].y, (int)t.p[2].x, (int)t.p[2].y);
    if(t.display_flags & 4) writeLine((int)t.p[2].x, (int)t.p[2].y, (int)t.p[1].x, (int)t.p[1].y);
}

void demo_run()
{
  clearDisplay();

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

    //log  fTheta
    std::cout << "fTheta: " << (float)fTheta << std::endl << std::endl;

    //log matRotZ
    std::cout << "matRotZ.m[0][0]: " << (float)matRotZ.m[0][0] << std::endl;
    std::cout << "matRotZ.m[0][1]: " << (float)matRotZ.m[0][1] << std::endl;
    std::cout << "matRotZ.m[1][0]: " << (float)matRotZ.m[1][0] << std::endl;
    std::cout << "matRotZ.m[1][1]: " << (float)matRotZ.m[1][1] << std::endl;
    std::cout << "matRotZ.m[2][2]: " << (float)matRotZ.m[2][2] << std::endl;
    std::cout << "matRotZ.m[3][3]: " << (float)matRotZ.m[3][3] << std::endl << std::endl;

    //log matRotX
    std::cout << "matRotX.m[0][0]: " << (float)matRotX.m[0][0] << std::endl;
    std::cout << "matRotX.m[0][1]: " << (float)matRotX.m[0][1] << std::endl;
    std::cout << "matRotX.m[0][2]: " << (float)matRotX.m[0][2] << std::endl;
    std::cout << "matRotX.m[1][1]: " << (float)matRotX.m[1][1] << std::endl;
    std::cout << "matRotX.m[1][2]: " << (float)matRotX.m[1][2] << std::endl;
    std::cout << "matRotX.m[2][1]: " << (float)matRotX.m[2][1] << std::endl;
    std::cout << "matRotX.m[2][2]: " << (float)matRotX.m[2][2] << std::endl;
    std::cout << "matRotX.m[3][3]: " << (float)matRotX.m[3][3] << std::endl << std::endl;


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

      std::cout << "Unchanged Triangle" << std::endl;
      logTriangle(tri);
      std::cout << std::endl << "Projekted Triangle" << std::endl;
      logTriangle(triProjected);
      std::cout << std::endl << "Translated Triangle" << std::endl;
      logTriangle(triTranslated);

      std::cout << "" << std::endl << std::endl;

      DrawTriangle(triProjected);

    }
  renderDisplay();
}

//wait for enter
void waitForEnter()
{
  std::cout << "Press ENTER to continue...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    demo_init();
    int frame = 0;
    while(1) 
    {
      frame ++;

      std::cout << std::endl << std::endl << "Frame: " << frame << std::endl;
      demo_run();
      waitForEnter();
    }
}