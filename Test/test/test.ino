#include <ESP8266WiFi.h>

const char* nazwaWIFI = "CMCC-F5vr";
const char* haslo = "karolincia08";
WiFiServer serwer(80);
 
void setup() {
Serial.begin(9600);
delay(10);
 
pinMode(5,OUTPUT);

digitalWrite(5,HIGH);


Serial.print("Laczenie do: ");
Serial.println(nazwaWIFI);
 
WiFi.begin(nazwaWIFI, haslo);
while (WiFi.status() != WL_CONNECTED) {
delay(100);
Serial.print(".");
}
 

Serial.println("WiFi connected");
 

serwer.begin();
Serial.println("Server started");

Serial.print("Strona : ");
Serial.print("http://");
Serial.print(WiFi.localIP());

}
int stan=0;
void loop() {
  WiFiClient klient = serwer.available();
  if(!klient){
  return;
  }
  int t=0;
  Serial.println("Nowy klient");
  while(!klient.available()){
    delay(1);
    t+=1;
    if(t>5000){
      Serial.println("Timeout");
      klient.stop();
      return;
    }
    
    
  }

  String request=klient.readStringUntil('\r');
  Serial.println("Request : "+request);
  klient.flush();

  if(request.indexOf("/TONE=0")!=-1){
 tone(5,800,0.5);
 delay(100);
 noTone(5);
 stan=1;
  }
  if(request.indexOf("/TONE=1")!=-1){
 tone(5,950,0.5);
  delay(100);
 noTone(5);
 stan=2;
  }
  if(request.indexOf("/TONE=2")!=-1){
 tone(5,1100,0.5);
  delay(100);
 noTone(5);
 stan=3;
  }
  if(request.indexOf("/TONE=3")!=-1){
 tone(5,1250,0.5);
  delay(100);
 noTone(5);
 stan=4;
  }
  if(request.indexOf("/TONE=4")!=-1){
 tone(5,1400,0.5);
  delay(100);
 noTone(5);
 stan=5;
  }
  if(request.indexOf("/TONE=5")!=-1){
 tone(5,1550,0.5);
  delay(100);
 noTone(5);
 stan=6;
  }
  if(request.indexOf("/TONE=6")!=-1){
 tone(5,1700,0.5);
  delay(100);
 noTone(5);
 stan=7;
  }
  if(request.indexOf("/TONE=7")!=-1){
 tone(5,900,0.5);
  delay(100);
 noTone(5);
 stan=8;
  }
  digitalWrite(5,HIGH);
  
 klient.println("HTTP/1.1 200 OK");
klient.println("Content-Type: text/html");
klient.println(""); 
klient.println("");
klient.println("");
klient.println("");
klient.println("");
klient.println("");
klient.println("");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=0'\">---1---</button>");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=1'\">---2---</button>");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=2'\">---3---</button>");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=3'\">---4---</button>");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=4'\">---5---</button>");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=5'\">---6---</button>");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=6'\">---7---</button>");
klient.println("");
klient.println("");
klient.println("<button onclick=\"window.location.href='/TONE=7'\">---8---</button>");

delay(1);
  
 

}
