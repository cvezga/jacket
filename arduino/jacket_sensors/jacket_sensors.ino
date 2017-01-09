#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
char ssid[] = "dd-wrt_vap"; //  your network SSID (name)
char pass[] = "mmepcbgad27f";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;       // your network key Index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[30];       // a string to send back

WiFiUDP Udp;

IPAddress broadcastIp(192, 168, 255, 255);

// these constants won't change:
const int ledPin = 6;   // led connected to digital pin 6 (MKR1000)

//Piezo Sensors
const int sensor1 = A1; // the piezo is connected to analog pin A1
const int sensor2 = A2; // the piezo is connected to analog pin A2
const int sensor3 = A3; // the piezo is connected to analog pin A3
const int sensor4 = A4; // the piezo is connected to analog pin A4
const int sensor5 = A5; // the piezo is connected to analog pin A5
const int sensor6 = A6; // the piezo is connected to analog pin A6

const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not
const int delayValue = 100;  // loop wait value


// these variables will change:
int sensorReading1 = 0;      // variable to store the value read from the sensor pin
int sensorReading2 = 0;      // variable to store the value read from the sensor pin
int sensorReading3 = 0;      // variable to store the value read from the sensor pin
int sensorReading4 = 0;      // variable to store the value read from the sensor pin
int sensorReading5 = 0;      // variable to store the value read from the sensor pin
int sensorReading6 = 0;      // variable to store the value read from the sensor pin

String s1 = "00000";
String s2 = "00000";
String s3 = "00000";
String s4 = "00000";
String s5 = "00000";
String s6 = "00000";

String data = "00000,00000,00000,00000,00000,00000";

int ledState = LOW;         // variable used to store the last LED status, to toggle the light



void setup() {
  initSerial();
 
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT

  checkWiFiShield();

  connectToWiFi();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
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

void  initSerial(){
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void  checkWiFiShield(){
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
}

void connectToWiFi(){

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid,pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

}

void printWifiStatus() {
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

void readSensors() {

  sensorReading1 = analogRead(sensor1);
  sensorReading2 = analogRead(sensor2);
  sensorReading3 = analogRead(sensor3);
  sensorReading4 = analogRead(sensor4);
  sensorReading5 = analogRead(sensor5);
  sensorReading6 = analogRead(sensor6);
}

void  printSensorValuesToSerial(){
  
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

void  toggleLedState(){
  
    //change led state
    ledState = !ledState;
    // update the LED pin itself:
    digitalWrite(ledPin, ledState);

}

 void prepareBufferData(){

    //Prepare string to send to wifi
    s1 =  String(sensorReading1);
    s2 =  String(sensorReading2);
    s3 =  String(sensorReading3);
    s4 =  String(sensorReading4);
    s5 =  String(sensorReading5);
    s6 =  String(sensorReading6);

    data = s1+","+s2+","+s3+","+s4+","+s5+","+s6;

    data.toCharArray(ReplyBuffer, data.length());

 }

 void sendData(){ 
    Udp.beginPacket(broadcastIp, localPort);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
 }

