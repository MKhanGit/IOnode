/* Author: Mohsin Khan 
IONode v1.1 Firmware

Control High Voltage Capable relay via 5v Serial Hardline || Serial BlueTooth control.

For schematics and Bill of Materials, visit https://github.com/MKhanGit/IOnode

Command Structure: <cmd byte><output n>

Example Serial line commands:
Toggle output 1
>: T1

Force output 3 LOW:
>: X3

Check output 2 state:
>: I2

Test Serial line:
>: P

*/

//Setup GPIO pin definitions
const int D[] = {13,2,3,4};
int D_size = sizeof(D) / sizeof(D[0]);

//Setup Serial BT Commands
const char CMD_TOGGLE = 'T';
const char CMD_INQUIRE = 'I';
const char CMD_HIGH = 'O';
const char CMD_LOW = 'X';
const char CMD_PING = 'P';

// Working variables for loop
char inByte;
int indexByte;
int STB_DLY = 300;

void setup() {
  // set up hardware serial line
  Serial.begin(9600);
  
  // Setup outputs and initilize to LOW
  for(int i=0; i<D_size; i++){
    pinMode(D[i], OUTPUT);
    digitalWrite(D[i],LOW);
    }
  
}

void loop() {
  // each loop checks for available commands, then runs through all bytes until the buffer is empty.
  while(Serial.available()){
    inByte=Serial.read();
    delay(STB_DLY); //stability delay
    
    switch (inByte) {
      // Based on first byte, drop to a specific case, before reading next byte in queue.
      case CMD_TOGGLE:
        // Read the next line in the queue, which should be an int representing the n-th output to affect (based on our syntax)
        if(Serial.available()){
          inByte=Serial.read();
          indexByte = inByte - '0';
          toggle(D, indexByte);
          }
        else{
          Serial.println("CMD received, no D Index given");
          }
       
        break;
        
      case CMD_INQUIRE:
        if(Serial.available()){
          inByte=Serial.read();
          indexByte = inByte - '0';
          Serial.println(digitalRead(D[indexByte]));
          }
        else{
          Serial.println("CMD received, no D Index given");
          }
        break;

      case CMD_HIGH:
        if(Serial.available()){
          inByte=Serial.read();
          indexByte = inByte - '0';
          digitalWrite(D[indexByte],HIGH);
          }
        else{
          Serial.println("CMD received, no D Index given");
          }
        break;
        
      case CMD_LOW:
        if(Serial.available()){
          inByte=Serial.read();
          indexByte = inByte - '0';
          digitalWrite(D[indexByte],LOW);
          }
        else{
          Serial.println("CMD received, no D Index given");
          }
        break;
        
      case CMD_PING:
        // Debug Command
        Serial.println("Pong!");   
        break;

      default:
        break;
      }
    
    }
    
    delay(STB_DLY);

}

// Generic toggle function, given array of outputs and index
void toggle(int D[], int i){
  digitalWrite(D[i],!digitalRead(D[i]));
  }
  
