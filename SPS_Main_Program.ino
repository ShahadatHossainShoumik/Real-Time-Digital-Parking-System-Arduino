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
      delay(3000);              // ⏱ Gate stays open for 3 seconds
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
      delay(3000);              // ⏱ Gate stays open for 3 seconds
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
