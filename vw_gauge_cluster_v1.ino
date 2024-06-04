//Modifed from VSS converter from civic eg vss to s2000 cluster
//Version 1.0
//read.the.disclaimer@gmail.com

#include <TimerOne.h> // This library will allow us to use pwm signals with custom period
// Required for CANBus
// https://github.com/coryjfowler/MCP_CAN_lib/blob/master/examples/CAN_send/CAN_send.ino#L17
#include <SPI.h>                //CAN Bus Shield SPI Pin Library
#include "mcp_can.h"
// Speed Map because I'm bad at math
#include "speedmap.h"

// CANBus Pin setup
#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN(10);                                // Set CS pin

int vssOut = 9;
double scale=0;
unsigned long durationHigh=0; //duration of the pulse in High zone (5v)
unsigned long durationLow=0; //duration of the pulse in Low zone (0v)
unsigned long period=0;
unsigned long duty=0;
int pack_counter = 0;
int speedSize = 5;
unsigned long pulseDelay = 0;
//ToDo:
// Figure out how to actuate temp gauge
// Figure out how to read speed
// Figure out how to read RPM
// Figure out how to read temp
// Figure out how to turn on and off low oil light
// Figure out how to increment odometer


// RPM Vars
//Definition
#define lo8(x) ((int)(x)&0xff)
#define hi8(x) ((int)(x)>>8)
int rpm=0;
short tempRPM = 0;
byte rpmL = 0;
byte rpmH = 0;

void setup(){
  pinMode(vssOut, OUTPUT); //sets the pin as output 
  Serial.begin(115200);  
  Timer1.initialize(); //initializing the Timer1, so we can use pwm function
  // Initialize CANController
  if(CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted

  // //Immobilizer
  // canSend(0x3D0, 0, 0x80, 0, 0, 0, 0, 0, 0);
  
  // //Engine on and ESP enabled
  // canSend(0xDA0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

  // //Airbag
  // canSend(0x050, 0, 0x80, 0, 0, 0, 0, 0, 0);

  // Verify gauge operation
  delay(1000);
  wipeGauges();
}

void canSend(short address, byte a, byte b, byte c, byte d, byte e, byte f, byte g, byte h)//function to send CAN-commands
{
  unsigned char DataToSend[8] = {a,b,c,d,e,f,g,h};//array storing a small buffer
  CAN.sendMsgBuf(address, 0, 8, DataToSend);      //sending the buffer using the given adress
}

void setSpeed(int speed) {
  Timer1.pwm(vssOut, 512, speedMap[speed]);
}

void setRPM( int rpm ) {
  tempRPM = rpm*4;
  rpmL = lo8(tempRPM);
  rpmH = hi8(tempRPM);
  canSend(0x280, 0x49, 0x0E, rpmL, rpmH, 0x0E, 0x00, 0x1B, 0x0E);
}

void wipeGauges() {
  Serial.println("Starting wipe gauges");
  // Set Speedometer to highest value
  setSpeed(160);

  // Set RPM to highest value
  for (int i = 0; i < 800; i++) {
    setRPM(7700);
    delay(2);
  }
  delay(200); // Adjust this so your needles return at the same time.

  setSpeed(0);
  Serial.println("Finished wipe gauges");

  return;
}

void readCAN() {
  return;
}

void updateGauges() {
  return;
}
 
void loop(){
  setSpeed(0);
  setRPM(3523);
}