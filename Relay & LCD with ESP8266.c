//Tutorial https://sites.google.com/site/kyrosprojects/
#include <ESP8266WiFi.h>
#include <Wire.h> // i2C Conection Library
#include <LiquidCrystal_I2C.h> //i2C LCD Library
//Gunakan define dibawah ini untuk jenis Relay Module LOW ACTIVE
#define ON 0
#define OFF 1
// Set the LCD address to 0x27 for a 16 chars and 2 line display
//pastikan i2C Address LCD anda sesuai dengan yang ditulis di sketch
LiquidCrystal_I2C lcd(0x27, 16, 2);
const char* ssid = "Wifi-Repeater"; //<-Ganti dengan nama jaringan wifi anda
const char* password = "f1b22a7ca0"; //<- Ganti dengan password wifi anda
//Wiring Relay ke module Nodemcu
const int LED1 = 15; //D8 on ESP Board
const int LED2 = 13; //D7 on ESP Board
const int LED3 = 12; //D6 on ESP Board
const int LED4 = 14; //D5 on ESP Board
bool value1 = LOW;
bool value2 = LOW;
bool value3 = LOW;
bool value4 = LOW;
WiFiServer server(80); // Wifi PORT
int delayLCD = 750; // delay pergantian text pada LCD 1602 (mS)
void setup() {
Serial.begin(115200);
// initialize the LCD
Wire.begin(2, 0);
lcd.init(); // initializing the LCD
lcd.backlight();
lcd.setCursor(0,0);
lcd.print(" Welcome! ");
delay (delayLCD);
pinMode(LED1, OUTPUT); digitalWrite(LED1, HIGH);
pinMode(LED2, OUTPUT); digitalWrite(LED2, HIGH);
pinMode(LED3, OUTPUT); digitalWrite(LED3, HIGH);
pinMode(LED4, OUTPUT); digitalWrite(LED4, HIGH);
// Connect to WiFi network
Serial.println("");
lcd.clear();
Serial.print("Connecting to ");
Serial.println(ssid);
lcd.setCursor (0,0);
lcd.print ("Connecting to...");
lcd.setCursor (0,1);
lcd.print (ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
lcd.print (".");
}
Serial.println("");
Serial.println("WiFi connected");
lcd.clear();
lcd.setCursor (0,0);
lcd.print (" WiFi connected ");
// Start the server
server.begin();
Serial.println("Server started");
lcd.setCursor (0,1);
lcd.print (" Server started ");
delay (2000);
// Print the IP address
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
lcd.clear();
lcd.setCursor (0,0);
lcd.print ("ESP8266 URL ADRS");
lcd.setCursor (0,1);
lcd.print (WiFi.localIP());
delay (2000);
}
void loop() {
// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
//lcd.clear();
lcd.setCursor (0,0);
lcd.print ("ESP8266 ");
lcd.setCursor (0,1);
lcd.print (WiFi.localIP());
lcd.print (" ");
return;
}
// Wait until the client sends some data
Serial.println("new client");
lcd.clear();
lcd.setCursor (0,0);
lcd.print ("Client Send Data");
while(!client.available()){
delay(1);
}
// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
lcd.setCursor (0,1);
lcd.print (request);
delay(1000);
client.flush();
// Set LED according to the request
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<fieldset>");
client.println("<font color = redq>");
client.print("Control 4 LED Via Wifi");
client.println("</font>");
client.println("</fieldset>");
client.println("<br><br>");
//Program Here
// Return the response LED1
//client.print("LED1 is now: ");
// Control LED 1
if (request.indexOf("/status1=1") != -1) {
digitalWrite(LED1, ON);
value1 = HIGH;
lcd.setCursor(0,0);
lcd.print("LED1 set to ON ");
lcd.setCursor(0,1);
lcd.print("by Client Reques");
delay (delayLCD);
}
if (request.indexOf("/status1=0") != -1) {
digitalWrite(LED1, OFF);
value1 = LOW;
lcd.setCursor(0,0);
lcd.print("LED1 set to OFF ");
lcd.setCursor(0,1);
lcd.print("by Client Reques");
delay (delayLCD);
}
if(value1==HIGH){
client.println("<br><br>");
client.print("status1=1");
}
if(value1==LOW){
client.println("<br><br>");
client.print("status1=0");
}
//client.println("<br><br>");
//client.println("<a href=\"/LED1=ON\"\"><button>LED1 ON </button></a>");
//client.println("<a href=\"/LED1=OFF\"\"><button>LED1 OFF </button></a><br />");
//client.println("</html>");
// Return the response LED2
//client.println("<br><br>");
//client.print("LED2 is now: ");
// Control LED 2
if (request.indexOf("/status2=1") != -1) {
digitalWrite(LED2, ON);
value2 = HIGH;
lcd.setCursor(0,0);
lcd.print("LED2 set to ON ");
lcd.setCursor(0,1);
lcd.print("by Client Reques");
delay (delayLCD);
}
if (request.indexOf("/status2=0") != -1) {
digitalWrite(LED2, OFF);
value2 = LOW;
lcd.setCursor(0,0);
lcd.print("LED2 set to OFF ");
lcd.setCursor(0,1);
lcd.print("by Client Reques");
delay (delayLCD);
}
if(value2==HIGH){
client.println("<br><br>");
client.print("status2=1");
}
if(value2==LOW){
client.println("<br><br>");
client.print("status2=0");
}
//client.println("<br><br>");
//client.println("<a href=\"/LED2=ON\"\"><button>LED2 ON </button></a>");
//client.println("<a href=\"/LED2=OFF\"\"><button>LED2 OFF </button></a><br />");
//client.println("</html>");
// Return the response LED3
//client.println("<br><br>");
//client.print("LED3 is now: ");
// Control LED 3
if (request.indexOf("/status3=1") != -1) {
digitalWrite(LED3, ON);
value3 = HIGH;
lcd.setCursor(0,0);
lcd.print("LED3 set to ON ");
lcd.setCursor(0,1);
lcd.print("by Client Reques");
delay (delayLCD);
}
if (request.indexOf("/status3=0") != -1) {
digitalWrite(LED3, OFF);
value3 = LOW;
lcd.setCursor(0,0);
lcd.println("LED3 set to OFF ");
lcd.setCursor(0,1);
lcd.println("by Client Reques");
delay (delayLCD);
}
if(value3==LOW){
client.println("<br><br>");
client.print("status3=1");
}
if(value3==HIGH){
client.println("<br><br>");
client.print("status3=0");
}
//client.println("<br><br>");
//client.println("<a href=\"/LED3=ON\"\"><button>LED3 ON </button></a>");
//client.println("<a href=\"/LED3=OFF\"\"><button>LED3 OFF </button></a><br />");
//client.println("</html>");
// Return the response LED4
//client.println("<br><br>");
//client.print("LED4 is now: ");
// Control LED 4
if (request.indexOf("/status4=1") != -1) {
digitalWrite(LED4, ON);
value4 = HIGH;
lcd.setCursor(0,0);
lcd.print("LED4 set to ON ");
lcd.setCursor(0,1);
lcd.print("by Client Reques");
delay (delayLCD);
}
if (request.indexOf("/status4=0") != -1) {
digitalWrite(LED4, OFF);
value4 = LOW;
lcd.setCursor(0,0);
lcd.print("LED4 set to OFF ");
lcd.setCursor(0,1);
lcd.print("by Client Reques");
delay (delayLCD);
}
if(value4==LOW){
client.println("<br><br>");
client.print("status4=1");
}
if(value4==HIGH){
client.println("<br><br>");
client.print("status4=0");
}
//client.println("<br><br>");
//client.println("<a href=\"/LED4=ON\"\"><button>LED4 ON </button></a>");
//client.println("<a href=\"/LED4=OFF\"\"><button>LED4 OFF </button></a><br />");
//client.println("</html>");
delay(1);
Serial.println("Client disonnected");
Serial.println("");
lcd.setCursor(0,1);
lcd.print("Client Disconect");
delay(1000);
}