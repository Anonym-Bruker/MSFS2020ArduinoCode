
#include <Joystick.h>

Joystick_ Joystick;

int gearDown = 1;
int countMax = 100;
int count = countMax;

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 2;

// Last state of the button
int lastButtonState[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  // Initialize Button Pins
  setupPins();
  // Initialize Joystick Library
  Joystick.begin();
}


void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the
  // two serial line pins
  for (int i = 2; i <= 14; i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
}

void loop() {
  // Read pin values
  for (int index = 0; index < 13; index++)
  {
    int currentButtonState = 0;
    currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
 Joystick.setButton(14, digitalRead(A4));
 Joystick.setButton(15, digitalRead(A5));
 Joystick.setYAxis(analogRead(A0));
 Joystick.setXAxis(analogRead(A1));
 delay(50);
}
