#include "pitches.h"
#define NOTE_ 0
#define PIN_BUZZER 13
#define PIN_BUTTON 0

int melody[] = {
  NOTE_, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_,
  NOTE_, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_,

  NOTE_, NOTE_G3, NOTE_A3, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_,
  NOTE_, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_,

  NOTE_, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_,
  NOTE_, NOTE_G3, NOTE_A3, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_,

  NOTE_, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4,
  NOTE_C4, NOTE_A3, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_,
  //
  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_A3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_,
  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_C4, NOTE_,

  NOTE_, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_,
  NOTE_, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_,

  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_A3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_,
  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_C4, NOTE_,

  NOTE_, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_G3, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_,
};

int noteDurations[] = {
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,

  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 8,
  16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 8, 8,

  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,

  16, 16, 16, 16, 16, 16, 16, 16, 8,
  16, 16, 16, 16, 16, 16, 8, 16, 4, 8,
  //
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,

  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 4, 8,
  16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 8,

  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,

  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 4,
  16, 8, 16, 16, 16, 4, 8,
};

void play_note(int freq) {
  if(freq>0) {
      // send square wave at freq Hz with 50% duty cycle
      analogWrite(PIN_BUZZER, 512);
      analogWriteFreq(freq);
    } else {
      analogWrite(PIN_BUZZER, 0);
    }
}

void setup() {
  // pin 12 is connected to the buzzer on the prototype board.
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  // play note at a given frequency
  for (int i = 0; i < sizeof(melody)/sizeof(int); i += 1) {
    int noteDuration = 3000 / noteDurations[i];
    play_note(melody[i]);
    delay(noteDuration * 1.30);
  }
}
