#include <Arduino.h>
#include <OneButton.h>

// Khai báo nút nhấn và LED từ platformio.ini
OneButton button(BTN_PIN, (BTN_ACT == LOW), true);

enum LedState {
  LED_OFF,
  LED_ON,
  LED_BLINKING
};

LedState currentLedState = LED_OFF;
unsigned long lastBlinkTime = 0;
const unsigned long BLINK_INTERVAL = 200; // Tần số nháy LED (ms)
bool rawLedState = false;

// Hàm điều khiển xuất mức điện áp ra LED (tương thích cả Active LOW lẫn Active HIGH)
void setLedHardwareState(bool turnOn) {
  if (LED_ACT == LOW) {
    digitalWrite(LED_PIN, turnOn ? LOW : HIGH);
  } else {
    digitalWrite(LED_PIN, turnOn ? HIGH : LOW);
  }
}

// 1. Single Click -> Bật / Tắt (ON / OFF)
void handleSingleClick() {
  if (currentLedState == LED_OFF) {
    currentLedState = LED_ON;
    setLedHardwareState(true);
    Serial.println("Single Click: LED ON");
  } else {
    currentLedState = LED_OFF;
    setLedHardwareState(false);
    Serial.println("Single Click: LED OFF");
  }
}

// 2. Double Click -> Nháy LED (BLINKING)
void handleDoubleClick() {
  if (currentLedState != LED_BLINKING) {
    currentLedState = LED_BLINKING;
    Serial.println("Double Click: LED BLINKING");
  } else {
    currentLedState = LED_OFF;
    setLedHardwareState(false);
    Serial.println("Double Click: LED OFF");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  setLedHardwareState(false); // Ban đầu tắt LED

  // Gán các sự kiện cho OneButton
  button.attachClick(handleSingleClick);
  button.attachDoubleClick(handleDoubleClick);
}

void loop() {
  // Cập nhật trạng thái nút nhấn
  button.tick();

  // Xử lý nháy LED (non-blocking)
  if (currentLedState == LED_BLINKING) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= BLINK_INTERVAL) {
      lastBlinkTime = currentMillis;
      rawLedState = !rawLedState;
      setLedHardwareState(rawLedState);
    }
  }
}