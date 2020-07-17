/*
   Displays text sent over the serial port (e.g. from the Serial Monitor) on
   an attached LCD.
   YWROBOT
  Compatible with the Arduino IDE 1.0
  Library version:1.1
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
RotaryEncoder encoder(A2, A3);

String line1Buff;
String line2Buff;
String line3Buff;
String line4Buff;
char readBuffer;

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{
while(Serial.available() > 0 ){
    line3Buff = Serial.readString();
    UpdateScreen();
}
  
  // when characters arrive over the serial port...
  //line3Buff = Serial.readString();
  //UpdateScreen();
  
  //if (Serial.available()) {
    // wait a bit for the entire message to arrive
    // clear the screen
    //lcd.clear();
    // read all the available characters
  //  while (Serial.available() > 0) {
      // display each character to the LCD

   //   String cmd = Serial.readString();

      //String type = getValue(cmd, '|', 0);
      //String prop = getValue(cmd, '|', 1);
      //String val = getValue(cmd, '|', 2);

   //   if(cmd == "Boeing 737 Controller") {
        //lcd.clear();
        //lcd.print(cmd); 
    //  } else {
        //line3Buff = cmd;
        //UpdateScreen();
    //  }
   // }
  //}

  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos != newPos) {
    String cmd;
    if (newPos > pos) {
      cmd = "C|MCPSPEED|1";
    } else {
      cmd = "C|MCPSPEED|-1";
    }
    Serial.print(cmd + "#");
    line1Buff = cmd;
    //UpdateScreen();
    pos = newPos;
  }
}

void UpdateScreen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SND: " + line1Buff);  
  lcd.setCursor(0,1);
  lcd.print(line2Buff); 
  lcd.setCursor(0,2);
  lcd.print("REC: " + line3Buff); 
  lcd.setCursor(0,3);
  lcd.print(line4Buff);   
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
