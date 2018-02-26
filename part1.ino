#define LED 2
bool isEnd = false;
int itr = 0;
int val = 51;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!isEnd) {
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    itr += 1;

    if (itr == 5) {
      isEnd = true;
      itr = 1;
    }
  } else {
    if (val <= 255) {
      analogWrite(LED,255 - val);
      delay(1000);
      val += 51;
    }
  }
}
