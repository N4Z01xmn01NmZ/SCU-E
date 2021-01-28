#include "ClientHandling.h"

/**
 * ClientHandling class constructor
 * @param client Reference to existing client object
 * @param html_code Reference to existing HTML code
 * @param state Reference to table state variable
 * @param servo Reference to existing servo object
 * @param timeout Web server refresh timeout
*/
ClientHandling::ClientHandling(WiFiClient &client, const char *html_code, String &state, unsigned char servo_pin, int timeout)
    : m_client(client), m_html_code(html_code), m_table_state(state), m_servo_pin(servo_pin), m_timeout(timeout)
{
    Serial.println("New client");
}

/**
 * ClientHandling class destructor
*/
ClientHandling::~ClientHandling()
{
    m_client.stop();
    Serial.println("Client disconnected.");
    Serial.println();
}

/**
 * Loop while connected to client
*/
void ClientHandling::HandleRequest()
{
    while (m_client.connected())
    {
        //If recieved incoming bytes from client
        if (m_client.available())
        {
            //Read a byte
            char c = m_client.read();
            Serial.write(c);
            m_header += c;
            if (c == '\n')
            {
                //If the current line is blank, it marks the end of the client HTTP request because it had recieved two newline characters in a row, so send a response
                if (m_current_line.length() == 0)
                {
                    HeaderResponse();
                    if (m_header.indexOf("GET /raise") >= 0)
                    {
                        if (m_table_state != "raised")
                        {
                            Serial.printf("State: %s\n", m_table_state);
                            Serial.println("Raising");
                            for(int i = 0; i < 256; i++)
                            {
                                ledcWrite(m_servo_pin, i);
                            }
                            delay(400);
                            m_table_state = "raised";
                            Serial.printf("State: %s\n", m_table_state);
                        }
                    }
                    if (m_header.indexOf("GET /lower") >= 0)
                    {
                        if (m_table_state != "lowered")
                        {
                            Serial.printf("State: %s\n", m_table_state);
                            Serial.println("Lowering");
                            for(int i = 256; i > 1; i--)
                            {
                                ledcWrite(m_servo_pin, i);
                            }
                            delay(400);
                            m_table_state = "lowered";
                            Serial.printf("State: %s\n", m_table_state);
                        }
                    }

                    //The content of the HTTP response as follows.
                    WebPageResponse();
                    //Ends HTTP response with a newline character.
                    m_client.println();
                    //Exiting while loop.
                    break;
                }
                else
                {
                    //If a newline is recieved, clear the m_current_line
                    m_current_line = "";
                }
            }
            else if (c != '\r')
            {
                //If nothing is recieved but a carriage return, added to the end of m_current_line
                m_current_line += c;
            }
            //Process the client request.
        }
    }
}

/**
 * Sending a HTTP response header starting with a response code (e.g. HTTP/1.1 200 OK)
 * followed by the content type the client expect to recieve and ends with a newline character
*/
void ClientHandling::HeaderResponse()
{
    m_client.println("HTTP/1.1 200 OK");
    m_client.printf("Keep-Alive: timeout=%d, max=100\n", m_timeout);
    m_client.println("Connection: Keep-Alive");
    m_client.println("Content-type:text/html");
    m_client.println();
}

void ClientHandling::WebPageResponse()
{
    m_client.print(m_html_code);
}

void ClientHandling::Clearheader()
{
    m_header = "";
}