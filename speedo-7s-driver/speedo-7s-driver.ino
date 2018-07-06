// LED speed-o-meter
//
// inspiration
// http://www.instructables.com/id/Bike-Speedometer/
//
// hs320401k-24 3 digit
// http://www.marthel.pl/katalog/Betlux/BL-T52A-31.pdf
//
// 7447 7SD decoder
// https://www.electroschematics.com/wp-content/uploads/2013/01/7447-datasheet.pdf

#include <math.h>

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

// decoder pins
int pinDecA = 3;
int pinDecB = 4;
int pinDecC = 5;
int pinDecD = 6;

int decoderPins[] = { pinDecA, pinDecB, pinDecC, pinDecD };

// reed switch
int pinReed = 2;

// NOTE: the dot (DP) pin is ignored since it's unused in this program
//int dispPins[] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG };

// common pins control digit selection; LOW is on
int pinC1 = 10; // 12
int pinC2 = 11; // 9
int pinC3 = 12; // 8

int controlPins[] = { pinC1, pinC2, pinC3 };

int digits[10][4] = {
  { 0,0,0,0 },  // = 0
  { 0,0,0,1 },  // = 1
  { 0,0,1,0 },  // = 2
  { 0,0,1,1 },  // = 3
  { 0,1,0,0 },  // = 4
  { 0,1,0,1 },  // = 5
  { 0,1,1,0 },  // = 6
  { 0,1,1,1 },  // = 7
  { 1,0,0,0 },  // = 8
  { 1,0,0,1 }   // = 9
};

// reed switch config
int switchPin = 2;
byte oldSwitchState = HIGH;
const unsigned long debounceTime = 10;
unsigned long switchPressTime;
int reedCount;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(57600);
  Serial.println("initializing...");

  //for (int i; i != (sizeof(dispPins) / 2); i++) {
  //  pinMode(dispPins[i], OUTPUT);
  //}

  for (int i; i != (sizeof(controlPins) / 2); i++) {
    pinMode(controlPins[i], OUTPUT);
  }

  for (int i; i != (sizeof(decoderPins) / 2); i++) {
    pinMode(decoderPins[i], OUTPUT);
  }

  pinMode(switchPin, INPUT_PULLUP);
}


void posNum(int pos, int num) {
  setPos(pos);
  setNum(num);
}

void setPos(int pos) {
  switch(pos) {
    case 1:
      digitalWrite(pinC1, HIGH);
      digitalWrite(pinC2, LOW);
      digitalWrite(pinC3, LOW);
      break;
    case 2:
      digitalWrite(pinC1, LOW);
      digitalWrite(pinC2, HIGH);
      digitalWrite(pinC3, LOW);
      break;
    case 3:
      digitalWrite(pinC1, LOW);
      digitalWrite(pinC2, LOW);
      digitalWrite(pinC3, HIGH);
      break;
  }
}

void setNum(int num) {
  for (int i = 0; i != 4; i++) {
    digitalWrite(decoderPins[i], digits[num][i]);
  }
}

//void setNum(int num) {
//  switch(num) {
//    case 0:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  HIGH);
//      digitalWrite(pinE,  HIGH);
//      digitalWrite(pinF,  HIGH);
//      digitalWrite(pinG,  LOW);
//      break;
//    case 1:
//      digitalWrite(pinA,  LOW);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  LOW);
//      digitalWrite(pinE,  LOW);
//      digitalWrite(pinF,  LOW);
//      digitalWrite(pinG,  LOW);
//      break;
//    case 2:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  LOW);
//      digitalWrite(pinD,  HIGH);
//      digitalWrite(pinE,  HIGH);
//      digitalWrite(pinF,  LOW);
//      digitalWrite(pinG,  HIGH);
//      break;
//    case 3:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  HIGH);
//      digitalWrite(pinE,  LOW);
//      digitalWrite(pinF,  LOW);
//      digitalWrite(pinG,  HIGH);
//      break;
//    case 4:
//      digitalWrite(pinA,  LOW);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  LOW);
//      digitalWrite(pinE,  LOW);
//      digitalWrite(pinF,  HIGH);
//      digitalWrite(pinG,  HIGH);
//      break;
//    case 5:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  LOW);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  HIGH);
//      digitalWrite(pinE,  LOW);
//      digitalWrite(pinF,  HIGH);
//      digitalWrite(pinG,  HIGH);
//      break;
//    case 6:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  LOW);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  HIGH);
//      digitalWrite(pinE,  HIGH);
//      digitalWrite(pinF,  HIGH);
//      digitalWrite(pinG,  HIGH);
//      break;
//    case 7:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  LOW);
//      digitalWrite(pinE,  LOW);
//      digitalWrite(pinF,  LOW);
//      digitalWrite(pinG,  LOW);
//      break;
//    case 8:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  HIGH);
//      digitalWrite(pinE,  HIGH);
//      digitalWrite(pinF,  HIGH);
//      digitalWrite(pinG,  HIGH);
//      break;
//    case 9:
//      digitalWrite(pinA,  HIGH);
//      digitalWrite(pinB,  HIGH);
//      digitalWrite(pinC,  HIGH);
//      digitalWrite(pinD,  HIGH);
//      digitalWrite(pinE,  LOW);
//      digitalWrite(pinF,  HIGH);
//      digitalWrite(pinG,  HIGH);
//      break;
//  }
//}

void num(int num) {
  // 3 <= 3 yes
  // 2 <= 3 yes 
  // 1 <= 3 yes
  //
  // 3 <= 2 no
  // 2 <= 2 yes
  // 1 <= 2 yes
  //
  // 3 <= 1 no
  // 2 <= 1 no
  // 1 <= 1 yes
  int nl = numLength(num);

  for (int i = 3; i > 0; i--) {
    //Serial.println(i);
    //Serial.println(nl);
    //Serial.println();
    //if (i <= nl) {    
    posNum(i, (num % 10));
    //}
    num /= 10;
    delay(5);
  }
}

//void clearDisp() {
//  for (int i; i != (sizeof(dispPins) / 2); i++) {
//    digitalWrite(dispPins[i], LOW);
//  }
//}

void demoCount(int count) {
  for (int i; i < count; i++) {
    num(i);
    delay(10);
  }
}

void demoLEDTest() {
  for (int i; i < 10; i++) {
    //int a = (i * 10) * i;
    //int b = (b * 10) * i;
    num(i);
    delay(100);
    //Serial.println(i);
  }
}

void reedSwitchDemo() {
  byte switchState = digitalRead(switchPin);
  if (switchState != oldSwitchState) {
    if (millis() - switchPressTime >= debounceTime) {
      switchPressTime = millis();
      oldSwitchState = switchState;
      if (switchState == LOW) {
        Serial.println("Switch closed.");
      } else {
        Serial.println("Switch opened.");
      }
      reedCount++;
      Serial.println(reedCount);
    }
  }
}

int numLength(int i)
{
  if (i > 99) {
    return 3;
  } else if (i > 9) {
    return 2;
  } else {
    return 1;
  }
}

void loop() {
  demoLEDTest();
  //demoCount(99);
  //num(1);
  //delay(10000);
}
