#include <SPI.h>
#include <WiFiNINA.h>

//This is for the Metro Card, don't change and don't use these pins
#define SPIWIFI       SPI  // The SPI port
#define SPIWIFI_SS    13   // Chip select pin
#define ESP32_RESETN  12   // Reset pin
#define SPIWIFI_ACK   11   // a.k.a BUSY or READY pin
#define ESP32_GPIO0   -1


#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

int PulseSensorPurplePin = 0; 
int Signal; 

//MAKE SURE THE arduino_secrets.h file contains the wifi ID and the password like in the previous tests in the tutorial doc
//Keep in mind that you need a simple router to do this, DREXEL network will not let you in

//////////////////////////////////////
IPAddress destIp(192, 168, 2, 2); // destination IP address (check in CMD with ipconfig/all what the IP of the computer is
int destPort = 7005; // destinatin Port, make sure Touchdesigner UDP in is set to this!
//////////////////////////////////////

unsigned int localPort = 7006;      // this is the local port of the board, not to be used for sending

WiFiUDP Udp;

  
void setup() 
{
  WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);
  
  while (status != WL_CONNECTED) 
  {
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }
  
  Udp.begin(localPort);
}

void loop() 
{
    Signal = analogRead(PulseSensorPurplePin);  
    Udp.beginPacket(destIp, destPort);
    Udp.print(Signal);
    Udp.endPacket();
}
