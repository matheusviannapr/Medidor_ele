#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(3,1);

//USAR SERIALNORMAL E VER O QUE ACONTECE.
//LEMBRAR DE LIGAR OS TERRAS JUNTOS.

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "EBzOKyeWePRCay5fP8tY-eMnQVQmY0x5";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "motorolaone";
char pass[] = "batata12";
int value;
String PotFase1;
String PotFase2;
String PotFase3;
int Pot1;
int Pot2;
int Pot3;
int PotAux;
char serialRead;
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

  
void myTimerEvent()
{ 

 
  Blynk.virtualWrite(V1,Pot1);
  delay(100);
  Blynk.virtualWrite(V2,Pot2);
  delay(100);
  Blynk.virtualWrite(V3,Pot3);
  
  

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
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{ 
  s.write("s");
  if (s.available()>0)
  {
   serialRead = s.read();
   if (serialRead == 'A'){
      s.write("s");
     PotAux=s.read();
     if(PotAux>0){
      Pot1=PotAux;}
   }
   if (serialRead == 'B'){
      s.write("s");
     PotAux=s.read();
     if(PotAux>0){
      Pot2=PotAux;}
   }

   if (serialRead == 'C'){
      s.write("s");
      PotAux=s.read();
     if(PotAux>0){
      Pot3=PotAux;}
   }
  }
  
 

  
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
