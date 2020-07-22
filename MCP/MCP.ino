#include <RotaryEncoder.h>
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_MULTI_AXIS,
  2, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  true, true,          // No rudder or throttle
  true, true, true);  // No accelerator, brake, or steering;

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(A2, A3);

unsigned long btn0Press = 0;
unsigned long btn1Press = 0;

void setup()
{
  //Serial.begin(57600);
  // Initialize Joystick Library
  Joystick.begin();
} 


// Read the current position of the encoder and print out when changed.
void loop()
{
   
  
  
  static int e1 = 0;
  encoder.tick();
  int e1New = encoder.getPosition();
  if (e1 != e1New) {
    if(e1New < e1) { 
      Joystick.setButton(0, 1);
      btn0Press = millis();
      //Serial.println("Down");
    }
    if(e1New > e1) {
      Joystick.setButton(1, 1);
      btn1Press = millis();
      //Serial.println("Up"); 
    }

    // Set back to unpressed 
    e1 = e1New;
  }

  
    if((millis() - btn0Press) >= 50) {
      //Serial.println("Btn 1 off");
      Joystick.setButton(0,0);
    }
    if((millis() - btn1Press) >= 50) {
      Joystick.setButton(1,0);
    }
}
