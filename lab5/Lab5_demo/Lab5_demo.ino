// Define hardware constants 
#define REED_PIN  14
#define LED_PIN  15
#define PIN_BUTTON 0
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below
WiFiClient client;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "80a0eed50c01403983e52180020c0beb";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AHHA Lab Wifi";
char pass[] = "ramanujan";

bool isDoorOpen = true;
int isAlarmOn = 0;
bool isBtnPush = false;
bool writeDoorClose = false;

String msgType = "";
BlynkTimer timer;

void setup() 
{
  
  Serial.begin(115200);

  //Blynk Setup
  Blynk.begin(auth, ssid, pass);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), disable_alram, RISING);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  timer.setInterval(1000L, blinkLED);

 //Tamboo Setup
  Serial.println();
  WiFi.begin("AHHA Lab Wifi", "ramanujan"); //connecting to the router Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  } 
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP()); 
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
    msgType = "Alarm Off";
  } else {
    isBtnPush = false;
    msgType = "Alarm On";
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
  int proximity = digitalRead(REED_PIN);
  if (!isDoorOpen && (proximity == HIGH)) { // door was close but open now
    Serial.println("Door is open, alarm is on");
    isAlarmOn = 1;
    isBtnPush = false;
    isDoorOpen = true;
    writeDoorClose = false;
//    write_google_spreadsheet(); // write to google spreadsheet indicate door is open
//    write_google_spreadsheet(); // write to google spreadsheet indicate alarm is on
  } else if ((isAlarmOn == 0) && isBtnPush) { // alarm is disable by pressed btn
    Serial.println("Alarm is Disable by clicking btn");
    isBtnPush = false;
    writeDoorClose = false;
//    write_google_spreadsheet(); // write to google spreadsheet indicate alarm is disable
  } else if ((isAlarmOn == 0) && proximity == LOW && !writeDoorClose) {
    Serial.println("Door is close");
    isDoorOpen = false;
    writeDoorClose = true;
//    write_google_spreadsheet(); //write to google spreadsheet indicate door is close
  }
}


void write_google_spreadsheet()
{
   Serial.println("Writing to Google Spereadsheet");
   TembooChoreo AppendValuesChoreo(client);

    // Invoke the Temboo client
    AppendValuesChoreo.begin();

    // Set Temboo account credentials
    AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    AppendValuesChoreo.addInput("RefreshToken", "ya29.GluRBZ9-n5xa-A5bvVwxDPZ1KBgPiYQ4jXdRMKqvvbmFhs4Qdd9hhez2rRu-9lekuj-I2_Vp0kUWeUjQAZdgD-aYhDs-zGBGxE9Ig6BxYEwRiob7nOjO9EiJHXO5");
    AppendValuesChoreo.addInput("ClientSecret", "jHHiccijDRRK8bcogn9nM2X-");
    AppendValuesChoreo.addInput("Values", "[\n  [\n    \"100\",\n    \"200\",\n    \"" + msgType + "\"\n  ]\n]");
    AppendValuesChoreo.addInput("ClientID", "127543262575-95jg7drogo3imjot646coolce8itfekt.apps.googleusercontent.com");
    AppendValuesChoreo.addInput("SpreadsheetID", "1CuJdEk3rzZfXyq80wv71wsQbxmpHC0seigQ9jKi2kmQ");

                                                 
    // Identify the Choreo to run
    AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");
    
    // Run the Choreo; when results are available, print them to serial
    AppendValuesChoreo.run();
    
    while(AppendValuesChoreo.available()) {
      char c = AppendValuesChoreo.read();
      Serial.print(c);
    }
    AppendValuesChoreo.close();
  }

