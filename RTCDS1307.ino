/*
*******************************************************************************************
****                     Real Time Clock DS1307                                        ****
****                                                                                   ****
*******************************************************************************************
*/



#include <Wire.h>

#define RTCI2C 0x68
int ledPin = 13;
int status = NULL;
byte minute, hour, day, month, year;

// Convert normal DECimal numbers to binary coded DECimal
byte DECToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
// Convert binary coded DECimal to normal DECimal numbers
byte bcdToDEC(byte val)
{
  return ( (val/16*10) + (val%16) );
}
//Set data to DS1307

void ledFlash(int nrFlash)
{
 for (int i=0; i<=nrFlash; i++)
    {
     digitalWrite(ledPin, HIGH);
     delay(500);
     digitalWrite(ledPin,LOW);
     delay(500);
    }
}
void dateSet()
{
   Wire.beginTransmission(RTCI2C);//se initiaza conexiunea I2C catre modul RTC gasit la adresa 0x68
   Wire.write(0x00); //selectam adresa registrului de memorie la care vom scrie data si ora
   Wire.write(0);
   Wire.write(DECToBcd(20));
   Wire.write(DECToBcd(15));
   status = Wire.endTransmission();
   Serial.print("Operatia de pornire a ceasului si de setare a orei a returnat codul:");
   Serial.println(status);
   ledFlash(5);
   
   Wire.beginTransmission(RTCI2C);//se initiaza conexiunea I2C catre modul RTC gasit la adresa 0x68
   Wire.write(0x04); //selectam adresa registrului de memorie la care vom scrie data si ora
   Wire.write(DECToBcd(22));
   Wire.write(DECToBcd(02));
   Wire.write(DECToBcd(2013));
   status=Wire.endTransmission();
   Serial.print("Operatia de setare a datei a returnat codul:");
   Serial.println(status);
   ledFlash(10);
}

void dateRead()
{
  Wire.beginTransmission(RTCI2C);
  Wire.write(0x01);
  status=Wire.endTransmission();
  Serial.print("Operatia de setare a registrului de citire a orei a returnat codul:");
  Serial.println(status);
  ledFlash(5);
  Wire.requestFrom(RTCI2C,2);
  minute = bcdToDEC(Wire.read());
  hour = bcdToDEC(Wire.read() & 0x3f);
  
  status=Wire.endTransmission();
  Serial.print("Operatia de citire a orei a returnat codul:");
  Serial.println(status);
  
  Wire.beginTransmission(RTCI2C);
  Wire.write(0x04);
  status=Wire.endTransmission();
  Serial.print("Operatia de setare a registrului de citire a datei a returnat codul:");
  Serial.println(status);
  ledFlash(5);
  Wire.requestFrom(RTCI2C,3);
  day = bcdToDEC(Wire.read());
  month = bcdToDEC(Wire.read());
  year = bcdToDEC(Wire.read());
  
  status=Wire.endTransmission();
  Serial.print("Operatia de citire a datei a returnat codul:");
  Serial.println(status);
  ledFlash(10);
  Serial.print(hour,DEC);
  Serial.print(":");
  Serial.print(minute,DEC);
  Serial.print(";");
  Serial.print(day,DEC);
  Serial.print("-");
  Serial.print(month,DEC);
  Serial.print("-");
  Serial.print("20");
  if (year < 10)
    Serial.print("0");
  Serial.println(year, DEC);
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  dateSet();
  pinMode(ledPin, OUTPUT);
}


void loop()
{
  dateRead();
  delay(10000);
}
