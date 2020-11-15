#define ONBOARD_LED  2
 
void setup() {
  pinMode(ONBOARD_LED,OUTPUT);
}
 
void loop() {
  delay(2000);
  for (int i = 0; i <= 3; i++) {
    digitalWrite(ONBOARD_LED,HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED,LOW);
    delay(100);
  }
}
