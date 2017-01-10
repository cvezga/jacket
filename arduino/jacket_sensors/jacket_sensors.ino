//#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

//WiFi values for Home CR
char ssid[] = "dd-wrt_vap";              //  your network SSID (name)
char pass[] = "mmepcbgad27f";            // your network password (use for WPA, or use as key for WEP)
IPAddress broadcastIp(192, 168, 1, 255); //net ip address
unsigned int localPort = 2390;           // local port to listen on

//WiFi values for University Vienna
//char ssid[] = "dd-wrt_vap";              //  your network SSID (name)
//char pass[] = "mmepcbgad27f";            // your network password (use for WPA, or use as key for WEP)
//IPAddress broadcastIp(10, 168, 1, 255); //net ip address
//unsigned int localPort = 2390;           // local port to listen on

boolean outputToSerial = false; //switch to send messages to serial console; no serial output will be done if value is set to false
const int delayValue   = 100;   // loop wait value

// these constants won't change:
const int ledPin = 6;    // on baord LED connected to digital pin 6 (MKR1000)
int ledState     = LOW;  // variable used to store the last LED status, to toggle the light
int ledCount     = 0;    // counter to control LED ON/OFF speed

//sensors values
int sensorReading1 = 0;      // variable to store the value read from the sensor pin1 
int sensorReading2 = 0;      // variable to store the value read from the sensor pin2
int sensorReading3 = 0;      // variable to store the value read from the sensor pin3
int sensorReading4 = 0;      // variable to store the value read from the sensor pin4
int sensorReading5 = 0;      // variable to store the value read from the sensor pin5
int sensorReading6 = 0;      // variable to store the value read from the sensor pin6

//all sensor values as string
String data = "00000,00000,00000,00000,00000,00000;";
char  ReplyBuffer[30];       // buffer to send data to wifi
WiFiUDP Udp;

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  initSerial();
  checkWiFiShield();
  connectToWiFi();
  Udp.begin(localPort);
}

void loop() {

  readSensors();
  printSensorValuesToSerial();
  toggleLedState();
  prepareBufferData();
  sendData();    
  
  delay(delayValue);  // delay to avoid overloading the serial port buffer

}

//Serial communitacion will only be initialiced if outputToSerial = true
void  initSerial(){
  if(outputToSerial){
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Jacket Sensors - Ver. 1.0");
  }
}

void  checkWiFiShield(){
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    if(outputToSerial) Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
}

void connectToWiFi(){
  int status = WL_IDLE_STATUS;
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    if(outputToSerial){
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
    }
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid,pass);
    // wait 5 seconds for connection:
    delay(5000);
  }
  if(outputToSerial){
     Serial.println("Connected to wifi");
     printWifiStatus();
  }
}

void printWifiStatus() {
  if(outputToSerial){
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
  
    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
  
    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
  }
}

void readSensors() {
  sensorReading1 = analogRead(A1);
  sensorReading2 = analogRead(A2);
  sensorReading3 = analogRead(A3);
  sensorReading4 = analogRead(A4);
  sensorReading5 = analogRead(A5);
  sensorReading6 = analogRead(A6);
}

void  printSensorValuesToSerial(){
  if(outputToSerial){
    Serial.print(sensorReading1);
    Serial.print(",");
    Serial.print(sensorReading2);
    Serial.print(",");
    Serial.print(sensorReading3);
    Serial.print(",");
    Serial.print(sensorReading4);
    Serial.print(",");
    Serial.print(sensorReading5);
    Serial.print(",");
    Serial.println(sensorReading6);
  }
}

void  toggleLedState(){

    ledCount = ledCount + 1;

    if(ledCount > 10){
      //init ledCount back to zero
      ledCount=0;
      //change led state
      ledState = !ledState;
      // update the LED pin itself:
      digitalWrite(ledPin, ledState);
    }
    
}

 void prepareBufferData(){

    //Prepare string to send to wifi
    data = String(sensorReading1)+","
          +String(sensorReading1)+","
          +String(sensorReading1)+","
          +String(sensorReading1)+","
          +String(sensorReading1)+","
          +String(sensorReading1)+";";
 }

 void sendData(){ 
    if(outputToSerial) Serial.println("Sending to WiFi: "+data);
    data.toCharArray(ReplyBuffer, data.length()+1);
    
    Udp.beginPacket(broadcastIp, localPort);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
 }


