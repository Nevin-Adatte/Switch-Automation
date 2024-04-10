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
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLjOtKHtIN"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "7N5w7p9EKaRyohKFI-99TTzPZ40kxUdR"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "7N5w7p9EKaRyohKFI-99TTzPZ40kxUdR";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Anaa";
char pass[] = "crazy@ar";

#define light1 2
#define light2 4
#define sw1 25
#define sw2 26

int f1=0;
int f2=0;

BLYNK_WRITE(V0)
{
  int a1=param.asInt();
  digitalWrite(light1,a1);
}
BLYNK_WRITE(V1)
{
  int b1=param.asInt();
  digitalWrite(light2,b1);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(light1,OUTPUT);
  pinMode(light2,OUTPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  switches();
}

void switches()
{
  if((digitalRead(sw1)==0)&&(f1==0))
  {
    digitalWrite(light1,1);
    Blynk.virtualWrite(V0,1);
    f1=1;
  }
  else if((digitalRead(sw1)==1)&&(f1==1))
  {
    digitalWrite(light1,0);
    Blynk.virtualWrite(V0,0);
    f1=0;
  }
   else if((digitalRead(sw2)==0)&&(f2==0))
  {
    digitalWrite(light2,1);
    Blynk.virtualWrite(V1,1);
    f2=1;
  }
  else if((digitalRead(sw2)==1)&&(f2==1))
  {
    digitalWrite(light2,0);
    Blynk.virtualWrite(V1,0);
    f2=0;
  }
}
