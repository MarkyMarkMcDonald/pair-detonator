/* Buttons to USB Keyboard Example

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

Bounce button0 = Bounce(0, 10);
Bounce button1 = Bounce(1, 10);  // 10 = 10 ms debounce time

#define READY 1
#define DISENGAGED_0 2
#define DISENGAGED_1 3
#define ARMED_0 4
#define ARMED_1 5
#define FIRE 6

int state = READY;

int led = 13;

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  button0.update();
  button1.update();

  if (state == READY) { 
    if (button0.fallingEdge()) {
      state = ARMED_0;
    } else if (button1.fallingEdge()) {
      state = ARMED_1;
    }    
  } else if (state == ARMED_0 && button1.fallingEdge()) {
    state = FIRE;
    Keyboard.println("");
  } else if (state == ARMED_1 && button0.fallingEdge()) {
    state = FIRE;
    Keyboard.println("");
  } else if (state == DISENGAGED_0 && button1.risingEdge()) {
    state = READY;
  } else if (state == DISENGAGED_1 && button0.risingEdge()) {
    state = READY; 
  } else if (state == FIRE) {
    if (button0.risingEdge()) {
      state = DISENGAGED_0; 
    } else if (button1.risingEdge()) {
      state = DISENGAGED_1;
    }
  }
  digitalWrite(led, state == ARMED_0 || state == ARMED_1 || state == FIRE ? HIGH : LOW);
}

