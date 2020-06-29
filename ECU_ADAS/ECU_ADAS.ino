#include <SPI.h> //Library for communication between Arduino and CAN Shield
#include <mcp_can.h> //MCP2515 chip control
#include <Servo.h> //Servo management
#include <LiquidCrystal.h> //LCD management

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
byte angle;
unsigned int canID;
Servo servo;
int servoPin = 3; //It has to be a PWM pin
LiquidCrystal lcd(14,15,16,17,18,19);

//-------------------------------------------------------------------------------------

void setup()
{
  //Serial
  SERIAL.begin(115200); //To communicate through Serial monitor to serial console
  //LCD
  lcd.begin(16,2);
  lcd.print("ANGULO VOLANTE:");
  // Servo
  servo.attach(servoPin);
  //CAN Bus
  while(CAN_OK != CAN.begin(CAN_500KBPS)) // Setting CAN baud rate
  { 
    SERIAL.println("CAN Bus Shield not connected, restarting...");
    delay(100);
  }
  SERIAL.println("CAN Bus Shield connected!");
  }

//-------------------------------------------------------------------------------------


void loop()
{
    if(CAN_MSGAVAIL == CAN.checkReceive()) //Checking if data is received through CAN Bus
    {
      
        CAN.readMsgBuf(&messageLength, buf); //Reading received CAN message
        canID = CAN.getCanId(); //Getting the ID of the incoming message
        angle = (int) buf[0]; //Getting the servo angle from the message
        servo.write(angle); //Writing angle to servo
        printLCD(angle); //LCD Monitor
        //serialCANDebug(canID,messageLength); //Serial Debug
    }
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


void printLCD(int value) //Function that prints a value on the LCD without refreshing problems
{
  lcd.setCursor(8,1);
  lcd.print(value);
  if (value < 10) lcd.print("   ");                 
  else if (value < 100) lcd.print("  ");
  else if (value < 1000) lcd.print(' ');
}