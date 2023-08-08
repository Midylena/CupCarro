#include "Ultrasonic.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http; 

const int echoPin = 26; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin1 = 25; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA) 
const int trigPin2 = ;
const int trigPin3 = ;
const int trigPin4 = ;
const int trigPin5 = ;
const int trigPin6 = ;

Ultrasonic ultrasonic1(trigPin1,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
Ultrasonic ultrasonic2(trigPin2,echoPin);
Ultrasonic ultrasonic3(trigPin3,echoPin);
Ultrasonic ultrasonic4(trigPin4,echoPin);
Ultrasonic ultrasonic5(trigPin5,echoPin);
Ultrasonic ultrasonic6(trigPin6,echoPin);
 
int distancia1; //VARIÁVEL DO TIPO INTEIRO
String result1; //VARIÁVEL DO TIPO STRING

int distancia2;
String result2;

int distancia3;
String result3;

int distancia4;
String result4;

int distancia5;
String result5;

int distancia6;
String result6;

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
  Serial.begin(115200);
  WiFi.begin("MILENAREDE3", "12345678");
  
  pinMode(M1CWPin, OUTPUT);
  pinMode(M1CCWPin, OUTPUT);
  pinMode(M2CWPin, OUTPUT);
  pinMode(M2CCWPin, OUTPUT);
  pinMode(M1CurrentSensePin, INPUT);
  pinMode(M2CurrentSensePin, INPUT);

  digitalWrite(M1CWPin, LOW);
  digitalWrite(M1CCWPin, LOW);
  digitalWrite(M2CWPin, LOW);
  digitalWrite(M2CCWPin, LOW);

  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin1, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  pinMode(trigPin2, OUTPUT)
  pinMode(trigPin3, OUTPUT)
  pinMode(trigPin4, OUTPUT)
  pinMode(trigPin5, OUTPUT)
  pinMode(trigPin6, OUTPUT)

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(1000);
    Serial.println("CONECTANDO...");
  }
  Serial.println("CONECTADO!");
}

void loop() {
  //Check WiFi connection status
  hcsr04();
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
  else if(distancia1 <= 30 || distancia2 <= 30 || distancia3 <= 30 || distancia4 <= 30 || distancia5 <= 30 || distancia6 <= 30){
      // Motor 1 CounterClockWise
      digitalWrite(M1CWPin, LOW);
      digitalWrite(M1CCWPin, LOW);
    
      // Motor 2 CounterClockWise
      digitalWrite(M2CWPin, LOW);
      digitalWrite(M2CCWPin, LOW);
    
      // Both motors full speed
      analogWrite(M1PWMPin, 0);
      analogWrite(M2PWMPin, 0);
      }else{
        // Motor 1 CounterClockWise
        digitalWrite(M1CWPin, HIGH);
        digitalWrite(M1CCWPin, LOW);
      
        // Motor 2 CounterClockWise
        digitalWrite(M2CWPin, LOW);
        digitalWrite(M2CCWPin, HIGH);
      
        // Both motors full speed
        analogWrite(M1PWMPin, 50);
        analogWrite(M2PWMPin, 50);
      
        // Move for two seconds
        delay (2000);
    }
    // Disconnect
    http.end();
    delay(2000);
  }
  else{
    Serial.println("Error in WiFi connection");
  }
}

void hcsr04(){
    digitalWrite(trigPin1, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin1, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin1, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia1 = (ultrasonic1.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result1 = String(distancia1); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS

    digitalWrite(trigPin2, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin2, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin2, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia2 = (ultrasonic2.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result2 = String(distancia2); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS

    digitalWrite(trigPin3, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin3, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin3, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia3 = (ultrasonic3.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result3 = String(distancia3); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS

    digitalWrite(trigPin4, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin4, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin4, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia4 = (ultrasonic4.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result4 = String(distancia4); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS

    digitalWrite(trigPin5, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin5, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin5, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia5 = (ultrasonic5.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result5 = String(distancia5); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS

    digitalWrite(trigPin6, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin6, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin6, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia6 = (ultrasonic6.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result6 = String(distancia6); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
}
