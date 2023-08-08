#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http;

void setup() {
  Serial.begin(115200);                 //Serial connection
  WiFi.begin("MILENAREDE", "Fa1718280317");   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(1000);
    Serial.println("CONECTANDO...");
  }
}
 
void loop() {
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {       
      // Send request
      http.begin(client, "http://26.17.180.2:8080/historicoCupCarro/get");
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

      // Disconnect
      http.end();
      delay(2000);   
  }
  else{
    Serial.println("Error in WiFi connection");
  }
}
