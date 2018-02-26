#include <Adafruit_NeoPixel.h>
#define LEDPIN 5 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIEXELS 20 // the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIEXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int count = 0;
void setup() {
  strip.begin(); // initialize the strip
  strip.setBrightness(64);
}

void loop() {
  rightToLeft();
  leftToRight();
  fade();  
}

void leftToRight() {
  for (int i = NUMBER_PIEXELS; i>=7; i--) {
    strip.setPixelColor(i,0,0,0);
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

void rightToLeft() {
  for (int i=0; i<NUMBER_PIEXELS-7; i++) {
    strip.setPixelColor(i,0,0,0);
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
}

void fade() {
  int red = random(0,256);
  int green = random(0, 256);
  int blue = random(0, 256);
  for(int j = 255; j >= 0; j--) {
    for (int i = 0; i< NUMBER_PIEXELS; i++) {
      strip.setPixelColor(i,red*j/255,green*j/255,blue*j/255);
    }
    strip.show();
    delay(30);
  }
  for (int j = 0; j < 255; j++){
    for (int i = 0; i < NUMBER_PIEXELS; i++) {
      strip.setPixelColor(i,red*j/255,green*j/255,blue*j/255);
    }
    strip.show();
    delay(30);
  }
}

