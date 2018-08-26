/*

                ATTINY44 / ATTINY84
                      pinout

                  VCC -####- GND
               pin 10 -####- pin 0 - decoderA
                pin 9 -####- pin 1 - decoderB
                  RST -####- pin 2 - doesnt work with decoder?
 control pin3 - pin 8 -####- pin 3 - decoderC
 control pin2 - pin 7 -####- pin 4 - decoderD
 control pin1 - pin 6 -####- pin 5 - HES

*/

// decoder pins
const int pinDecA = 0;
const int pinDecB = 1;
const int pinDecC = 3;
const int pinDecD = 4;
const int decoderPins[] = { pinDecA, pinDecB, pinDecC, pinDecD };

// common pins control digit selection; LOW is on
const int pinC1 = 6;
const int pinC2 = 7;
const int pinC3 = 8;
const int controlPins[] = { pinC1, pinC2, pinC3 };

// Hall Effect Sensor
const int pinHES = 5;
