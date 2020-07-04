/**
   This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
*/
#include <BleKeyboard.h>

/*
  connecting Rotary encoder
  CLK (A pin) - to any microcontroler intput pin with interrupt -> in this example pin 32
  DT (B pin) - to any microcontroler intput pin with interrupt -> in this example pin 21
  SW (button pin) - to any microcontroler intput pin -> in this example pin 25
  VCC - to microcontroler VCC (then set ROTARY_ENCODER_VCC_PIN -1) or in this example pin 25
  GND - to microcontroler GND
*/
#define UP_BUTTON 27
#define DOWN_BUTTON 26

BleKeyboard bleKeyboard;

bool keyPressed(byte pin) {
  bool keyStatus = false;
  if (!digitalRead(pin)) {
    while (!digitalRead(pin));
    keyStatus = true;
    delay(100);
  }
  return keyStatus;
}

void setup() {
  Serial.begin(115200);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  bleKeyboard.begin();
  Serial.println("Initialized");
}

void loop() {
  bool up = keyPressed(UP_BUTTON);
  bool down = keyPressed(DOWN_BUTTON);
  if (up) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    Serial.println("Volume up");
  }
  if (down) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    Serial.println("Volume down");
  }
  delay(100);
}
