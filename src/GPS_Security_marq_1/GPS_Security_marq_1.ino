#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial sms(7, 8);
SoftwareSerial serial_connection(10, 11);
TinyGPSPlus gps;


void setup()
{

  sms.begin(9600);
  serial_connection.begin(9600);
  Serial.begin(9600);
  
  sms.println("AT+CMGF=1");
  
  delay(500);
}

void loop()
{
while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
  sms.println("AT+CMGS=\"09501809905\"");
delay (500);
   sms.println("Latitude:");
    sms.println(gps.location.lat(), 6);
   sms.println("Longitude:");
    sms.println(gps.location.lng(), 6);
      delay(10000);
      sms.write( 0x1a ); // ctrl+Z character
  
  delay(500);
    }
}

  

  
