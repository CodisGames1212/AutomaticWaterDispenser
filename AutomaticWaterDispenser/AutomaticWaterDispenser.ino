#include <Servo.h>

Servo dispenserServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 8;

const int dispenseAngle = 90;
const int idleAngle = 0; 
const int detectDistance = 10;
const int dispenseTime = 1000;

void setup() {
  dispenserServo.attach(servoPin);
  dispenserServo.write(idleAngle);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

long readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long distance = readDistanceCM();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= detectDistance) {
    dispenserServo.write(dispenseAngle);
    delay(dispenseTime);
    dispenserServo.write(idleAngle);
    delay(1000);
  }

  delay(200);
}
