#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(3,1);

//TX RX como serial.
//LEMBRAR DE LIGAR OS TERRAS JUNTOS.

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "EBzOKyeWePRCay5fP8tY-eMnQVQmY0x5";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "motorolaone";
char pass[] = "batata12";
WidgetLCD lcd(V10);
int value;
String PotFase1;
String PotFase2;
String PotFase3;
int Pot1;
int Pot2;
int Pot3;
int i1;
int i2;
int i3;
int v1;
int v2;
int v3;
int FP1;
int FP2;
int FP3;
int Energia;
float Preco;
int PotAux;
char serialRead;
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

  
void myTimerEvent()
{ 

 
  Blynk.virtualWrite(V1,Pot1);
  delay(50);
  Blynk.virtualWrite(V2,Pot2);
  delay(50);
  Blynk.virtualWrite(V3,Pot3);
  delay(50);
  Blynk.virtualWrite(V4,v1);
  delay(50);
  Blynk.virtualWrite(V5,i1);
  delay(50);
  Blynk.virtualWrite(V6,v2);
  delay(50);
  Blynk.virtualWrite(V7,i2);
  delay(50);
  Blynk.virtualWrite(V8,v3);
  delay(80);
  Blynk.virtualWrite(V9,i3);
  delay(50);
  Blynk.virtualWrite(V10,FP1);
  delay(50);
  Blynk.virtualWrite(V11,FP2);
  delay(50);
  Blynk.virtualWrite(V12,FP3);
  delay(50);
  
  
  
  
  

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, myTimerEvent);
}

void loop()
{ 
  s.write("s");
  if (s.available()>0)
  {
   serialRead = s.read();
   if (serialRead == 'A'){
      s.write("s");
     if (s.available()>0){
     PotAux=s.read();
     if(PotAux>=0){
      Pot1=PotAux;}}
      s.write("s");
      if (s.available()>0){
      PotAux=s.read();
      if(PotAux>=0){
      Pot1=100*PotAux+Pot1;}}
   }
   if (serialRead == 'B'){
      s.write("s");
     if (s.available()>0){
     PotAux=s.read();
     if(PotAux>=0){
      Pot2=PotAux;}}
      s.write("s");
      if (s.available()>0){
      PotAux=s.read();
      if(PotAux>=0){
      Pot2=100*PotAux+Pot2;}}
   }

   if (serialRead == 'C'){
      s.write("s");
      if (s.available()>0){
      PotAux=s.read();
     if(PotAux>=0){
      Pot3=PotAux;}}
      s.write("s");
      if (s.available()>0){
      PotAux=s.read();
      if(PotAux>=0){
      Pot3=100*PotAux+Pot3;}}
   }
   
   if (serialRead == 'D'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      i1=PotAux;}
   }

  if (serialRead == 'E'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      v1=PotAux;}
   }

   if (serialRead == 'F'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      i2=PotAux;}
   }

   if (serialRead == 'G'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      v2=PotAux;}
   }


   if (serialRead == 'H'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      i3=PotAux;}
   }

   if (serialRead == 'I'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      v3=PotAux;}
   }
   
   if (serialRead == 'J'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      Energia=PotAux;}
   }

   if (serialRead == 'K'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      FP1=PotAux;}
   }
   
   if (serialRead == 'L'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      FP2=PotAux;}
   }

   if (serialRead == 'M'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>=0){
      FP3=PotAux;}
   }
   
  }
  
 

  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
