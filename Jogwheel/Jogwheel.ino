/**
   This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
*/
#include <BleKeyboard.h>
#include <ESP32Encoder.h>


/*
  connecting Rotary encoder
  CLK (A pin) - to any microcontroler intput pin with interrupt -> in this example pin 32
  DT (B pin) - to any microcontroler intput pin with interrupt -> in this example pin 21
  SW (button pin) - to any microcontroler intput pin -> in this example pin 25
  VCC - to microcontroler VCC (then set ROTARY_ENCODER_VCC_PIN -1) or in this example pin 25
  GND - to microcontroler GND
*/

#define JOG_BUTTON 20
#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 21
#define ROTARY_ENCODER_BUTTON_PIN 25
#define ROTARY_ENCODER_VCC_PIN -1 /*put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */
#define STOPSWITCH 6

ESP32Encoder encoder;
BleKeyboard bleKeyboard;
#define KEY_LEFT

int nbr = 0;

int readJogWheel() {
  int direction = 0;
  if (nbr != encoder.getCount()) {
    //   Serial.println("Encoder count = " + String((int32_t)encoder.getCount()));
    if (nbr > encoder.getCount()) direction = 1;
    else direction = -1;
    nbr = encoder.getCount();
  }
  return direction;
}

void setup() {
  Serial.begin(115200);

  pinMode(JOG_BUTTON, INPUT_PULLUP);

  // Attache pins for use as encoder pins
  encoder.attachSingleEdge(32, 21);
  encoder.clearCount();
  bleKeyboard.begin();
  Serial.println("Starting BLE work!");
}

void loop() {

  //  while (!digitalRead(STOPSWITCH));
  char key = 0;
  int dir = readJogWheel();
  if (dir < 0) key = KEY_LEFT_ARROW;
  if (dir > 0) key = KEY_RIGHT_ARROW;
  if (dir != 0) Serial.println(key, HEX);

  if (bleKeyboard.isConnected()) {
    if (digitalRead(JOG_BUTTON == HIGH)) bleKeyboard.write(key);
    else {
      switch (key) {
        case 0xD8:
          Serial.println("left");
          bleKeyboard.press(KEY_LEFT_SHIFT);
          bleKeyboard.press('J');
          delay(100);
          bleKeyboard.releaseAll();
          break;
        case 0xD7:
          Serial.println("right");
          bleKeyboard.press(KEY_LEFT_SHIFT);
          bleKeyboard.press('L');
          delay(100);
          bleKeyboard.releaseAll();
          break;
        case 0x00:
          Serial.println("zero");
          break;
        default:
          break;
      }
    }
  }
  delay(100);
}
