
// Include Software Serial library to communicate with GSM
#include <SoftwareSerial.h>

// Configure software serial port
SoftwareSerial sms(7, 8);

// Variable to store text message
String textMessage;

// Create a variable to store Lamp state
String lampState = "HIGH";

// Relay connected to pin 12
const int relay1 = 3;
const int relay2 = 4;
const int relay3 = 5;
void setup() {
  // Automatically turn on the shield
  
  
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

void loop(){
  if(sms.available()>0){
    textMessage = sms.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("ON")>=0){
    // Turn on relay and save current state
    digitalWrite(relay2, HIGH);
    lampState = "on";
    Serial.println("Relay set to ON");  
    textMessage = "";   
  }
  if(textMessage.indexOf("OFF")>=0){
    // Turn off relay and save current state
    digitalWrite(relay2, LOW);
    lampState = "off"; 
    Serial.println("Relay set to OFF");
    textMessage = ""; 
  }
 if(textMessage.indexOf("START")>=0){
    // Turn on relay and save current state
    digitalWrite(relay3, HIGH);
    delay(900);
    digitalWrite(relay3, LOW);
    textMessage = "";   
  }
   if(textMessage.indexOf("THEFT")>=0){
    // Turn on relay and save current state
    digitalWrite(relay1, HIGH);
    textMessage = "";   
  }
  if(textMessage.indexOf("STATE")>=0){
    String message = "Car is " + lampState;
    sendSMS(message);
    Serial.println("Car state resquest");
    textMessage = "";
  }
}  

// Function that sends SMS
void sendSMS(String message){
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
