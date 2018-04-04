// Define hardware constants 
#define REED_PIN  14
#define LED_PIN  15
#define PIN_BUTTON 0
#define PIN_BUZZER 13

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below
#include <time.h>
#include <Adafruit_NeoPixel.h>


WiFiClient client;
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

int timezone = -4;
int dst = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "80a0eed50c01403983e52180020c0beb";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "weihai";
char pass[] = "weihaihenshuai";

bool isDoorOpen = true;
int isAlarmOn = false;
bool isBtnPush = false;
bool writeDoorClose = false;
bool LEDOn = true;
bool systemOn = true;

BlynkTimer timer;

void setup() 
{
  
  Serial.begin(115200);

  //Blynk Setup
  pixel.begin();
  // lower brightness (default is 256)
  pixel.setBrightness(128);
  Blynk.begin(auth, ssid, pass);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), disable_alram, RISING);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  timer.setInterval(1000L, blinkLED);

 //Tamboo Setup
  Serial.println();
  WiFi.begin("weihai", "weihaihenshuai"); //connecting to the router Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  } 
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

BLYNK_WRITE(V0)
{
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  if (systemOn) {
      isAlarmOn = !isAlarmOn;
    if (isAlarmOn) {
      Blynk.virtualWrite(V1, "Alarm On");
      write_google_spreadsheet("Alarm on");
      isBtnPush = true;
     } else {
      Blynk.virtualWrite(V1, "Alarm Off");
      write_google_spreadsheet("Alarm Off");
      isBtnPush = false;
    }
  }
}

BLYNK_WRITE(V3) {
  if (systemOn) {
    write_google_spreadsheet("Called Police");
  }
}

BLYNK_WRITE(V4) {
  systemOn = !systemOn;
  if (systemOn) {
    write_google_spreadsheet("Turn On the System");
  } else {
    isAlarmOn = false;
    write_google_spreadsheet("Turn Off the System");
  }
}

void disable_alram() {
  if (systemOn) {
    isBtnPush = true;
    isAlarmOn = false;
  }  
}

void blinkLED()
{
  if (isAlarmOn) {
    if (LEDOn) {
      pixel.setPixelColor(0, pixel.Color(255, 0, 0));
      pixel.show();
      LEDOn = !LEDOn;
    } else {
      pixel.setPixelColor(0, pixel.Color(0, 0, 0));
      pixel.show();
      LEDOn = !LEDOn;
    }
  } else {
    pixel.setPixelColor(0, pixel.Color(0, 0, 0));
    pixel.show();
    LEDOn = true;
  }
}

void loop() 
{
  Blynk.run();
  timer.run();
    int proximity = digitalRead(REED_PIN);
    if (!isDoorOpen && (proximity == HIGH)) { // door was close but open now
      Serial.println("Door is open, alarm is on");
      Blynk.virtualWrite(V1, "Alarm On");
      Blynk.virtualWrite(V2, "Door Open");
      if (systemOn) {
         isAlarmOn = true;
         isBtnPush = false;
        Blynk.notify("Someone open the door!!!!");
        write_google_spreadsheet("Door Open"); // write to google spreadsheet indicate door is open
        write_google_spreadsheet("Alarm on"); // write to google spreadsheet indicate alarm is on
      }
      isDoorOpen = true;
      writeDoorClose = false;
    } else if ((!isAlarmOn) && isBtnPush) { // alarm is disable by pressed btn
      Serial.println("Alarm is Disable by clicking btn");
      Blynk.virtualWrite(V1, "Alarm Off");
      write_google_spreadsheet("RESET Button Pressed"); // write to google spreadsheet indicate alarm is disable
      isBtnPush = false;
    } else if (proximity == LOW && !writeDoorClose) {
      Serial.println("Door is close");
      Blynk.virtualWrite(V2, "Door Close");
      if (systemOn) {
        isBtnPush = false;
        write_google_spreadsheet("Door close"); //write to google spreadsheet indicate door is close
      }
      writeDoorClose = true;
      isDoorOpen = false;
    }

  if (isAlarmOn) {
      analogWrite(PIN_BUZZER, 512);
      analogWriteFreq(138);
  }else {
      analogWrite(PIN_BUZZER, 0);
  }
}


void write_google_spreadsheet(String msgType)
{
   Serial.println("Writing to Google Spereadsheet");
   time_t now = time(nullptr);
   String temp = ctime(&now);
   String tembooInput = "[[\""+ temp + "\",\"" + msgType + "\"]]";
   TembooChoreo AppendValuesChoreo(client);
    // Invoke the Temboo client
    AppendValuesChoreo.begin();

    // Set Temboo account credentials
    AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);
    
  // Set Choreo inputs
    AppendValuesChoreo.addInput("RefreshToken", "1/Wu7hLi2RMp6E6gKsB5qOh5sj2Q5NyHCh3y0VQsgSLqr_LVsyy-9kr4MIOueCz4pS");
    AppendValuesChoreo.addInput("ClientSecret", "jHHiccijDRRK8bcogn9nM2X-");
    AppendValuesChoreo.addInput("Values", tembooInput);
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

