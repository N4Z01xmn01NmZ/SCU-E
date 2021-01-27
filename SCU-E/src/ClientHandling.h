#pragma once

#include <Arduino.h>
#include <WiFi.h>

#include "ESP32_Servo.h"

class ClientHandling
{
    //typedef enum
private:
    //Used to refer to the client object
    WiFiClient m_client;
    //Used to hold incoming data from client
    String m_header = "";
    String m_current_line = "";
    //HTML code
    const char *m_html_code;

    String m_table_state;
    Servo m_servo;

    const int m_timeout;
public:
    ClientHandling(WiFiClient &client, const char *html_code, String &state, Servo &servo, int timeout = 15);
    ~ClientHandling();

    void HandleRequest();
    void HeaderResponse();
    void WebPageResponse();

    void Clearheader();
};