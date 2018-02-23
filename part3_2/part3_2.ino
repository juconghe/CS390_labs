#include <Adafruit_NeoPixel.h>
#define PIN 5 // output for LED strip
#define NUM_LEDS 20 // number of LEDs on strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int red = 0;
int blue = 0;
int green = 0;
bool inc = true;
void setup() {
  strip.begin();
//  strip.show();
}

void loop() {
  for (int i=0; i<NUM_LEDS; i++) {
    changeColor();
    strip.setPixelColor(i,strip.Color(red,green,blue));
    strip.show();
//    delay(50);
  }
}


uint32_t changeColor() {
   if (inc) {
    if (red < 255) {
      red += 85;
    } else if (green < 255) {
      green += 85;
    } else if (blue < 255){
      blue ++;
    } else {
      inc = !inc;
    }
  } else {
    if (red > 0) {
      red -= 85;
    } else if (green > 0) {
      green -= 85;
    } else if (blue > 0){
      blue -= 85;
    } else {
      inc = !inc;
    }
  }
}
