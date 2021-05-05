
unsigned long startMillis; 
unsigned long currentMillis;


unsigned long startMillis_rec; 
unsigned long currentMillis_rec;
const unsigned long period = 75000;
bool temp=true;
int recording[20];
bool te2,te3;
bool gugugaga=true;
int recN=0;
int n=0;
bool LedOn,LedToggle;
void setup() {
  Serial.begin(9600);
 pinMode(2,OUTPUT);
  
 pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
   pinMode(5,INPUT_PULLUP);  
   pinMode(6,OUTPUT);
   pinMode(7,OUTPUT);

Serial.println("Clearing recording");
     recording[0]=0;
      recording[1]=0;
      recording[2]=0;
      recording[3]=0;
      recording[4]=0;
      recording[5]=0;
      recording[6]=0;
      recording[7]=0;
      recording[8]=0;
      recording[9]=0;
      recording[10]=0;
      recording[11]=0;
      recording[12]=0;
      recording[13]=0;
      recording[14]=0;
      recording[15]=0;
      recording[16]=0;
      recording[17]=0;
      recording[18]=0;
      recording[19]=0;
      recording[20]=0;
}


void loop() {

if(LedOn){
      if(LedToggle){
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
      }else{
        
        digitalWrite(7,HIGH);
        digitalWrite(6,LOW);
      }
    }else{
      
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
    }


 if(digitalRead(4)==LOW){
  n=0;
    if(te2){
       Serial.println("Clearing recording");
      recording[0]=0;
      recording[1]=0;
      recording[2]=0;
      recording[3]=0;
      recording[4]=0;
      recording[5]=0;
      recording[6]=0;
      recording[7]=0;
      recording[8]=0;
      recording[9]=0;
      recording[10]=0;
      recording[11]=0;
      recording[12]=0;
      recording[13]=0;
      recording[14]=0;
      recording[15]=0;
      recording[16]=0;
      recording[17]=0;
      recording[18]=0;
      recording[19]=0;
      recording[20]=0;
      
      recN=0;
      te2=false;
      startMillis_rec=millis();
    }
    if(digitalRead(5)==LOW){
      if(te3){
              
        if(recN>19){
        return;
        }
        if(millis()-startMillis_rec!=0 && millis()-startMillis_rec>0 && millis()-startMillis_rec<3000 && millis()-startMillis_rec>10){
          recording[recN]=millis()-startMillis_rec;
        
      
      Serial.println(String(recN)+"  Adding : "+String(millis()-startMillis_rec));
      Serial.println("Return : "+String(recording[recN]));
      startMillis_rec=millis();
      recN++;
      
      te3=false;
      }
    }
    }else{
      te3=true;
    }
  }else{
    te2=true;
  }

 


  
 if(digitalRead(3)==LOW){
  if(temp){
    Serial.println("Resetting startMillis  "+String(temp));
    startMillis = millis();
    temp=false;
  }
  currentMillis=millis();
   Serial.println("Current : "+String(currentMillis)+"     Start : "+String(startMillis)+"    elapsed : "+String(currentMillis - startMillis));
  if(currentMillis - startMillis>=period){
  if(gugugaga){
    n=0;
    gugugaga=false;
  }
  LedOn=true;
    if(recording[n]!=0 && recording[n]>0 && recording[n]<3000 && recording[n]>10){
    
    
    Serial.println("Delay = "+String(recording[n]));
    LedToggle=!LedToggle;
    delay(recording[n]);
    
    
    tone(2,900,100);
    }else{
      Serial.println(String(n) +" With "+String(recording[n]));
      
    }
    n++;
    if(n>20){
      n=0;
    }
 }
 }else{
  LedOn=false;
  temp=true;
  gugugaga=true;
  n=0;
 }
 }
