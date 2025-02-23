#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const char* serverName = "https://api.africastalking.com/version1/messaging/bulk";

const char* apiKey = "sandbox";
const char* username = "api";

// PIR sensor pin
const int PIR_SENSOR_OUTPUT_PIN = 13;
int warm_up;

unsigned long lastTime = 0;
unsigned long timerDelay = 5000; // Send SMS after every 5 seconds of motion detection

void setup() {
  pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);
  Serial.begin(115200);  // Initialize serial communication
  Serial.println("Waiting For Power On Warm Up");
  delay(20000);  // Warm-up delay
  Serial.println("Ready!");
  
  WiFi.begin(ssid, password);  // Connect to Wi-Fi
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);  // Read PIR sensor output
  if(sensor_output == LOW) {
    if(warm_up == 1) {
      Serial.print("Warming Up\n\n");
      warm_up = 0;
      delay(2000);
    }
    Serial.print("No object in sight\n\n");
    delay(1000);
  } else {
    Serial.print("Object detected\n\n");
    warm_up = 1;

    // Send SMS when motion is detected
    sendSMS();

    delay(1000); // Add delay for sensor stabilization
  }
}

void sendSMS() {
  // Only send SMS if it's been 5 seconds since the last message
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      // Begin HTTP connection to Africa's Talking API
      http.begin(client, serverName);

      // Set HTTP Headers
      http.addHeader("Accept", "application/json");
      http.addHeader("Content-Type", "application/json");
      http.addHeader("apiKey", apiKey);  // Africa's Talking API Key

      // Prepare message data
      String phoneNumbers = "[\"+254700000000\"]"; // List of phone numbers (use actual phone numbers)
      String message = "Motion detected! Please check your security system.";
      String httpRequestData = "{\"username\":\"" + String(username) + "\", \"message\":\"" + message + "\", \"phoneNumbers\":" + phoneNumbers + "}";

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // Print HTTP response code for debugging
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      // Free resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();  // Update the last time SMS was sent
  }
}