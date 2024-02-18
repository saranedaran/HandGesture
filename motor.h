const int Pin1 = D5;
const int Pin2 = D6;
const int Pin3 = D7;
const int Pin4 = D8;
void motor_init() {
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  Serial.begin(9600);
}
void stop() {
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, LOW);
  Serial.println("Stop");
    delay(500);
}
void reverse() {
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, HIGH);
  digitalWrite(Pin4, LOW);
  delay(500);
  Serial.println("Forward");
}
void forward() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, HIGH);
  delay(500);
  Serial.println("Reverse");
}
void left() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, LOW);
  delay(500);
  Serial.println("Reverse");
}
void right() {
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, HIGH);
  delay(500);
  Serial.println("Reverse");
}