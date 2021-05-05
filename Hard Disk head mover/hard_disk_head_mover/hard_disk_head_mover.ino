

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(2,OUTPUT); //left
  pinMode(3,OUTPUT); //right

}

// the loop function runs over and over again forever
void loop() {
delay(1000);
digitalWrite(2,HIGH);

delay(1000);
digitalWrite(2,LOW);
}
