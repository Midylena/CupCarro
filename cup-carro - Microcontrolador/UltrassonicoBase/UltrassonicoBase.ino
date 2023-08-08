#include "Ultrasonic.h" 

const int echoPin = D0; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin2 = D2; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int trigPin1 = D1; 

Ultrasonic ultrasonic1(trigPin1,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
Ultrasonic ultrasonic2(trigPin2,echoPin);
 
int distancia1; //VARIÁVEL DO TIPO INTEIRO
String result1; //VARIÁVEL DO TIPO STRING

int distancia2; //VARIÁVEL DO TIPO INTEIRO
String result2; //VARIÁVEL DO TIPO STRING
 
void setup(){
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin1, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  pinMode(trigPin2, OUTPUT);
  Serial.begin(115200); //INICIALIZA A PORTA SERIAL
  }
void loop(){
  
  hcsr04(); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  Serial.print("Distancia 1 "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(result1); ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.println("cm"); //IMPRIME O TEXTO NO MONITOR SERIAL

  Serial.print("Distancia 2 "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(result2); ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.println("cm"); //IMPRIME O TEXTO NO MONITOR SERIAL
  
}
//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
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
 }
