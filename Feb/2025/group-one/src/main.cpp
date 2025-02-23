#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include <HTTPClient.h>
#include "http.hpp"
// WiFi Credentials
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6


// PIR Sensor Calibration Time (10-60 secs according to the datasheet)
constexpr int calibrationTime = 10;        

// Time when the sensor outputs a LOW impulse
unsigned long lowIn;         

// Time (ms) the sensor must stay LOW before assuming motion has stopped
constexpr unsigned long pauseDuration = 5000;  

// PIR Sensor & Buzzer Pins
constexpr int pirPin = 13;    // PIR sensor digital output
constexpr int buzzerPin = 18; // Buzzer output

// PWM settings for ESP32 (LEDC)
#define BUZZER_PWM_CHANNEL 0  // Use LEDC channel 0
#define BUZZER_FREQUENCY 500  // 500 Hz tone
#define BUZZER_RESOLUTION 8   // 8-bit resolution (0-255)

// State flags
bool lockLow = true;
bool takeLowTime = false;

// SETUP FUNCTION
void setup() {
    Serial.begin(9600);

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
    Serial.print("Connecting to WiFi ");
    Serial.print(WIFI_SSID);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println(" Connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Pin Modes
    pinMode(pirPin, INPUT);
    pinMode(buzzerPin, OUTPUT);

    // Initialize LEDC PWM for buzzer
    ledcSetup(BUZZER_PWM_CHANNEL, BUZZER_FREQUENCY, BUZZER_RESOLUTION);
    ledcAttachPin(buzzerPin, BUZZER_PWM_CHANNEL);

    digitalWrite(pirPin, LOW);

    // Sensor Calibration
    Serial.print("Calibrating sensor ");
    for (int i = 0; i < calibrationTime; i++) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" Done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}

// LOOP FUNCTION
void loop() {
    bool motionDetected = digitalRead(pirPin) == HIGH;

    if (motionDetected) {

        sendSMS();
        ledcWrite(BUZZER_PWM_CHANNEL, 128); // 50% duty cycle for sound
        
      
        if (lockLow) {  
            lockLow = false;            
            Serial.println("---");
            Serial.print("Motion detected at ");
            Serial.print(millis() / 1000);
            Serial.println(" sec"); 
            delay(30000);
        }         
        takeLowTime = true;
    } else {       
        ledcWrite(BUZZER_PWM_CHANNEL, 0); // Stop buzzer
        if (takeLowTime) {
            lowIn = millis(); // Save time of LOW transition
            takeLowTime = false;
        }
        
        // If sensor is LOW for longer than `pauseDuration`, assume motion has stopped
        if (!lockLow && ((uint32_t)(millis() - lowIn) > pauseDuration)) { 
            lockLow = true;                        
            Serial.print("Motion ended at ");
            Serial.println(millis() / 1000);
            delay(50);
        }
    }
}