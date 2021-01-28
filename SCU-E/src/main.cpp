/**
 * @file Aplication.cpp
 * @author Kelompok V
 * @version 3.0 1/15/21
*/

#include <Arduino.h>
#include <WiFi.h>

#include "ClientHandling.h"
#include "HTMLResponses.h"


const char *ssid = "SSID";
const char *pass = "PASS";

const unsigned char servo_pin = 18;
const unsigned char servo_channel = 0;

String table_state = "lowered";

WiFiServer server(80);

/**
 * The setup function, run only once.
*/

void setup()
{
  Serial.begin(115200);

  ledcAttachPin(servo_pin, servo_channel);
  ledcSetup(servo_channel, 50, 8);

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
  Serial.
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
    ClientHandling *client_handler = new ClientHandling(client, INDEX_HTML, table_state, servo_pin);
    //Loop while connected to client
    client_handler->HandleRequest();
    //Closing the connection.
    client_handler->~ClientHandling();
  }
}
