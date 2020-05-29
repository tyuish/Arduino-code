void setup() {
  
  pinMode(3, INPUT_PULLUP);// define pin two as input for push button
  pinMode(12, OUTPUT);// defind pin 10 as output
}

void loop() {
  
  int pusshed = digitalRead(3);// read pin 2 and put the result in the "pusshed" variable
  if(pusshed == LOW){
    digitalWrite(12, HIGH);// if pusheed is equal LOW, turn the pin 10 HIGH (give it 5v)
  }else{
    digitalWrite(12, LOW);// else set pin 10 to low or zero volt
  }
}
