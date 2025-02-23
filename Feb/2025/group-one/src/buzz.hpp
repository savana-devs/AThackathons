#ifndef HTTP_BUZZ_HPP
#define HTTP_BUZZ_HPP

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>

const char* serverNamebuzz = "http://6.tcp.eu.ngrok.io:15158/buzz";
unsigned long timerDelaybuzz = 5000; 
unsigned long lastTimebuzz = 0;

String sendBUZZ() {
    if ((millis() - lastTimebuzz) > timerDelaybuzz) {
        if (WiFi.status() == WL_CONNECTED) {
            WiFiClient client;
            HTTPClient http;

            // Begin HTTP GET request
            http.begin(client, serverNamebuzz);

            // Send request and get response code
            int httpResponseCode = http.GET();

            // Print response code
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);

            // Print response payload
            if (httpResponseCode > 0) {
                String response = http.getString();
                Serial.println("Response:");
                Serial.println(response);
                return response.c_str();
            }

            // End request
            http.end();

        } else {
            Serial.println("WiFi Disconnected");
        }
        lastTimebuzz = millis();  // Update last request time
    }

    
}

#endif