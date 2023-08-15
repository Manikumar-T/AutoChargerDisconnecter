#include <Arduino.h>
//ESP3266WiFi module is used to access the Wifi
#include<ESP8266WiFi.h>
//WiFiUdp module is used to Create the udp server
#include<WiFiUdp.h>

bool isEqual(char value1[] , char value2[]);
void buzzerTone(int tone_no);

//It's the SSID and Password of the wifi network i want to connect
#define SSID "Mani's Galaxy A71"
#define PASSWORD "        "
#define BUZZER 5 //D1
//Define the Port the server has to run
#define PORT 4210

//UDP object to access to initialize the udp server
WiFiUDP udp;

//char arrar of message to send to client
//char replayPacket[] = "Hi i am esp8266 speaking ";

//Function to Compare the two string
bool isEqual(char value1[] , char value2[]) {
 return std::strcmp(value1, value2) == 0;
}

//Buzzer to produce the tone 
void buzzerTone(int tone_no) {
  if(tone_no == 0) {
    //tone for of the buzzer
    noTone(BUZZER);
  }else if (tone_no == 1) {
    //for forgot to turn of the charger
      tone(BUZZER,1000);
      
  }else if (tone_no == 2){
    //Charge is full
    for(int i=0; i<5; i++)
    {
      tone(BUZZER,1000);
      delay(1000);
      noTone(BUZZER);
      delay(1000);
      

    } 
    noTone(BUZZER);
    Serial.print("\n Buzzer OFF");
  }else if (tone_no == 3){
    for(int i=0; i<5; i++)
    {
      //charge is low
      tone(BUZZER,3000);
      delay(1000);
      tone(BUZZER,2500);
      delay(1000);
      tone(BUZZER,2000);
      delay(1000);
      tone(BUZZER,1500);
      delay(1000);
      tone(BUZZER,1000);
      delay(1000);
      noTone(BUZZER);
      delay(1000);

    }
    noTone(BUZZER);
    Serial.print("\n Buzzer OFF\n");
    
  }
  
}

void setup() {
  
  //Begin the Serial monitor
  Serial.begin(9600);
  Serial.print("\nESP8266 is Started....\n");

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
  Serial.print("\nConnected, IP address:");
  Serial.print(WiFi.localIP());
  
  //Begin to listening 
  Serial.print("\nStart UDP server at port 4210\n");
  udp.begin(PORT);

 //Initialize the Buzzer
 pinMode(BUZZER,OUTPUT);
  
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

    if (isEqual(incomingPacket,"FULL") ) {
      Serial.print("\nOK Turn ON Buzzer for FULL\n");
      buzzerTone(2);
  
    }else if(isEqual(incomingPacket,"LOW")){
      Serial.print("\nOK Turn ON Buzzer for LOW\n");
      buzzerTone(3);
    }else if (isEqual(incomingPacket,"OFF"))
    {
      buzzerTone(0);
      Serial.print("\nBuzzer OFF\n");
    }else if (isEqual(incomingPacket,"shutdown"))
    {
      buzzerTone(1);
      Serial.print("\nBuzzer ON  For Shutdown\n");
    }else if (isEqual(incomingPacket,"wait&down"))
    { 
      delay(20 * 60 * 1000);
      buzzerTone(1);
      Serial.print("\nBuzzer ON for Wait and shutdown\n");
      
    }else{
      Serial.print("\nInvalid instruction\n");
    }
    
    //Send the packet to the client 
    // udp.beginPacket(udp.remoteIP(),udp.remotePort());
    // udp.write(replayPacket);
    // udp.endPacket();

  }
}
