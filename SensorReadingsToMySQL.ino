/*
  Web Service to MySQL 
*/

#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"

#define DHTPIN 2

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte ip[] = { 192, 168, 1, 75 };
byte gateway[] = { 192, 168, 1, 1 };
byte subnet[] = {255, 255, 255, 0 };

// Enter the MySQL server IP address
byte server[] = {111, 111, 111, 111};

EthernetClient client;

long lastReadingTime = 0;
float h = 0;
float tC = 0;
float tF = 0;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  delay(1000);
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  dht.begin();
}


void loop() { 

  //get sensor data
  getData();
  
  if(client.connect(server, 80))
    {
      Serial.println("connected...");
      Serial.println("ARDUINO: forming HTTP request message");

      client.print("GET /temperature/arduino_process.php?temp=");
      client.print(tF);
      client.print("&humidity=");
      client.print(h);
      client.println(" HTTP/1.1");
      client.println("Host: www.mysite.com");
      client.println();
      
      Serial.println("ARDUINO: HTTP message sent");
      
      delay(3000);

      if(client.available())
        {
          Serial.println("ARDUINO: HTTP message received");
          Serial.println("ARDUINO: printing received headers and script response...\n");

          while(client.available())
            {
              char c = client.read();
              Serial.print(c);
            }
        }
      else
        {
          Serial.println("ARDUINO: no response received / no response received in time");
        }

      client.stop();
    }
   
  else
    {
      Serial.println("connection failure");
    }

}

void getData() {

  h = dht.readHumidity();
  tC = dht.readTemperature();
  tF = (tC * 1.8) + 32.0;

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(tC) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  }
  else {
    Serial.println();
    Serial.print("DHT Humidity: "); 
    Serial.print(h);
    Serial.println("%");
    Serial.print("DHT F Temperature: "); 
    Serial.print(tF);
    Serial.println("* F");
    Serial.println();
  }

}
