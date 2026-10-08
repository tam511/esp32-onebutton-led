#include <Arduino.h>
#include <OneButton.h>

#define LED1_PIN 2
#define LED2_PIN 19
#define BUTTON_PIN 4

OneButton btn(BUTTON_PIN, true, true);

enum ActiveLED { SELECT_LED1, SELECT_LED2 };
ActiveLED currentLED = SELECT_LED1;

bool led1State = false;
bool led2State = false;

unsigned long lastBlinkTime = 0;
bool blinkToggle = false;

void handleDoubleClick() {
  currentLED = (currentLED == SELECT_LED1) ? SELECT_LED2 : SELECT_LED1;
}

void handleClick() {
  if (currentLED == SELECT_LED1) {
    led1State = !led1State;
    digitalWrite(LED1_PIN, led1State ? HIGH : LOW);
  } else {
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State ? HIGH : LOW);
  }
}

void handleDuringLongPress() {
  if (millis() - lastBlinkTime >= 200) {
    lastBlinkTime = millis();
    blinkToggle = !blinkToggle;
    
    int activePin = (currentLED == SELECT_LED1) ? LED1_PIN : LED2_PIN;
    digitalWrite(activePin, blinkToggle ? HIGH : LOW);
  }
}

void handleLongPressStop() {
  digitalWrite(LED1_PIN, led1State ? HIGH : LOW);
  digitalWrite(LED2_PIN, led2State ? HIGH : LOW);
  blinkToggle = false;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  btn.attachDoubleClick(handleDoubleClick);
  btn.attachClick(handleClick);
  btn.attachDuringLongPress(handleDuringLongPress);
  btn.attachLongPressStop(handleLongPressStop);
}

void loop() {
  btn.tick();
}