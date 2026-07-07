/*
 * Project 02 - Automated Irrigation Controller
 * Decode Labs IoT Internship
 *
 * Board  : ESP32
 * Sensor : Simulated Soil Moisture (Potentiometer)
 *
 * Reads soil moisture level and automatically
 * controls a water pump (LED).
 */

#define SOIL_SENSOR_PIN 34
#define PUMP_PIN 2

int soilValue;
int moisturePercent;

unsigned long previousMillis = 0;
const unsigned long interval = 2000;

void setup() {

  Serial.begin(115200);

  pinMode(PUMP_PIN, OUTPUT);

  Serial.println();
  Serial.println("=======================================");
  Serial.println(" Automated Irrigation Controller");
  Serial.println("=======================================");
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // Read analog value
    soilValue = analogRead(SOIL_SENSOR_PIN);

    // Convert to percentage
    moisturePercent = map(soilValue, 4095, 0, 0, 100);

    // Limit values
    moisturePercent = constrain(moisturePercent, 0, 100);

    Serial.println("--------------------------------");

    Serial.print("Soil Moisture : ");
    Serial.print(moisturePercent);
    Serial.println(" %");

    if (moisturePercent < 40) {

      digitalWrite(PUMP_PIN, HIGH);

      Serial.println("Pump Status   : ON");
      Serial.println("Action        : Irrigation Started");

    }
    else {

      digitalWrite(PUMP_PIN, LOW);

      Serial.println("Pump Status   : OFF");
      Serial.println("Action        : Soil Moist Enough");

    }

    Serial.println("--------------------------------");
    Serial.println();

  }

}