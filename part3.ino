#include <Adafruit_NeoPixel.h>
#define LEDPIN 5 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIEXELS 20 // the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIEXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int count = 0;
void setup() {
  strip.begin(); // initialize the strip
}

void loop() {
  for (int i=0; i<NUMBER_PIEXELS-7; i++) {
    strip.setPixelColor(i,255,255,255);
    strip.setPixelColor(i+1,    25, 0, 25); 
    strip.setPixelColor(i+2,  255, 0, 255); 
    strip.setPixelColor(i+3, 0, 0, 150); 
    strip.setPixelColor(i+4,  0, 150, 0); 
    strip.setPixelColor(i+5,  255, 255, 0); 
    strip.setPixelColor(i+6,  110, 70, 0); 
    strip.setPixelColor(i+7,  150, 0, 0); 
    strip.show();
    delay(100);
  }

  for (int i = NUMBER_PIEXELS; i>=7; i--) {
    strip.setPixelColor(i,255,255,255);
    strip.setPixelColor(i-7,  150, 0, 0);
    strip.setPixelColor(i-6,  110, 70, 0);
    strip.setPixelColor(i-5,  255, 255, 0);
    strip.setPixelColor(i-4,  0, 150, 0);
    strip.setPixelColor(i-3, 0, 0, 150);
    strip.setPixelColor(i-2,  255, 0, 255);
    strip.setPixelColor(i-1,    25, 0, 25);
    strip.show();
    delay(100);  
  }
}
