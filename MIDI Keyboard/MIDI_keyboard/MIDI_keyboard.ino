#include <MIDIUSB.h>
#include <Keypad.h>
const byte ROWS = 8;
const byte COLS = 8;
float amp;
byte colPins[COLS] = {0,1,2,3,4,5,6};

byte rowPins[ROWS] = {7,8,9,10,11,12,13};

const String keys[ROWS][COLS] = {
{"0","8","16","24","32","40","48","56"},
{"1","9","17","25","33","41","49","57"},
{"2","10","18","26","34","42","50","58"},
{"3","11","19","27","35","43","51","59"},
{"4","12","20","28","36","44","52","60"},
{"5","13","21","29","37","45","53","61"},
{"6","14","22","30","38","46","54","62"},
{"7","15","23","31","39","47","55","63"},
};


const int selectPinsX[3] = {4,5,6};
const int selectPinsY[3] = {7,8,9};


bool oldState[ROWS][COLS];
bool state[ROWS][COLS];
void setup() {

  //--------X--------
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);

digitalWrite(4,HIGH);
digitalWrite(5,HIGH);
digitalWrite(6,HIGH);


  //--------Y--------

pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);

digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);

pinMode(A0,INPUT); //--Y
pinMode(A1,OUTPUT); //--X
pinMode(A2,INPUT_PULLUP);
Serial.begin(9600);
}



int selectMuxPinX (const byte which)
  {
  // select correct MUX channel
  digitalWrite (selectPinsX[0], (which & 1) ? HIGH : LOW);  // low-order bit
  digitalWrite (selectPinsX[1], (which & 2) ? HIGH : LOW);
  digitalWrite (selectPinsX[2], (which & 4) ? HIGH : LOW);  // high-order bit
  // now read the sensor
  return analogRead (A0);
  } 




void WriteMuxPinY(byte pin,int value){
  for (int i=0; i<3; i++)
  {
   
  digitalWrite (selectPinsY[0], (pin & 1) ? HIGH : LOW);  // low-order bit
  digitalWrite (selectPinsY[1], (pin & 2) ? HIGH : LOW);
  digitalWrite (selectPinsY[2], (pin & 4) ? HIGH : LOW);  // high-order bit
   analogWrite(A1,value);
   
  }
}


void loop() {

 amp = (analogRead(A2)/7);
  if(amp>125)
    amp=125;
    
   /*
   for (byte i = 0; i < 8; i++)
    {
      int a = selectMuxPin(i);
    Serial.print ("Sensor ");
    Serial.print (i);
    Serial.print (" reads: ");
    Serial.println (a);
    delay (250);
    }
    Serial.println ("------------------");
  delay (1000);
  */
  
  
 for(int i=0;i<COLS;i++){
  for(int o=0;o<ROWS;o++){
 // pinMode(colPins[i],OUTPUT);
  WriteMuxPinY(i,255);
 // pinMode(rowPins[o],INPUT_PULLUP);
    
 // Serial.println(i);
  //Serial.println(o);
  
 //Serial.println(selectMuxPinX(o));


  
  if(selectMuxPinX(o)>365){
    state[i][o] = true;
    if(oldState[i][o]!=state[i][o]&&oldState[i][o]==false){
      noteOn(1,24+keys[i][o].toInt(),amp);
     Serial.println("Key down : "+keys[i][o]+" - ");
     Serial.print(selectMuxPinX(o));
        Serial.println("");
    }
    
     
   
   
   oldState[i][o] = true;
   } else{
    
    state[i][o] = false;
    if(oldState[i][o]!=state[i][o]&&oldState[i][o]==true){
      Serial.println("Key up : "+keys[i][o]);
     Serial.print(selectMuxPinX(o));
        Serial.println("");
      noteOff(1,24+keys[i][o].toInt(),amp);
    }
    oldState[i][o] = false;
   
   }
   
   
   

      
      WriteMuxPinY(i,0);
    
    }

  }
  
 // 


 
    
   

}










void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush(); 
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush(); 
}
