#  Smart Environmental Monitor

> **Project 01** of the **Decode Labs IoT Engineering Internship**

A simple IoT-based environmental monitoring system built using an ESP32 and a DHT22 sensor. The project reads real-time temperature and humidity values and displays them on the Serial Monitor.

---

##  Project Overview

Environmental monitoring is one of the fundamental applications of the Internet of Things (IoT). This project demonstrates how an ESP32 interfaces with a DHT22 sensor to continuously monitor temperature and humidity in real time.

---

##  Objectives

- Interface the DHT22 sensor with the ESP32
- Read temperature and humidity values
- Display sensor readings on the Serial Monitor
- Understand basic sensor interfacing using Arduino IDE

---

##  Hardware Components

| Component | Quantity |
|----------|----------|
| ESP32 Dev Board | 1 |
| DHT22 Sensor | 1 |

---

##  Software Used

- Arduino IDE
- Visual Studio Code
- Wokwi Simulator
- Git & GitHub

---

##  Circuit Connections

| DHT22 Pin | ESP32 Pin |
|-----------|-----------|
| VCC | 3.3V |
| DATA | GPIO 4 |
| GND | GND |

---

##  Working Principle

1. The ESP32 initializes the DHT22 sensor.
2. The sensor measures temperature and humidity.
3. The ESP32 reads the sensor values every two seconds.
4. The readings are displayed on the Serial Monitor.

---

##  Project Structure

```text
Project-01-Smart-Environmental-Monitor
│
├── code
│   ├── sketch.ino
│   ├── diagram.json
│   ├── libraries.txt
│   └── wokwi.toml
│
├── images
├── README.md
└── report.md
```

---

## ▶ Running the Project

1. Open the project in Arduino IDE.
2. Install the required libraries:
   - DHT sensor library by Adafruit
   - Adafruit Unified Sensor
3. Select **ESP32 Dev Module** as the target board.
4. Compile the sketch.
5. Simulate the circuit in Wokwi or upload it to an ESP32 board.

---

##  Results

The project successfully compiles using Arduino IDE with the ESP32 board package.

Simulation screenshots and Serial Monitor output will be added after successful execution in Wokwi.

---

##  License

This project was developed as part of the **Decode Labs IoT Engineering Internship** for educational purposes.
