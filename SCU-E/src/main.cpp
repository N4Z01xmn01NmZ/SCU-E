/**
 * @file Aplication.cpp
 * @author Kelompok V
 * @version 3.0 1/15/21
*/
#include <fstream>

#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>

#include "ClientHandling.h"
#include "HTMLResponses.h"
#include "ServoKonti.h"

const char *ssid = "SSID";
const char *pass = "PASS";

const unsigned char servo_pin = 18;
const unsigned char servo_channel = 0;

String table_state = "lowered";

WiFiServer server(80);
ServoKonti servo(servo_pin, servo_channel, 50, 8);

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
    ClientHandling ClientHandling(&client, INDEX_HTML);
    //Loop while connected to client
    ClientHandling.HandleRequest();
    //Closing the connection.
    ClientHandling.~ClientHandling();
  }
}
