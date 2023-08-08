#include "Ultrasonic.h" 

const int echoPin = 26; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 25; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA) 

Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
 
int distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING

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
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)

  Serial.begin(115200);
}

void loop() {
  hcsr04();
  if(distancia <= 30){
      // Motor 1 CounterClockWise
      digitalWrite(M1CWPin, LOW);
      digitalWrite(M1CCWPin, LOW);
    
      // Motor 2 CounterClockWise
      digitalWrite(M2CWPin, LOW);
      digitalWrite(M2CCWPin, LOW);
    
      // Both motors full speed
      analogWrite(M1PWMPin, 0);
      analogWrite(M2PWMPin, 0);
    }
    else{
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
}

void hcsr04(){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
}
