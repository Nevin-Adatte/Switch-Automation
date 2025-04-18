#include "DHT.h"

/***************************************************
  This is an example sketch for our optical Fingerprint sensor

  Designed specifically to work with the Adafruit BMP085 Breakout
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_Fingerprint.h>

#define BLYNK_TEMPLATE_ID "TMPL3iizWE4GC"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "7tgFPmN33WqxR2SE_j9i8qgOh6pKQpru"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Nevin";
char pass[] = "11111111";

BlynkTimer timer;

#define t1 25
#define t2 26
#define f1 27
#define f2 14
#define lock 2

#define t1in 35
#define t2in 34
#define f1in 33
#define f2in 32

#define DHTPIN 15
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int MODE=0;
int flag1=0;
int flag2=0;
int flag3=0;
int flag4=0;


BLYNK_WRITE(V1)
{
  int a1=param.asInt();
  digitalWrite(t1,!a1);
}
BLYNK_WRITE(V2)
{
  int a2=param.asInt();
  digitalWrite(t2,!a2);
}
BLYNK_WRITE(V3)
{
  int a3=param.asInt();
  digitalWrite(f1,!a3);
}
BLYNK_WRITE(V4)
{
  int a4=param.asInt();
  digitalWrite(f2,!a4);
}
BLYNK_WRITE(V5)
{
  int a5=param.asInt();
  digitalWrite(lock,!a5);
}


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial2

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  digitalWrite(2,0);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


   pinMode(t1,OUTPUT);
   pinMode(t2,OUTPUT);
   pinMode(f1,OUTPUT);
   pinMode(f2,OUTPUT);
   pinMode(lock,OUTPUT);

   digitalWrite(t1,1);
   digitalWrite(t2,1);
   digitalWrite(f1,1);
   digitalWrite(f2,1);
   digitalWrite(lock,1);

   Blynk.virtualWrite(V1,0);
   Blynk.virtualWrite(V2,0);
   Blynk.virtualWrite(V3,0);
   Blynk.virtualWrite(V4,0);
   Blynk.virtualWrite(V5,0);
   

   pinMode(t1in,INPUT_PULLDOWN);
   pinMode(t2in,INPUT_PULLDOWN);
   pinMode(f1in,INPUT_PULLDOWN);
   pinMode(f2in,INPUT_PULLDOWN);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }

   dht.begin();

   timer.setInterval(3000L,checkblynk);
   timer.setInterval(5000L,temper);
}

void loop()                     // run over and over again
{
  Blynk.run();
  timer.run();

   if(MODE==0)
   {
    internet();
   }
   else
   {
    no_internet();
   }
  
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

void checkblynk()
{
   bool isconnected = Blynk.connected();
  if (isconnected == false)
  {
    MODE = 1;
    WiFi.reconnect();
  }
  if (isconnected == true)
  {
    MODE = 0;
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    digitalWrite(2,!(digitalRead(2)));
    Blynk.virtualWrite(V5,!(digitalRead(2)));
    delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}

void internet()
{
   if((digitalRead(t1in))==LOW)
  {
    if(flag1==1)
    {
      digitalWrite(t1,HIGH);
      Blynk.virtualWrite(V1,1);
      flag1=0;
    }
  }
  if((digitalRead(t1in))==HIGH)
  {
    if(flag1==0)
    {
      digitalWrite(t1,LOW);
      Blynk.virtualWrite(V1,0);
      flag1=1;
    }
  }

   if((digitalRead(t2in))==LOW)
  {
    if(flag2==1)
    {
      digitalWrite(t2,HIGH);
      Blynk.virtualWrite(V2,1);
      flag2=0;
    }
  }
  if((digitalRead(t2in))==HIGH)
  {
    if(flag2==0)
    {
      digitalWrite(t2,LOW);
      Blynk.virtualWrite(V2,0);
      flag2=1;
    }
  }

   if((digitalRead(f1in))==LOW)
  {
    if(flag3==1)
    {
      digitalWrite(f1,HIGH);
      Blynk.virtualWrite(V3,1);
      flag3=0;
    }
  }
  if((digitalRead(f1in))==HIGH)
  {
    if(flag3==0)
    {
      digitalWrite(f1,LOW);
      Blynk.virtualWrite(V3,0);
      flag3=1;
    }
  }

   if((digitalRead(f2in))==LOW)
  {
    if(flag4==1)
    {
      digitalWrite(f2,HIGH);
      Blynk.virtualWrite(V4,1);
      flag4=0;
    }
  }
  if((digitalRead(f2in))==HIGH)
  {
    if(flag4==0)
    {
      digitalWrite(f2,LOW);
      Blynk.virtualWrite(V4,0);
      flag4=1;
    }
  }
}

void no_internet()
{
  digitalWrite(t1,!digitalRead(t1in));
  digitalWrite(t2,!digitalRead(t2in));
  digitalWrite(f1,!digitalRead(f1in));
  digitalWrite(f2,!digitalRead(f2in));
}


void temper()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V9, h);
  Blynk.virtualWrite(V10, t);
}
