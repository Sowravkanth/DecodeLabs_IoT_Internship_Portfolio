/*
 * Project 03 - Cloud Connected Smart Security System
 * DecodeLabs IoT Internship
 *
 * ESP32 + HC-SR04 + LED + Adafruit IO MQTT
 */

#include <WiFi.h>
#include <PubSubClient.h>

// -------------------- Pins --------------------
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 2

// -------------------- WiFi --------------------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// -------------------- Adafruit IO --------------------
const char* mqttServer = "io.adafruit.com";
const int mqttPort = 1883;

const char* mqttUser = "YOUR_ADAFRUIT_AIO_USERNAME";
const char* mqttPassword = "YOUR_ADAFRUIT_AIO_KEY";

// MQTT Topics
const char* distanceFeed = "YOUR_ADAFRUIT_AIO_USERNAME/feeds/distance";
const char* statusFeed = "YOUR_ADAFRUIT_AIO_USERNAME/feeds/status";

// -------------------- Objects --------------------
WiFiClient espClient;
PubSubClient client(espClient);

// -------------------- Variables --------------------
unsigned long previousMillis = 0;
const unsigned long interval = 2000;

long duration;
float distance;

// =====================================================

void connectWiFi() {

  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

}

// =====================================================

void connectMQTT() {

  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {

    Serial.print("Connecting to MQTT... ");

    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {

      Serial.println("Connected!");

    } else {

      Serial.print("Failed (");
      Serial.print(client.state());
      Serial.println(")");
      Serial.println("Retrying in 2 seconds...");

      delay(2000);

    }

  }

}

// =====================================================

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println();
  Serial.println("======================================");
  Serial.println(" Cloud Connected Security Node");
  Serial.println(" DecodeLabs Project 03");
  Serial.println("======================================");

  connectWiFi();
  connectMQTT();

  Serial.println();
  Serial.println("System Ready");
  Serial.println();

}

// =====================================================

void loop() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi Lost. Reconnecting...");
    connectWiFi();

  }

  if (!client.connected()) {

    Serial.println("MQTT Lost. Reconnecting...");
    connectMQTT();

  }

  client.loop();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // Trigger Sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure Echo
    duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate Distance
    distance = duration * 0.0343 / 2.0;

    Serial.println("--------------------------------------");

    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");

    // Convert distance to string
    char distanceBuffer[10];
    dtostrf(distance, 4, 2, distanceBuffer);

    // Publish Distance
    client.publish(distanceFeed, distanceBuffer);

    if (distance < 20) {

      digitalWrite(LED_PIN, HIGH);

      Serial.println("Status   : ALERT");
      Serial.println("LED      : ON");
      Serial.println("Message  : Intruder Detected");

      client.publish(statusFeed, "ALERT");

    } else {

      digitalWrite(LED_PIN, LOW);

      Serial.println("Status   : SAFE");
      Serial.println("LED      : OFF");
      Serial.println("Message  : Area Secure");

      client.publish(statusFeed, "SAFE");

    }

    Serial.println("Published to Adafruit IO");
    Serial.println("--------------------------------------");
    Serial.println();

  }

}
