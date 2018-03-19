#include <Adafruit_NeoPixel.h>
#define PIN 5 // output for LED strip
#define NUM_LEDS 20 // number of LEDs on strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int red = 0;
int blue = 0;
int green = 0;
int m;
void setup() {
  strip.begin();
//  strip.show();
}

void loop() {
  m = random(0,100);
  if (m > 10) {
    for (int i=0; i<NUM_LEDS; i++) {
      changeColor();
      strip.setPixelColor(i,strip.Color(red,green,blue));
    }
    strip.show();
    delay(50);
  } else {
    red = 255;
    green = 255;
    blue = 255;
    fade();
  }
}


uint32_t changeColor() {
   red = random(0,256);
   green = random(0,256);
   blue = random(0,256);
}

void fade() {
  for(int i = 255; i >= 0; i--) {
    for( int j = 0; j > NUM_LEDS; j++) {
      strip.setPixelColor(j,strip.Color(red*i/255, green*i/255, blue*i/255));
      strip.show();
      delay(3);
    }
  }
}

