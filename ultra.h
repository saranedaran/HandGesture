ultra.h


const int trigPin = D0;
const int echoPin = D1;
void ultra_init() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

float dist() {
  // Send a trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(50);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(trigPin, LOW);

  // Measure the echo pulse
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
   return distance;
  delay(1000);

  
}