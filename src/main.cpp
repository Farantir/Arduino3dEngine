//Programa : Teste display Nokia 5110 usando biblioteca Adafruit
//Autor : Arduino e Cia
#include <Arduino.h>
#include <demo.h>

void setup()   
{
	demo::demo_init();
}
  
void loop()
{
	demo::demo_run();
}