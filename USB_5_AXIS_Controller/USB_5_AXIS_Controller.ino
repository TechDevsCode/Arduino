//
// Pin A0 = CLUTCH
// Pin A1 = BRAKE
// Pin A2 = THROTTLE
//
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_MULTI_AXIS,
  1, 0,                  // Button Count, Hat Switch Count
  false, false, true,     // X and Y, but no Z Axis
  true, true, false,   // No Rx, Ry, or Rz
  true, true,          // No rudder or throttle
  false, true, false);  // No accelerator, brake, or steering;

  int _throttle = 0;
  int _brake = 0;
  int _clutch = 0;
  int _Rx = 0;
  int _Ry = 0;
  int _Rbtn = 0;
  
  int lastButtonState[1] = {0};

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 2;

const bool initAutoSendState = true; 

void setup()
{
      pinMode(2, INPUT_PULLUP);  
      Joystick.begin();
}
   
void loop(){
  _throttle = analogRead(A1);  
  _clutch = analogRead(A0);
  _brake = analogRead(A2);
  _Rx = analogRead(A4);
  _Ry = analogRead(A5);
  
   Joystick.setThrottle(_throttle);
   Joystick.setBrake(_brake);
   Joystick.setZAxis(_clutch);
   Joystick.setRxAxis(_Rx);
   Joystick.setRyAxis(_Ry);
  
  // Read pin values
  for (int index = 0; index < 1; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
   
  delay (50);
}

//AMSTUDIO Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
