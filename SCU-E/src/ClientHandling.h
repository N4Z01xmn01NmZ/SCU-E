#pragma once

#include <Arduino.h>
#include <WiFi.h>

class ClientHandling
{
private:
    //Used to refer to the client object
    WiFiClient* m_client;
    //Used to hold incoming data from client
    String m_current_line = "";
    //HTML code
    const char *m_html_code;

    const int m_timeout;
public:
    ClientHandling(WiFiClient* client, const char *html_code, int timeout = 15);
    ~ClientHandling();

    void HandleRequest();
    void HeaderResponse();
    void WebPageResponse();
};