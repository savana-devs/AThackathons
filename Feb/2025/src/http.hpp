#ifndef HTTP_HPP
#define HTTP_HPP

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>

const char* serverName = "http://6.tcp.eu.ngrok.io:15158";
unsigned long timerDelay = 5000;
unsigned long lastTime = 0;

void sendSMS() {
    if ((millis() - lastTime) > timerDelay) {
        if (WiFi.status() == WL_CONNECTED) {
            WiFiClient client;
            HTTPClient http;

            // Begin HTTP GET request
            http.begin(client, serverName);

            // Send request and get response code
            int httpResponseCode = http.GET();

            // Print response code
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);

            // Print response payload
            if (httpResponseCode > 0) {
                String response = http.getString();
                Serial.println("Response:");
                //Serial.println(response);
            }

            // End request
            http.end();

        } else {
            Serial.println("WiFi Disconnected");
        }
        lastTime = millis();  // Update last request time
    }
}

#endif