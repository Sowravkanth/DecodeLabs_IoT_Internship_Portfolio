/*
 * Project 03 - Smart Security Alert System
 * Decode Labs IoT Internship
 *
 * Board  : ESP32
 * Sensor : HC-SR04 Ultrasonic Sensor
 * Output : LED
 *
 * Measures distance and turns ON the LED
 * when an object is detected nearby.
 */

#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 2

unsigned long previousMillis = 0;
const unsigned long interval = 2000;

long duration;
float distance;

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println();
  Serial.println("=====================================");
  Serial.println(" Smart Security Alert System");
  Serial.println("=====================================");
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = duration * 0.034 / 2;

    Serial.println("-------------------------------------");
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < 20) {

      digitalWrite(LED_PIN, HIGH);

      Serial.println("Status   : ALERT");
      Serial.println("LED      : ON");
      Serial.println("Message  : Intruder Detected");

    } else {

      digitalWrite(LED_PIN, LOW);

      Serial.println("Status   : SAFE");
      Serial.println("LED      : OFF");
      Serial.println("Message  : Area Secure");

    }

    Serial.println("-------------------------------------");
    Serial.println();

  }

}