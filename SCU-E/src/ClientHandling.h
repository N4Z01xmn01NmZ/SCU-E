#pragma once

#include <Arduino.h>
#include <WiFi.h>

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

    const unsigned char m_servo_pin;
    const int m_timeout;
public:
    ClientHandling(WiFiClient &client, const char *html_code, String &state, unsigned char servo_pin, int timeout = 15);
    ~ClientHandling();

    void HandleRequest();
    void HeaderResponse();
    void WebPageResponse();

    void Clearheader();
};