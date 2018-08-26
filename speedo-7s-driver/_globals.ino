

// reader..

// wheel measurements
//                      radius == 12.1"
//              diameter (r*2) =~ 24.2" 61.47
//              diameter in cm = 61.47cm 
// circumfrence in cm (pi*r*2) =~ pi*61.47cm = 193.11cm
//
// 160934.4 cm per mile. * 100 = 16093440
//
// 16093440  / circumference = rotations per hour
//
// so: 16093440 / 193 =~ 83385
//
//
// 83385 / 60 / 60 = revolutions per second
//
// max RPS = 23.16 rps

// number of pulses over 1 mile
//
// wheel circumference = 1931mm
// 1 mile in mm = 1609344
// 
// 1 mile / wheel circumference = pulses per mile
// 1609344 / 1931 =~ 833.42 
// 
// MPH = distance in milimeters / (avgMs * pulses per mile)

// hall effect sensor config
/*
byte oldSwitchState = LOW;
//const unsigned long debounceTime = 10;
unsigned long switchCloseTime;
long countHESOpen;
long countHESClosed;
int mph;
int revolutions = 0;
int timer = 0;
int elapsedTime;
*/


#include <CircularBuffer.h>

CircularBuffer<unsigned int,8> buffer;

unsigned int previousMs;
unsigned int currentMs;
unsigned int revolutionMs;
unsigned int sensorState;
unsigned int mph;
unsigned int displayTimer;

// at 100mph, 1 rotation takes: 1000ms / 23.16rps =~ 44ms
// if we get a read more often than ~44ms then disregard it.
int debounceHESMs = 45;


// these values are reversed so they are written to the correct pins
const int digits[10][4] = {
  { 0,0,0,0 },  // = 0
  { 1,0,0,0 },  // = 1
  { 0,1,0,0 },  // = 2
  { 1,1,0,0 },  // = 3
  { 0,0,1,0 },  // = 4
  { 1,0,1,0 },  // = 5
  { 0,1,1,0 },  // = 6
  { 1,1,1,0 },  // = 7
  { 0,0,0,1 },  // = 8
  { 1,0,0,1 }   // = 9
};
