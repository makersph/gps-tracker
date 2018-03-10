
// Include Software Serial library to communicate with GSM
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// GPS AREA
SoftwareSerial sms(7, 8);
SoftwareSerial serial_connection(10, 11);
TinyGPSPlus gps;
// GPS AREA END

// GSM AREA
// Variable to store text message
String textMessage;

// Create a variable to store Lamp state
String lampState = "HIGH";

// Relay connected to pin 12
const int relay1 = 3;
const int relay2 = 4;
const int relay3 = 5;
// GSM AREA END

void setup() {
  gpsSetup(); // INITIALIZE GPS REQUIREMENTS
  gsmSetup(); // INITIALIZE GSM REQUIREMENTS
}

void loop(){
  getMessage(); // fetch message
  smsRules();
  delay(5000);
}

void gsmSetup() {  
  // Set relay as OUTPUT
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  // By default the relay is off

  // Initializing serial commmunication
  Serial.begin(19200); 
  sms.begin(19200);

  // Give time to your GSM shield log on to network
  delay(20000);
  Serial.print("sms ready...");

  // AT command to set sms to SMS mode
  sms.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  sms.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void gpsSetup()
{
  sms.begin(9600);
  serial_connection.begin(9600);
  Serial.begin(9600);
  
  sms.println("AT+CMGF=1");
  
  delay(500);
}

void getLoc() {
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    sms.println("AT+CMGS=\"09501809905\"");
    delay (500);
    sms.print("https://www.latlong.net/c/?lat=");
    sms.print(gps.location.lat(), 6);
    sms.print("&long=");
    sms.print(gps.location.lng(), 6);

    delay(10000);
    sms.write( 0x1a ); // ctrl+Z character
  
    delay(500);
  }
}

void getMessage() {
  if(sms.available()>0){
    textMessage = sms.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
}

void smsRules() {
  if(textMessage.indexOf("ON")>=0) {
    // Turn on relay and save current state
    digitalWrite(relay2, HIGH);
    lampState = "on";
    Serial.println("Relay set to ON");  
    textMessage = "";   
  }
  if(textMessage.indexOf("OFF")>=0) {
    // Turn off relay and save current state
    digitalWrite(relay2, LOW);
    lampState = "off"; 
    Serial.println("Relay set to OFF");
    textMessage = ""; 
  }
 if(textMessage.indexOf("START")>=0) {
    // Turn on relay and save current state
    digitalWrite(relay3, HIGH);
    delay(900);
    digitalWrite(relay3, LOW);
    textMessage = "";   
  }
   if(textMessage.indexOf("THEFT")>=0) {
    // Turn on relay and save current state
    digitalWrite(relay1, HIGH);
    textMessage = "";   
  }
  if(textMessage.indexOf("STATE")>=0) {
    String message = "Car is " + lampState;
    sendSMS(message);
    Serial.println("Car state resquest");
    textMessage = "";
  }
  if(textMessage.indexOf("FIND")>=0) {
    getLoc();
  }

}

// Function that sends SMS
void sendSMS(String message) {
  // AT command to set sms to SMS mode
  sms.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  sms.println("AT + CMGS = \"09501809905\""); 
  delay(100);
  // Send the SMS
  sms.println(message); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  sms.println((char)26); 
  delay(100);
  sms.println();
  // Give module time to send SMS
  delay(5000);  
}
