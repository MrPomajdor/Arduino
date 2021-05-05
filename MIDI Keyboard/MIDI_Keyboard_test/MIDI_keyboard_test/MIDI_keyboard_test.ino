#include <MIDIUSB.h>
#include <Keypad.h>
const byte ROWS = 7;
const byte COLS = 7;

byte colPins[COLS] = {0,1,2,3,4,5,6};

byte rowPins[ROWS] = {7,8,9,10,11,12,13};

const String keys[ROWS][COLS] = {
{"0","1","2","3","4","5","6"},
{"7","8","9","10","11","12","13"},
{"14","15","16","17","18","19","20"},
{"21","22","23","24","25","26","27"},
{"28","29","30","31","32","33","34"},
{"35","36","37","38","39","40","41"},
{"42","43","44","45","46","47","48"},
};
bool oldState[ROWS][COLS];
bool state[ROWS][COLS];
void setup() {
pinMode(A0,OUTPUT);
  pinMode(A1,INPUT_PULLUP);
analogWrite(A0,HIGH);
Serial.begin(9600);
}

bool s;

void loop() {

Serial.println(analogRead(A1));
if(analogRead(A1)<50){
  if(s==false){
  noteOn(1,10+keys[2][3].toInt(),64);
  s=true;
  }
}else{
  if(s==true){
    noteOff(1,10+keys[2][3].toInt(),64);
    s=false;
  }
}
  
   
   


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
