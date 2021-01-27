/**
 * @file Aplication.cpp
 * @author Kelompok V
 * @version 3.0 1/15/21
*/

#include <Arduino.h>
#include <WiFi.h>

#include "ClientHandling.h"
#include "HTMLResponses.h"
#include "ESP32_Servo.h"


const char *ssid = "SSID";
const char *pass = "PASS";

const unsigned char servo_pin = 18; 
Servo myservo;

String table_state = "lowered";

WiFiServer server(80);

/**
 * The setup function, run only once.
*/
void setup()
{
  Serial.begin(115200);

  myservo.attach(servo_pin, 1000, 2000);

  Serial.printf("\n\nConnecting to: %s\n", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

/**
 * The main code, run repeatedly.
*/
void loop()
{
  //Listen for incoming clients
  WiFiClient client = server.available();
  if (client)
  {
    ClientHandling *client_handler = new ClientHandling(client, INDEX_HTML, table_state, myservo);
    //Loop while connected to client
    client_handler->HandleRequest();
    //Closing the connection.
    client_handler->~ClientHandling();
  }
}
