int relayPin = 5;// define output pin for relay 
int relayPin2 = 4;// define output pin for relay 

void setup() {
  pinMode(relayPin, OUTPUT);// define pin 8 as output
  pinMode(relayPin2, OUTPUT);// define pin 8 as output

}

void loop() {
  
  digitalWrite(relayPin, LOW); // turn the relay ON (low is ON if relay is LOW trigger. change it to HIGH if you have got HIGH trigger relay)
  digitalWrite(relayPin2, HIGH); // turn the relay ON (low is ON if relay is LOW trigger. change it to HIGH if you have got HIGH trigger relay)

  delay(1000); // wait for 500 millisecond
 digitalWrite(relayPin, HIGH);// // turn the relay OFF (HIGH is OFF if relay is LOW trigger. change it to LOW if you have got HIGH trigger relay)
 digitalWrite(relayPin2, LOW);
 delay(1000);// wait for 500 millisecond
}
