// DS3232 I2C alarms test

#include "Wire.h"
#define DS3232_I2C_ADDRESS 0x68

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

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void readDS3232alarm1(byte *second, 
byte *minute, 
byte *hour, 
byte *dayOfMonth)
{
  Wire.beginTransmission(DS3232_I2C_ADDRESS);
  Wire.write(0x07); // set DS3232 register pointer to 07h
  Wire.endTransmission();  
  Wire.requestFrom(DS3232_I2C_ADDRESS, 4); // request 4 bytes of data from DS3232 starting from register 07h

  *second     = bcdToDec(Wire.read());
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f);
  *dayOfMonth = bcdToDec(Wire.read()) ;
}

void readDS3232alarm2(
byte *minute, 
byte *hour, 
byte *dayOfMonth)
{
  Wire.beginTransmission(DS3232_I2C_ADDRESS);
  Wire.write(0x0B); // set DS3232 register pointer to 07h
  Wire.endTransmission();  
  Wire.requestFrom(DS3232_I2C_ADDRESS, 3); // request 4 bytes of data from DS3232 starting from register 07h

  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f);
  *dayOfMonth = bcdToDec(Wire.read()) ;
}

void setDS3232alarm1(byte second, byte minute, byte hour, byte dayOfMonth)
// sets alarm 1 data
{
  Wire.beginTransmission(DS3232_I2C_ADDRESS);  
  Wire.write(0x07); 
  Wire.write(decToBcd(second));     // set seconds
  Wire.write(decToBcd(minute));     // set minutes
  Wire.write(decToBcd(hour));       // set hours
  Wire.write(decToBcd(dayOfMonth));  // set date of month
  Wire.endTransmission();
}

void setDS3232alarm2(byte minute, byte hour, byte dayOfMonth)
// sets alarm 1 data
{
  Wire.beginTransmission(DS3232_I2C_ADDRESS);  
  Wire.write(0x0B); 
  Wire.write(decToBcd(minute));     // set minutes
  Wire.write(decToBcd(hour));       // set hours
  Wire.write(decToBcd(dayOfMonth));  // set date of month
  Wire.endTransmission();
}

void displayAlarm1()
{
  byte second, minute, hour, dayOfMonth;
  
  // retrieve data from DS3232  
  readDS3232alarm1(&second, &minute, &hour, &dayOfMonth);
  
  // send it to the serial monitor
  Serial.print("Alarm One: ");
  Serial.print(hour, DEC);// convert the byte variable to a decimal number when being displayed
  Serial.print(":");
  if (minute<10)
  {
      Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
      Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print("  ");
  Serial.println(dayOfMonth, DEC);
}

void displayAlarm2()
{
  byte minute, hour, dayOfMonth;
  
  // retrieve data from DS3232  
  readDS3232alarm2(&minute, &hour, &dayOfMonth);
  
  // send it to the serial monitor
  Serial.print("Alarm Two ");
  Serial.print(hour, DEC);// convert the byte variable to a decimal number when being displayed
  Serial.print(":");
  if (minute<10)
  {
      Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print("  ");
  Serial.println(dayOfMonth, DEC);
}

void loop()
{
   // setDS3232alarm1(56, 34, 12, 31); // set alarm 1 seconds, minutes, hours, date
   // setDS3232alarm2(57, 17, 31); // set alarm 2 minutes, hours, date   
   
   displayAlarm1();
   displayAlarm2();
   
   delay(5000);
}

