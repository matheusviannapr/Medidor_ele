/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  NOTE:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  App project setup:
    Value Display widget attached to Virtual Pin V5
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "EBzOKyeWePRCay5fP8tY-eMnQVQmY0x5";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "motorolaone";
char pass[] = "batata12";
int value;
float PotFase1;
float PotFase2;
float PotFase3;
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

  
void myTimerEvent()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  PotFase1=root["PotFase1"];
  PotFase2=root["PotFase2"];
  PotFase3=root["PotFase3"];
  
  Blynk.virtualWrite(V1,PotFase1);
  Blynk.virtualWrite(V2,PotFase1);
  Blynk.virtualWrite(V3,PotFase1);
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  s.begin(9600);
  pinMode(A0,INPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
