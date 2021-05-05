#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.begin(9600);
  
  Serial.println();

}
int lastScan;
int currentMillis;
bool stateLeft,stateRight;
bool hold0 = true;
bool hold1 = true;
void loop() {
  currentMillis=millis();
  Serial.println(String(stateLeft)+" "+String(stateRight));

  if(digitalRead(4)==LOW){
    stateLeft=true;
    
  }
  if(digitalRead(5)==LOW){
    stateRight=true;
    stateLeft=true;
  }
  if(digitalRead(6)==LOW){
    stateLeft=false;
    stateRight=false;
  }

  if(stateRight==false){
    digitalWrite(2,HIGH);
  }else{
    digitalWrite(2,LOW);
  }

   if(stateLeft==false){
    digitalWrite(3,HIGH);
    if(hold1){
      digitalWrite(8,HIGH);
      delay(100);
      digitalWrite(8,LOW);
      delay(100);
      digitalWrite(8,HIGH);
      delay(100);
      digitalWrite(8,LOW);

      hold1=false;
    }
    
    hold0=true;
  }else{
    digitalWrite(3,LOW);

    if(hold0){
      digitalWrite(8,HIGH);
      delay(100);
      digitalWrite(8,LOW);
      delay(100);
      digitalWrite(8,HIGH);
      delay(100);
      digitalWrite(8,LOW);

      hold0=false;
    }
    hold1=true;
  }



   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "8A 3E CE 81" or content.substring(1) == "3A F0 AF 82" or content.substring(1) == "6A 61 A6 82" or content.substring(1) == "0A E7 9C 82" or content.substring(1) == "FA 12 C0 81" or content.substring(1) == "63 8A 08 19")
  {
    
    if(currentMillis-lastScan>5000){
    Serial.println("Authorized access");
    lastScan=millis();
    if (stateLeft){
      stateLeft=false;
      stateRight=false; 
    }else{
      stateLeft=true; 
    }
    //delay(3000);
    }else{
      Serial.println("You are beeing rate limited.");
    }
  }
 
 else   {
    Serial.println(" Access denied");
  }
}
