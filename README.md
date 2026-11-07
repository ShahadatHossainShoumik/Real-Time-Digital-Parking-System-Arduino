<div align="center">

#  Real-Time Digital Parking Slot Monitoring & Control System
### *Towards Sustainable Cities: Microcontroller-Driven Automated Gate Control & Occupancy Tracking System*

![C++](https://img.shields.io/badge/Embedded_C++-Arduino_INO-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Arduino](https://img.shields.io/badge/Microcontroller-Arduino_UNO_(ATmega328P)-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Proteus](https://img.shields.io/badge/Simulation-Proteus_&_Tinkercad-1E88E5?style=for-the-badge&logo=autodesk&logoColor=white)
![Hardware](https://img.shields.io/badge/Sensors-Active_IR_&_I2C_LCD-FF6F00?style=for-the-badge)
![Status](https://img.shields.io/badge/Project_Status-Completed-success?style=for-the-badge)

**Course:** Microprocessor and Embedded Systems  
**Institution:** Department of Computer Science and Engineering, American International University-Bangladesh (AIUB)  
**Domain:** 🏙️ Smart Cities & Urban Mobility / 🤖 Embedded Systems & Hardware Automation

</div>

---

## 📖 Table of Contents
- [📌 Project Overview](#-project-overview)
- [🎯 Problem Statement & Urban Sustainability Impact](#-problem-statement--urban-sustainability-impact)
- [🛠️ Hardware Components & Software Tools](#️-hardware-components--software-tools)
- [🔌 System Architecture & Pinout Configuration](#-system-architecture--pinout-configuration)
- [⚙️ Operational Workflow & Control Algorithm](#️-operational-workflow--control-algorithm)
- [📊 Simulation, Experimental Results & Cost Analysis](#-simulation-experimental-results--cost-analysis)
- [🧱 Embedded C++ Firmware Implementation](#-embedded-c-firmware-implementation)
- [⚠️ System Limitations & Future Scope](#️-system-limitations--future-scope)
- [📂 Repository File Structure](#-repository-file-structure)
- [🚀 Hardware Setup & Execution Guide](#-hardware-setup--execution-guide)
- [👥 Project Group Members](#-project-group-members)

---

## 📌 Project Overview
**Towards Sustainable Cities: Design and Implementation of a Real-time Parking Slot Monitoring and Control System** is a microcontroller-based smart parking automation prototype developed at the Department of Computer Science and Engineering, **American International University-Bangladesh (AIUB)**.

Rapid urbanization and rising automobile ownership in metropolitan areas cause severe traffic congestion, wasted fuel, and driver frustration due to the absence of real-time parking vacancy data. This project designs, simulates (via **Proteus** and **Autodesk Tinkercad**), and physically implements a low-cost, automated parking management system powered by an **Arduino UNO (`ATmega328P`)**. Using dual **Active Infrared (IR) proximity sensors**, a **PWM-controlled Servo Motor**, an **I2C $16\times2$ LCD Display**, and a **DC piezoelectric buzzer**, the system achieves **$>95\%$ vehicle detection accuracy**, automates barrier gate actuation, prevents over-capacity entry with audio-visual alerts, and updates slot availability in real time.

---

## 🎯 Problem Statement & Urban Sustainability Impact

### Root Causes Addressed
* **Absence of Real-Time Vacancy Data:** Traditional manual parking lots force drivers to cruise blindly in search of open spaces, increasing urban traffic bottlenecks and carbon emissions.
* **High Cost of Commercial Smart Parking:** Camera-based deep learning and industrial WSN parking systems require expensive infrastructure that prevents adoption in developing urban areas.
* **Manual Gate & Capacity Mismanagement:** Unmonitored entry gates allow vehicles into already full parking lots, causing internal gridlock.

### Key Contributions
* **Automated Access Control:** Opens the barrier gate smoothly ($90^\circ \rightarrow 20^\circ$) only when vacant slots are available (`carCount < capacity`).
* **Real-Time Visual & Audio Feedback:** Continuously displays `Occupied` and `Vacant` slot counts on an I2C $16\times2$ LCD and triggers a `PARKING FULL / NO VACANCY` alarm via a buzzer when capacity is reached.
* **Ultra-Low-Cost Hardware Footprint:** Built entirely with off-the-shelf components for a total hardware investment of **BDT 1,560 (\~$13 USD)**.

---

## 🛠️ Hardware Components & Software Tools

| Category | Component / Tool | Technical Specification & Role in System |
| :--- | :--- | :--- |
| **Microcontroller Unit** | **Arduino UNO R3** | Powered by the **ATmega328P** ($16\text{ MHz}$ crystal oscillator, 14 digital I/O pins, 6 analog inputs); executes the real-time sensor polling and gate control loop |
| **Proximity Sensors** | **Active Infrared (IR) Sensors ($\times2$)** | Emits and detects reflected IR radiation (`Active LOW` trigger output); positioned at the entry (`Pin 2`) and exit (`Pin 4`) lanes with $>95\%$ detection precision |
| **Actuator** | **Micro Servo Motor (`SG90`)** | Closed-loop positional motor controlled via PWM (`Pin 3`); actuates the physical parking barrier between $90^\circ$ (closed) and $20^\circ$ (open) in $15\text{ ms}$ increments |
| **Visual Interface** | **I2C $16\times2$ LCD Display** | 16-character by 2-row liquid crystal display with an **I2C serial backpack (`0x27`)**, reducing wiring overhead to just 2 data pins (`SDA` / `SCL`) |
| **Audio Alert** | **DC Piezoelectric Buzzer** | Connected to Digital `Pin 5`; emits a $2\text{-second}$ high-decibel alert when a vehicle approaches a fully occupied parking lot |
| **Simulation & IDE** | **Arduino IDE, Proteus & Tinkercad** | Used for C++ firmware compilation, schematic design, virtual circuit verification, and hardware prototyping |

---

## 🔌 System Architecture & Pinout Configuration

```text
+-----------------------------------------------------------------------------+
|                     EXTERNAL ENVIRONMENT (PARKING LANE)                     |
|     [Approaching Vehicle]                        [Departing Vehicle]        |
+---------------+-------------------------------------------+-----------------+
                |                                           |
                v                                           v
     +---------------------+                     +---------------------+
     |  Entry IR Sensor    |                     |   Exit IR Sensor    |
     | (Active LOW: Pin 2) |                     | (Active LOW: Pin 4) |
     +----------+----------+                     +----------+----------+
                |                                           |
                +-------------------+   +-------------------+
                                    |   |
                                    v   v
+-----------------------------------------------------------------------------+
|                    ARDUINO UNO R3 (ATmega328P @ 16 MHz)                     |
|  • State Variables: capacity = 3 | carCount (0 to 3)                        |
|  • Debounce Flags : entryDetected | exitDetected                            |
|  • Decision Logic : Vacancy Check, Counter Increment/Decrement & Gate Timer |
+---------+---------------------------+-----------------------------+---------+
          |                           |                             |
          v                           v                             v
+-------------------+       +-------------------+         +-------------------+
|  I2C 16x2 LCD     |       |  PWM Servo Motor  |         |   DC Piezo Buzzer |
| (Addr: 0x27, I2C) |       |  (Digital Pin 3)  |         |  (Digital Pin 5)  |
| Displays Occupied |       | Smooth 90° <-> 20°|         | 2s Siren Alert on |
| & Vacant Slots    |       | Gate Actuation    |         | "PARKING FULL"    |
+-------------------+       +-------------------+         +-------------------+
```

### Hardware Pin Mapping Table

| Component | Module Pin | Arduino UNO Pin | Signal Type / Protocol |
| :--- | :--- | :--- | :--- |
| **Entry IR Sensor** | `OUT` | `Digital Pin 2` | Digital Input (`LOW` = Vehicle Detected) |
| **Servo Motor (Gate)** | `PWM / Signal` | `Digital Pin 3 (PWM)` | PWM Output ($90^\circ$ Closed $\leftrightarrow 20^\circ$ Open) |
| **Exit IR Sensor** | `OUT` | `Digital Pin 4` | Digital Input (`LOW` = Vehicle Detected) |
| **Alert Buzzer** | `VCC / (+)` | `Digital Pin 5` | Digital Output (`HIGH` = Alarm Active) |
| **I2C $16\times2$ LCD** | `SDA` / `SCL` | `A4 (SDA)` / `A5 (SCL)` | I2C Serial Communication (`Address: 0x27`) |
| **Power Rail** | `VCC` / `GND` | `5V` / `GND` | Common $5\text{V DC}$ Power Distribution |

---

## ⚙️ Operational Workflow & Control Algorithm

1. **System Initialization (`setup()`):**
   - Initializes the I2C $16\times2$ LCD at address `0x27`, enables the backlight, sets the Servo Motor to its closed default angle ($90^\circ$), and displays `"SMART PARKING / SYSTEM READY"` for $3\text{ seconds}$ before rendering the live slot counter (`Occupied: 0 | Vacant: 3`).
2. **Vehicle Entry Detection & Vacancy Check:**
   - When a vehicle triggers the Entry IR Sensor (`digitalRead(IR_ENTRY) == LOW`) and `entryDetected == false`:
     - **Case 1 — Slot Available (`carCount < capacity`):** Increments `carCount++`, smoothly sweeps the servo motor from $90^\circ$ to $20^\circ$ (`gateOpen()`), holds the gate open for $3\text{ seconds}$ (`delay(3000)`), sweeps the gate back to $90^\circ$ (`gateClose()`), and refreshes the LCD.
     - **Case 2 — Lot Full (`carCount == capacity`):** Keeps the gate closed, activates the buzzer (`digitalWrite(buzzer, HIGH)`), displays `"PARKING FULL / NO VACANCY"` on the LCD for $2\text{ seconds}$, and then restores the standard occupancy screen.
3. **Vehicle Exit Detection & Slot Release:**
   - When a departing vehicle triggers the Exit IR Sensor (`digitalRead(IR_EXIT) == LOW`) and `carCount > 0`, the system decrements `carCount--` (increasing available slots), actuates the servo gate open for $3\text{ seconds}$, closes the gate, and updates the LCD in real time.
4. **State Debouncing (`entryDetected` / `exitDetected`):**
   - Prevents multiple false counts from a single stationary vehicle by locking the sensor state until the IR beam returns to `HIGH`.

---

## 📊 Simulation, Experimental Results & Cost Analysis

### 1. Simulation & Physical Prototype Performance
The circuit was validated in **Proteus** and **Autodesk Tinkercad** prior to physical breadboard assembly:
* **Sensor Accuracy:** Achieved **$>95\%$ vehicle detection accuracy** across varying ambient lighting conditions.
* **Actuator Responsiveness:** Using a $15\text{ ms}$ per-degree step loop (`90°` $\leftrightarrow$ `20°`), the servo motor eliminated mechanical jerking and maintained reliable gate timing.
* **Real-Time Display Synchronization:** Zero-latency I2C updates ensured approaching drivers immediately saw accurate `Occupied` and `Vacant` counts.

### 2. Bill of Materials (BOM) & Cost Breakdown

| # | Hardware Component | Quantity | Unit Cost (BDT) | Total Cost (BDT) |
| :-: | :--- | :---: | :---: | :---: |
| 1 | **Arduino UNO R3 Microcontroller Board** | 1 | 790 | 790 |
| 2 | **Infrared (IR) Obstacle Avoidance Sensors** | 2 | 80 | 160 |
| 3 | **Micro Servo Motor (`SG90`)** | 1 | 140 | 140 |
| 4 | **I2C $16\times2$ Liquid Crystal Display (LCD)** | 1 | 350 | 350 |
| 5 | **DC Piezoelectric Buzzer** | 1 | 20 | 20 |
| 6 | **Jumper Wires & Interconnects** | 1 Set | 100 | 100 |
| | **Total Prototype Hardware Cost** | | | **BDT 1,560** |

---

## 🧱 Embedded C++ Firmware Implementation

<details>
<summary><b>🔍 Click to Expand: Complete Arduino C++ Source Code (<code>Program Code.cpp</code>)</b></summary>
<br>

```cpp
/*                 Smart Car Parking System (Final Version)           */
/**********************************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C display(0x27, 16, 2);
Servo gateServo;

// IR Sensors
int IR_ENTRY = 2;
int IR_EXIT  = 4;

// Buzzer
int buzzer = 5;

// Parking variables
int capacity = 3;
int carCount = 0;              // Cars currently inside

// Sensor flags
bool entryDetected = false;
bool exitDetected  = false;

void setup() {
  display.init();
  display.backlight();

  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_EXIT, INPUT);
  pinMode(buzzer, OUTPUT);

  gateServo.attach(3);
  gateServo.write(90); // Gate closed position

  display.clear();
  display.setCursor(0, 0);
  display.print("SMART PARKING");
  display.setCursor(0, 1);
  display.print("SYSTEM READY");
  delay(3000);
  display.clear();

  updateDisplay();
}

void loop() {

  /* ================= ENTRY ================= */
  if (digitalRead(IR_ENTRY) == LOW && !entryDetected) {
    entryDetected = true;

    if (carCount < capacity) {
      carCount++;               // Increase count
      gateOpen();               // Open gate
      delay(3000);              // Gate stays open for 3 seconds
      gateClose();              // Close gate
    } else {
      // Parking Full
      digitalWrite(buzzer, HIGH);
      display.clear();
      display.setCursor(0, 0);
      display.print(" PARKING FULL ");
      display.setCursor(0, 1);
      display.print(" NO VACANCY ");
      delay(2000);
      digitalWrite(buzzer, LOW);
    }
    updateDisplay();
  }

  if (digitalRead(IR_ENTRY) == HIGH) {
    entryDetected = false;
  }

  /* ================= EXIT ================= */
  if (digitalRead(IR_EXIT) == LOW && !exitDetected) {
    exitDetected = true;

    if (carCount > 0) {
      carCount--;               // Decrease count
      gateOpen();               // Open gate
      delay(3000);              // Gate stays open for 3 seconds
      gateClose();              // Close gate
    }
    updateDisplay();
  }

  if (digitalRead(IR_EXIT) == HIGH) {
    exitDetected = false;
  }
}

/* ================= LCD DISPLAY ================= */
void updateDisplay() {
  display.clear();
  display.setCursor(0, 0);
  display.print("Occupied: ");
  display.print(carCount);

  display.setCursor(0, 1);
  display.print("Vacant: ");
  display.print(capacity - carCount);
}

/* ================= GATE CONTROL ================= */
void gateOpen() {
  for (int pos = 90; pos >= 20; pos--) {   // Smooth open
    gateServo.write(pos);
    delay(15);
  }
}

void gateClose() {
  for (int pos = 20; pos <= 90; pos++) {   // Smooth close
    gateServo.write(pos);
    delay(15);
  }
}
```

</details>

---

## ⚠️ System Limitations & Future Scope

* **Current Prototype Limitations:**
  * **Single-Gate Bottleneck:** Relying on a single shared servo barrier for both entry and exit can cause queuing delays during peak traffic hours.
  * **Fixed Microcontroller I/O Capacity:** A standalone Arduino UNO limits the total number of individual slot-level sensors that can be wired without multiplexers.
  * **No Remote Cloud Sync:** Occupancy status is currently displayed locally on the I2C LCD without mobile app or cloud dashboard telemetry.
* **Future Enhancements:**
  * **IoT & Mobile App Integration:** Interface an `ESP8266` / `ESP32` Wi-Fi module to broadcast real-time slot availability to a smartphone app with pre-booking support.
  * **RFID & ANPR Automated Billing:** Integrate RFID tags or camera-based Automatic Number Plate Recognition (ANPR) for cashless toll deduction.
  * **Individual Slot Ultrasonic/IR Nodes:** Deploy per-slot sensors with LED guidance indicators for multi-story commercial parking garages.

---

## 📂 Repository File Structure

```text
Real-Time-Digital-Parking-System-Arduino/
├── Program Code.cpp                                                   # Complete Arduino Embedded C++ Firmware
├── Project-Report-Microprocessor Readl Time Digital Parking System.pdf # IEEE-Format Academic Research Report
└── README.md                                                          # Project Documentation
```

---

## 🚀 Hardware Setup & Execution Guide

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/<your-username>/Real-Time-Digital-Parking-System-Arduino.git
cd Real-Time-Digital-Parking-System-Arduino
```

### 2️⃣ Install Required Arduino Libraries
1. Open the **Arduino IDE**.
2. Go to **Sketch ➔ Include Library ➔ Manage Libraries...**
3. Search for and install:
   - `LiquidCrystal I2C` (by Frank de Brabander)
   - `Servo` (built-in standard library)

### 3️⃣ Upload Firmware to Arduino UNO
1. Rename or copy `Program Code.cpp` into an Arduino sketch (`SmartParking.ino`).
2. Connect your **Arduino UNO** via USB, select **Tools ➔ Board ➔ Arduino UNO**, and choose the active **COM Port**.
3. Click **Upload (`→`)**.

---

## 👥 Project Group Members

| # | Name | Student ID | Email |
| :-: | :--- | :---: | :--- |
| 1 | **Mir Moahtasim Billah Soykot** | `23-50442-1` | `23-50442-1@student.aiub.edu` |
| 2 | **Shahadat Hossain** | `23-51341-1` | `23-51341-1@student.aiub.edu` |
| 3 | **Hamidul Islam Hasib** | `23-50447-1` | `23-50447-1@student.aiub.edu` |
| 4 | **Zahin Tahiat Annesha** | `23-50414-1` | `23-50414-1@student.aiub.edu` |
| 5 | **Md Sadek Hosen** | `23-50435-1` | `23-50435-1@student.aiub.edu` |

---

<div align="center">
  <i>Developed for the Department of Computer Science and Engineering — American International University-Bangladesh (AIUB).</i>
</div>
