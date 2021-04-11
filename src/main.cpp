//Programa : Teste display Nokia 5110 usando biblioteca Adafruit
//Autor : Arduino e Cia
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)

#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 48

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

struct vec3d
{
  float x, y, z;
};

struct triangle
{
  vec3d p[3];
};

struct mat4x4
{
  float m[4][4] = { 0 };
};


int inline swap(int16_t &a,int16_t &b)
{
  const int c = a;
  a = b;
  b = c;  
}

void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    if (steep) {
      display.drawPixel(y0, x0, 1);
    } else {
      display.drawPixel(x0, y0, 1);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

triangle meshCube[] = {
  
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



mat4x4 matProj;

float fTheta;

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
{
  o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
  o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
  o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
  float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

  if (w != 0.0f)
  {
    o.x /= w; o.y /= w; o.z /= w;
  }
}
  
void setup()   
{
  Serial.begin(9600);
  display.begin();
    // Projection Matrix
    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float)DISPLAY_HEIGHT / (float)DISPLAY_WIDTH;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

    matProj.m[0][0] = fAspectRatio * fFovRad;
    matProj.m[1][1] = fFovRad;
    matProj.m[2][2] = fFar / (fFar - fNear);
    matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    matProj.m[2][3] = 1.0f;
    matProj.m[3][3] = 0.0f;
}

void DrawTriangle(float x1,float y1,float x2,float y2,float x3,float y3)
{
  
  writeLine((int)x1,(int)y1,(int)x2, (int)y2);
  writeLine((int)x1,(int)y1,(int)x3, (int)y3);
  writeLine((int)x3,(int)y3,(int)x2, (int)y2);
}

float mid_z(triangle t)
{
  return (t.p[0].z + t.p[1].z + t.p[2].z)/3;
}


void shellsort (int *array, int elemente) {
  int i, j, temp, n;

   /* Anfangswert fü^ elemente; i++) {
        temp = array[i];
        /* Größer als temp und nicht elemente
         * sowie >= und nicht > */
        for(j = i;
            j >= n && array[j-n] > temp;
            j -= n) {
           array[j] = array[j-n];
        }
        array[j] = temp;
     //}
  //}
}
  
void loop()
{

   display.clearDisplay();
  // Set up rotation matrices
    mat4x4 matRotZ, matRotX;
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
     
      triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

      // Rotate in Z-Axis
      MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
      MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
      MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

      // Rotate in X-Axis
      MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
      MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
      MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

      // Offset into the screen
      triTranslated = triRotatedZX;
      triTranslated.p[0].z = triRotatedZX.p[0].z + 2.5f;
      triTranslated.p[1].z = triRotatedZX.p[1].z + 2.5f;
      triTranslated.p[2].z = triRotatedZX.p[2].z + 2.5f;

      // Project triangles from 3D --> 2D
      MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
      MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
      MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

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
      DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
        triProjected.p[1].x, triProjected.p[1].y,
        triProjected.p[2].x, triProjected.p[2].y);

    }
    
  display.display();
}