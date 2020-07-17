/* Simple Serial ECHO script : Written by ScottC 03/07/2012 */

/* Use a variable called byteRead to temporarily store the data coming from the computer */
byte byteRead;
byte inData[24]; // Make this big enough to hold the entire event

byte buff[6];
int index = 0;

void setup() {                
// Turn the Serial Protocol ON
  Serial.begin(9600);
}

void loop() {  
  handleMessages();
}

void handleMessages() {
  if (Serial.available()) {
    // Ready bytes into the buffer  
    byte iByte = Serial.read();
    buff[index++] = iByte;   
    // If we get a message ending byte then handle the message
    if(iByte == 10) {  
      if(buff[0] == 0x5e) { handleCommand(); }
      if(buff[0] == 0x25) { handleValue(); }
      resetBuffer();
    }
  }
}

void resetBuffer() {
      index = 0;
      memset(buff, 0, 3);
}

void handleCommand() {
  byte command = buff[1];
  if(command == 0x41) {
    Serial.println("COMMAND.MCP_SPEED_UP");
  }
  if(command == 0x42) {
    Serial.println("COMMAND.MCP_SPEED_DOWN");
  }
  if(command == 0x43) {
    Serial.println("COMMAND.MCP_ALT_UP");
  }
}

void handleValue() {
  byte property = buff[1];
  byte value = buff[2] - 'O';

  Serial.print("Property: ");
  Serial.print(property, HEX);
  Serial.println("");
  Serial.print("Value: ");
  Serial.print(value, HEX);
}
