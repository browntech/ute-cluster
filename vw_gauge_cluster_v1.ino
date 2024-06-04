//Modifed from VSS converter from civic eg vss to s2000 cluster
//Version 1.0
//read.the.disclaimer@gmail.com

#include <TimerOne.h> // This library will allow us to use pwm signals with custom period
// Required for CANBus
// https://github.com/coryjfowler/MCP_CAN_lib/blob/master/examples/CAN_send/CAN_send.ino#L17
#include <SPI.h>                //CAN Bus Shield SPI Pin Library
#include "mcp_can.h"

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
long speedMap[] = {
  0,      // 0
  260000, // 1
  141000, // 5
  63000, // 10
  42000, // 15
  31000, // 20
  24500, // 25
  20500, // 30
  17500, // 35
  15500, // 40
  14000, // 45
  13000, // 50
  11000, // 60
  9400,  // 70
  8100,  // 80
  7500,  // 85
  7200,  // 90
  6800,  // 95
  6500,  // 100
  6200,  // 105
  5900,  // 110
  5660,  // 115
  5430,  // 120
  5220,  // 125
  5010,  // 130
  4830,  // 135
  4650,  // 140
  4500,  // 145
  4350,  // 150
  4220,  // 155
  4080   // 160
};
int speedSize = 5;
unsigned long pulseDelay = 0;
//ToDo:
// Build out complete speed map above
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

  //Immobilizer
  canSend(0x3D0, 0, 0x80, 0, 0, 0, 0, 0, 0);
  
  //Engine on and ESP enabled
  canSend(0xDA0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

  //Airbag
  canSend(0x050, 0, 0x80, 0, 0, 0, 0, 0, 0);

  // Verify gauge operation
  wipeGauges();
}

void canSend(short address, byte a, byte b, byte c, byte d, byte e, byte f, byte g, byte h)//function to send CAN-commands
{
  unsigned char DataToSend[8] = {a,b,c,d,e,f,g,h};//array storing a small buffer
  CAN.sendMsgBuf(address, 0, 8, DataToSend);      //sending the buffer using the given adress
}

void wipeGauges() {
  // Set Speedometer to highest value
  Timer1.pwm(vssOut, (55.0 / 100) * 1023,speedMap[30]);
  
  // Set RPM to highest value
  tempRPM = 7500*4;
  rpmL = lo8(tempRPM);
  rpmH = hi8(tempRPM);

  for (int i = 0; i < 1500; i++) {
    canSend(0x280, 0x49, 0x0E, rpmL, rpmH, 0x0E, 0x00, 0x1B, 0x0E);
    delay(2);
  }

  // Wait while needles up
  // delay(3000);
  // Return to 0
  Timer1.pwm(vssOut,0,0);

  return;
}

void readCAN() {
  return;
}

void updateGauges() {
  return;
}
 
void loop(){
  // Startup 
  
  // Set RPM gauge to highest value
  tempRPM = 927*4;
  rpmL = lo8(tempRPM);
  rpmH = hi8(tempRPM);
  // canSend(0x280, 0x49, 0x0E, rpmL, rpmH, 0x0E, 0x00, 0x1B, 0x0E);


  // updateGauges();
  // tempRPM = rpm*4;
  // rpmL = lo8(tempRPM);
  // rpmH = hi8(tempRPM);
  // //RPM
  // CanSend(0x280, 0x49, 0x0E, rpmL, rpmH, 0x0E, 0x00, 0x1B, 0x0E);
}