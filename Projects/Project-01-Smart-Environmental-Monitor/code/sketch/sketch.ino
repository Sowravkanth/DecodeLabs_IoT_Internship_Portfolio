/*
 * Project 01 - Smart Environmental Monitor
 * Decode Labs IoT Internship
 *
 * Board  : ESP32
 * Sensor : DHT22
 *
 * Reads temperature and humidity from the DHT22 sensor
 * and displays the values on the Serial Monitor.
 */

#include <DHT.h>

// -----------------------------
// Pin Configuration
// -----------------------------
#define DHTPIN 4          // GPIO connected to DHT22 DATA pin
#define DHTTYPE DHT22     // Sensor Type

// Create DHT object
DHT dht(DHTPIN, DHTTYPE);

// Variables
float temperature;
float humidity;

// Time control
unsigned long previousMillis = 0;
const unsigned long interval = 2000;   // Read every 2 seconds

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("====================================");
  Serial.println(" Smart Environmental Monitor");
  Serial.println(" Decode Labs IoT Internship");
  Serial.println("====================================");

  dht.begin();
}

void loop() {

  unsigned long currentMillis = millis();

  // Read sensor every 2 seconds
  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    // Check if sensor reading failed
    if (isnan(temperature) || isnan(humidity)) {

      Serial.println("Failed to read from DHT22 Sensor!");
      return;

    }

    Serial.println("------------------------------");
    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity    : ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.println("------------------------------");
    Serial.println();

  }

}