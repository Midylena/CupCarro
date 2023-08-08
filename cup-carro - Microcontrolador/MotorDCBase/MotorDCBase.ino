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

  Serial.begin(115200);
}

void loop() {
  /////////////////////////////
  // Motor 1 ClockWise
  digitalWrite(M1CWPin,  LOW);
  digitalWrite(M1CCWPin, HIGH);

  // Motor 2 ClockWise
  digitalWrite(M2CWPin, HIGH);
  digitalWrite(M2CCWPin, LOW);

  // Both motors full speed
  analogWrite(M1PWMPin, 50);
  analogWrite(M2PWMPin, 50);

  // Move for two seconds
  delay (2000);

  ////////////////////////////////
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
