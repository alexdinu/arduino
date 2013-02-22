/*
*******************************************************************************************
****                     Real Time Clock DS1307                                        ****
****                                                                                   ****
*******************************************************************************************
*/



#include <Wire.h>

#define RTCI2C 0x68

int status = NULL;

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}
//Set data to DS1307

void DataSet()
{
   Wire.beginTransmission(RTCI2C);//se initiaza conexiunea I2C catre modul RTC gasit la adresa 0x68
   Wire.write(0x00); //selectam adresa registrului de memorie la care vom scrie data si ora
   Wire.write(0);
   Wire.write(decToBcd(20));
   Wire.write(decToBcd(13));
   status = Wire.endTransmission();
   Serial.println("Operatia de pornire a ceasului si de setare a orei a returnat codul:"+status);
   
   
   Wire.beginTransmission(RTCI2C);//se initiaza conexiunea I2C catre modul RTC gasit la adresa 0x68
   Wire.write(0x04); //selectam adresa registrului de memorie la care vom scrie data si ora
   Wire.write(decToBcd(22));
   Wire.write(decToBcd(02));
   Wire.write(decToBcd(2013));
   status=Wire.endTransmission();
   Serial.println("Operatia de setare a datei a returnat codul:"+status);
   
}


void setup()
{
  
}


void loop()
{
  
}
