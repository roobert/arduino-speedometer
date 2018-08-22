

// these values are reversed so they are written to the correct pins
int digits[10][4] = {
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


// LEDs: A-F clockwise from top; G is the bar; DP is the dot; HIGH is on
// NOTE: pin D13 is used as output rather than input since it's connected
// to the board LED which makes input from the reed switch fail to be read

//             Arduino |  LED Disp. |  7447
// int pinA  = 13;     // 11        // 13
// int pinB  = 3;      // 7         // 12
// int pinC  = 4;      // 4         // 11
// int pinD  = 5;      // 2         // 10
// int pinE  = 6;      // 1         // 9
// int pinF  = 7;      // 10        // 15
// int pinG  = 8;      // 5         // 14
// int pinDP = 9;      // 3         //

// decoder pins - for breadboard version with arduino nano
int pinDecA = 3;
int pinDecB = 4;
int pinDecC = 5;
int pinDecD = 6;

// decoder pins - for attiny84
/*
int pinDecA = 0;
int pinDecB = 1;
int pinDecC = 3;
int pinDecD = 4;
*/

int decoderPins[] = { pinDecA, pinDecB, pinDecC, pinDecD };

// Hall Effect Sensor
int pinHES = 2; // arduino
//int pinHES = 6; // attiny

// NOTE: the dot (DP) pin is ignored since it's unused in this program
//int dispPins[] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG };

// common pins control digit selection; LOW is on - arduino nano
int pinC1 = 10; // 12
int pinC2 = 11; // 9
int pinC3 = 12; // 8

// common pins control digit selection; LOW is on - attiny84
/*
int pinC1 = 6; // 12
int pinC2 = 7; // 9
int pinC3 = 8; // 8
*/

int controlPins[] = { pinC1, pinC2, pinC3 };
