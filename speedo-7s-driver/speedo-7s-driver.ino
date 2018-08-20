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
// works with anode display


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
/*
int pinDecA = 6;
int pinDecB = 5;
int pinDecC = 4;
int pinDecD = 3;
*/

// decoder pins - for attiny84
int pinDecA = 0;
int pinDecB = 1;
int pinDecC = 3;
int pinDecD = 4;

int decoderPins[] = { pinDecA, pinDecB, pinDecC, pinDecD };

// reed switch
//int pinReed = 2; // arduino
int pinReed = 9; // attiny


// NOTE: the dot (DP) pin is ignored since it's unused in this program
//int dispPins[] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG };

// common pins control digit selection; LOW is on - arduino nano
/*
int pinC1 = 10; // 12
int pinC2 = 11; // 9
int pinC3 = 12; // 8
*/

// common pins control digit selection; LOW is on - attiny84
int pinC1 = 6; // 12
int pinC2 = 7; // 9
int pinC3 = 8; // 8

int controlPins[] = { pinC1, pinC2, pinC3 };

/* this map is backwards..
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
*/

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


// reader..

/*
// reed switch config
int switchPin = 2;
byte oldSwitchState = HIGH;
const unsigned long debounceTime = 10;
unsigned long switchPressTime;
int reedCount;
*/

// calculations
// tire radius ~ 13.5 inches
// circumference = pi*2*r =~85 inches
// max speed of 35mph =~ 616inches/second
// max rps =~7.25

// time between one full rotation (in ms)
long timer;
int mph;
float circumference;
int reedVal;
int reedCounter;

// tire radius (in inches)
float radius = 12.1;

//min time (in ms) of one rotation (for debouncing)
int maxReedCounter = 50;


// the setup function runs once when you press reset or power the board
void setup() {
  //Serial.begin(57600);
  //Serial.println("initializing...");

  for (int i; i != (sizeof(controlPins) / 2); i++) {
    pinMode(controlPins[i], OUTPUT);
  }

  for (int i; i != (sizeof(decoderPins) / 2); i++) {
    pinMode(decoderPins[i], OUTPUT);
  }

  pinMode(pinReed, INPUT_PULLUP);

  // reader..
  reedCounter = maxReedCounter;
  circumference = 2*3.14*radius;
  
  // pinMode(pinReed, INPUT);

  // TIMER SETUP
  // the timer interrupt allows precise timed measurements of the reed switch
  // for more info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1

  // stop interrupts
  cli();

  // set timer1 interrupt at 1kHz

  // set entire TCCR1A register to 0
  TCCR1A = 0;

  // same for TCCR1B
  TCCR1B = 0;

  TCNT1  = 0;

  // set timer count for 1khz increments
  // = (1/1000) / ((1/(16*10^6))*8) - 1
  OCR1A = 1999;

  // turn on CTC mode
  TCCR1B |= (1 << WGM12);

  // set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);

  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // allow interrupts
  sei();
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

// convert digit to BCD and write to decoder pins
// FIXME - this should support writing the forward map value of bits backwards
void setNum(int num) {
  for (int i = 0; i != 4; i++) {
    digitalWrite(decoderPins[i], digits[num][i]);
  }
}

// write each number to a column
void num(int num) {
  for (int i = 1; i < 4; i++) {  
    posNum(i, (num % 10));
    num /= 10;
    delay(1);
  }
}

void demoCount(int count) {
  for (int i; i < count; i++) {
    num(i);
    delay(20);
  }
}

void demoLEDTest() {
  for (int i; i < 10; i++) {
    num(i);
    delay(20);
  }
}

/*
void reedSwitchDemo() {
  byte switchState = digitalRead(pinReed);
  
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
*/


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


//Interrupt at freq of 1kHz to measure reed switch
ISR(TIMER1_COMPA_vect) {
  reedVal = digitalRead(pinReed);
  
  // if reed switch is closed
  // NOTE: my reedValue defaults to 1 which is open
  if (!reedVal){
    // min time between pulses has passed
    if (reedCounter == 0) {
      // calculate miles per hour
      mph = (56.8*float(circumference))/float(timer);

      // reset timer
      timer = 0;

      // reset reedCounter
      reedCounter = maxReedCounter;
    }
    else{
      // don't let reedCounter go negative
      if (reedCounter > 0){
        reedCounter -= 1;
      }
    }
  // if reed switch is open
  } else {
    if (reedCounter > 0){
      reedCounter -= 1;
    }
  }
  if (timer > 2000){
    // if no new pulses from reed switch- tire is still, set mph to 0
    mph = 0;
  }
  else{
    timer += 1;
  }
}

void displayMph() {
  num(mph);
  //Serial.println(mph);
}

void loop() {
  //reedSwitchDemo();
  
  //demoCount(999);

  displayMph();

  // a good way to test chip / cables are working is trace along wires and check they are all LOW
  /*
  setPos(1);
  digitalWrite(pinDecA, 0);
  digitalWrite(pinDecB, 0);
  digitalWrite(pinDecC, 0);
  digitalWrite(pinDecD, 0);
  delay(50);
  */

  // light all the LEDs (digit 8) then trace the cables checking they are all HIGH
  /*
  setPos(1);
  digitalWrite(pinDecA, 1);
  digitalWrite(pinDecB, 1);
  digitalWrite(pinDecC, 0);
  digitalWrite(pinDecD, 1);
  delay(50);
  */
}
