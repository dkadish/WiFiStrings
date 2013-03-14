#include <WiFi.h>
#include <WiFiStringClient.h>

char ssid[] = "dd-wrt";     // the name of your network
int status = WL_IDLE_STATUS;     // the Wifi radio's status
byte mac[6];                     // the MAC address of your Wifi shield
IPAddress server(192,168,1,100);  // Processing Server

// Initialize the client library
//WiFiClient wfClient;
WiFiStringClient client;

boolean messageSent=false;

void setup() {
  // initialize serial:
  Serial.begin(9600);

  // attempt to connect to an open network:
  Serial.println("Attempting to connect to open network...");
  status = WiFi.begin(ssid);

  // if you're not connected, stop here:
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } 
  // if you are connected :
  else {
      Serial.println("Connected to the network");
      Serial.println("\nStarting connection...");
      // if you get a connection, report back via serial:
      if (client.connect(server, 10002)) {
        Serial.println("connected");
      }
  }
}

void loop() {
  if( !messageSent ){
    Serial.println("Sending a message");    
    client.writeString("Hello, Processing. Can you hear me?");
    messageSent = true;
    Serial.println("Message Sent");
  }
    
  if ( client.available() > 0) {
    Serial.print("READ: ");
    Serial.print(client.available());
    Serial.print(", ");
    Serial.println(client.readString());
    messageSent = false;
  }

}

