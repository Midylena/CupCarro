#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http;

/// Motor 1
const byte M1CWPin = 5;  // INA: Clockwise input
const byte M1CCWPin = 18;  // INB: Counter-clockwise input
const byte M1PWMPin = 2;  // PWM input
const byte M1CurrentSensePin = 14;  // CS: Current sense ANALOG input
const byte M1EnablePin = 13;  // EN: Status of switches output (Analog pin)

// Motor 2
const byte M2CWPin = 15;  // INA: Clockwise input
const byte M2CCWPin = 19; // INB: Counter-clockwise input
const byte M2PWMPin = 4; // PWM input
const byte M2CurrentSensePin = 27; // CS: Current sense ANALOG input
const byte M2EnablePin = 12; // EN: Status of switches output (Analog pin)

void setup() {
 
  Serial.begin(115200);                 //Serial connection
  WiFi.begin("MILENAREDE3", "12345678");   //WiFi connection
  
  pinMode(M1CWPin, OUTPUT);
  pinMode(M1CCWPin, OUTPUT);
  pinMode(M2CWPin, OUTPUT);
  pinMode(M2CCWPin, OUTPUT);

  digitalWrite(M1CWPin, LOW);
  digitalWrite(M1CCWPin, LOW);
  digitalWrite(M2CWPin, LOW);
  digitalWrite(M2CCWPin, LOW);
  
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(1000);
    Serial.println("CONECTANDO...");
  }
}
 
void loop() {
  
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {       
      // Send request
      http.begin(client, "http://192.168.155.129:8080/historicoCupCarro/get");
      http.GET();
      String historico = http.getString();
      StaticJsonDocument<128> doc;
      DeserializationError error = deserializeJson(doc, historico);

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      
      JsonObject root = doc[0];
      int id = root["id"];
      int numClasse = root["numClasse"];
      const char* classe = root["classe"];
      
      // Print the response
      Serial.println(classe);
      String classeString(classe);
      
      // Both motors stop when camera sees someone
      if (classeString.equals("person") || classeString.equals("traffic light") || classeString.equals("stop sign")){
        // Motor 1 Stops
        digitalWrite(M1CWPin, LOW);
        digitalWrite(M1CCWPin, LOW);
      
        // Motor 2 Stops
        digitalWrite(M2CWPin, LOW);
        digitalWrite(M2CCWPin, LOW);
      
        // Both motors Stopped
        analogWrite(M1PWMPin, 0);
        analogWrite(M2PWMPin, 0);
      }
      else{
        // Motor 1 ClockWise
        digitalWrite(M1CWPin, HIGH);
        digitalWrite(M1CCWPin, LOW);
      
        // Motor 2 ClockWise
        digitalWrite(M2CWPin, HIGH);
        digitalWrite(M2CCWPin, LOW);
      
        // Both motors full speed
        analogWrite(M1PWMPin, 100);
        analogWrite(M2PWMPin, 100);
      }
      // Disconnect
      http.end();
      delay(2000);   
  }
  else{
    Serial.println("Error in WiFi connection");
  }
}
