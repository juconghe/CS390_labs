  #include <Ticker.h>
 #define PIN_BUZZER  13 // the digital pin the Buzzer is attached to
 #include <EEPROM.h>
 PROGMEM const int freqs[] = {31, 49, 78, 123, 196,  311, 494, 784, 1245, 1976, 3136,
 4978};
 Ticker secondTick;
 volatile int watchdogCount = 0;
// volatile int freqIdx = 0; //the index that will store the last frequency before it restarts.
// //The Watchdog Interrupt Service Routine (ISR)
 int EEPROM_Addr = 0;
 volatile int freqIdx;
 void ISRwatchdog() {
 watchdogCount++;
 //The watchdog will be waken up when the couter reaches 4
 if (watchdogCount == 4) {
  EEPROM.write(EEPROM_Addr,freqIdx);
  EEPROM.commit();
  ESP.restart(); //restarting the board
 } 
} 
 void setup() {
   ESP.wdtDisable(); // disabling the built-in watchdog
   EEPROM.begin(4096);
   Serial.begin(115200);
   secondTick.attach(1, ISRwatchdog); //registering the watchdog ISR
   pinMode(PIN_BUZZER, OUTPUT);
 }
 void loop() {
   // generating 50% PWM
//   Serial.print("Watchdog counter  = ");
//   Serial.println(watchdogCount);
   analogWrite(PIN_BUZZER, 256);
   freqIdx = EEPROM.read(EEPROM_Addr);
   Serial.println("Value in the EEPROM is ");
   Serial.println(freqIdx);
   
   analogWriteFreq(freqs[freqIdx]);
   //STEP 1: Write Freq
   freqIdx = random(0, sizeof(freqs)/sizeof(int));
   EEPROM.write(EEPROM_Addr,freqIdx);
   Serial.println("Writing new value into EEPROM");
   Serial.println(freqIdx);
   EEPROM.commit();   

   //depending on the value of delay, the program may wake up the watchdog
   delay(1000);
 } 
