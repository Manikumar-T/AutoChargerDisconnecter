#include <Arduino.h>
//ESP3266WiFi module is used to access the Wifi
#include<ESP8266WiFi.h>
//WiFiUdp module is used to Create the udp server
#include<WiFiUdp.h>

#include<Servo.h>


bool isEqual(char value1[] , char value2[]);
//It's the SSID and Password of the wifi network i want to connect
#define SSID "Mani's Galaxy A71"
#define PASSWORD "        "

//Define the Port the server has to run
#define PORT 4210

//UDP object to access to initialize the udp server
WiFiUDP udp;


//char arrar of message to send to client
char replayPacket[] = "Hi i am esp8266 speaking ";

bool isEqual(char value1[] , char value2[]) {
 return std::strcmp(value1, value2) == 0;
}

void setup() {
  
  //Begin the Serial monitor
  Serial.begin(9600);
  Serial.print("ESP8266 is Started....\n");

  //Connect to the wifi network using the criedntials
  WiFi.begin(SSID,PASSWORD);

  //loop to check the connection status
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  }
  //To print the localIP of esp8266
  Serial.print("Connected, IP address:");
  Serial.print(WiFi.localIP());
  
  //Begin to listening 
  Serial.print("\nStart UDP server at port 4210");

  udp.begin(PORT);


  
}

void loop() {
  
  //char array to store the incoming packet
  char incomingPacket[1024];
  //Get the received packet size in byte
  int packetSize = udp.parsePacket();
  //If packet received
  if(packetSize) {
    //print the remote client ip and port 
    Serial.printf("\nPacket recevied %d bytes from %s, port %d \n",packetSize,udp.remoteIP().toString().c_str(),udp.remotePort());
    //read the data and stored it into incomingpacket char arrays and return the length of the message
    int len =udp.read(incomingPacket,1023);
    //Print the content is the packet
    Serial.printf("UDP packet contents: %s\n",incomingPacket);
    
    if (isEqual(incomingPacket,"Turn ON") ) {
      Serial.print("OK Turn ON the charger");
    }else{
      Serial.print("OK Turn OFF the charger");
    }
    //Send the packet to the client 
    udp.beginPacket(udp.remoteIP(),udp.remotePort());
    udp.write(replayPacket);
    udp.endPacket();

  }
}
