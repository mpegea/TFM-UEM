#include <SPI.h> //Library for communication between Arduino and CAN Shield
#include <mcp_can.h> //Library for MCP2515 control

// Compatibilidad con Arduinos ARM SAMD*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
#define SERIAL Serial
#endif

//Global variables
MCP_CAN CAN(9); //Set SPI Chip Select to pin 9 for Arduino UNO
unsigned char messageLength = 0;
byte buf[8];
byte command;
unsigned int canID;
int autonomous_mode = 0; // 1 Enabled, 0 Disabled
int const potentiometerPin = A0; //It has to be an analog pin
int potentiometerValue;
byte mappedValue = 0;
byte data[8]; //Array that contains the message to be sent through CAN Bus
int side = 1; // 1 Left->Right, -1 Right->Left
const int ledPin = 2; //Autopilot LED


//-------------------------------------------------------------------------------------

void setup()
{
  // Serial
  SERIAL.begin(115200); //To communicate through Serial monitor to serial console
  // CAN Bus
  while (CAN_OK != CAN.begin(CAN_500KBPS)) // Setting CAN baud rate
  {
    SERIAL.println("CAN Bus Shield not connected, restarting...");
    delay(100);
  }
  SERIAL.println("CAN Bus Shield connected!");
  //LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

//-------------------------------------------------------------------------------------

void loop()
{
  if(CAN_MSGAVAIL == CAN.checkReceive()) //Checking if data is received through CAN Bus
    {
        CAN.readMsgBuf(&messageLength, buf); //Reading received CAN message
        canID = CAN.getCanId(); //Getting the ID of the incoming message
        SERIAL.println(canID, HEX);
        if(canID == 0x111) //CAN Message from Autopilot ECU
        {
          command = buf[0];
          if(command == 0xAA){ //AA to activate, DD to deactivate autonomous mode
            autonomous_mode=1;
            digitalWrite(ledPin , HIGH);
            }
            else{
              autonomous_mode=0;
              digitalWrite(ledPin, LOW);
              }
          SERIAL.print("Autonomous mode: ");
          SERIAL.println(autonomous_mode);
        }
    }
  if(autonomous_mode){ // In autonomous mode, this controlls the direction
    if(side == 1){ //Right Direction
      if (mappedValue < 160){
        mappedValue = mappedValue + 10;
        }
        else{
              side = -1;
          }
    }
    else { //Left Direction
      if (mappedValue > 20){
        mappedValue = mappedValue - 10;
        }
        else{
              side = 1;
          }
      }
  }
  else{ // Autonomous mode Disabled
      // Reading Sensor Data
      potentiometerValue = analogRead(potentiometerPin);
      mappedValue = map(potentiometerValue, 0, 1023, 0, 179); //Mapping analog data to the range of the servo
    }
  
  data[0] = mappedValue;
  CAN.sendMsgBuf(0x222, 0, 8, data); //CAN.sendMsgBuf(msg ID, extended, number of data bytes, data array)
  //Serial.println(mappedValue); //Potentiometer Serial Debug
  delay(50); //Delay between messages
}

//-------------------------------------------------------------------------------------

// Functions

void serialCANDebug(unsigned int canID, unsigned char messageLength) //Function that writes by serial monitor the proporties of a given CAN message
{
  SERIAL.print("ID is: ");
  SERIAL.print(canID, HEX);
  SERIAL.print("    Length is: ");
  SERIAL.println(messageLength);
  for(int i = 0; i<messageLength; i++)
  {
    SERIAL.print(buf[i]);
  }
  SERIAL.println("\n\n**********************************\n");
}
