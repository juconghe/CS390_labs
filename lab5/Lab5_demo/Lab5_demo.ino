/******************************************************************************
Reed_Switch_Example.ino
Example sketch for SparkFun's Reed Switch
  (https://www.sparkfun.com/products/8642)
Jim Lindblom @ SparkFun Electronics
May 3, 2016

The reed switch is a two-terminal, magnetically-actuated, normally-open switch.
Connect one end of the switch to ground, and the other to Arduino's D2 pin.

The D2 pin's internal pull-up resistor is used to bias the pin high. When the
switch closes, the pin should go low.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
#define REED_PIN  14
#define LED_PIN  15
#define PIN_BUTTON 0
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "80a0eed50c01403983e52180020c0beb";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AHHA Lab Wifi";
char pass[] = "ramanujan";
int isAlarmOn = 0;
bool isBtnPush = false;
BlynkTimer timer;

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), disable_alram, RISING);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  timer.setInterval(1000L, blinkLED);
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  isAlarmOn = pinValue;
  if (pinValue == 0) {
    isBtnPush = true;
  }
  
}

void disable_alram() {
  isBtnPush = true;
  isAlarmOn = 0;
}

void blinkLED()
{
  if (isAlarmOn == 0) {
    Serial.println("LED on V1: off");
  } else {
    Serial.println("LED on V1: on");
  }
}

void loop() 
{
  Blynk.run();
  timer.run();
  if (digitalRead(REED_PIN) == LOW) // If the pin reads low, the switch is closed.
  {
    isAlarmOn = 0;
    isBtnPush = false;
  }
  else
  {
    if (isBtnPush == false) {
       isAlarmOn = 1;
    }
  }
}

