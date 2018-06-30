// LED speed-o-meter

// hs320401k-24 3 digit
// http://www.marthel.pl/katalog/Betlux/BL-T52A-31.pdf

// LEDs: A-F clockwise from top; G is the bar; DP is the dot; HIGH is on
// NOTE: pin D13 is used as output rather than input since it's connected
// to the board LED which makes input from the reed switch fail to be
// read
int pinA  = 13; // 11
int pinB  = 3;  // 7
int pinC  = 4;  // 4
int pinD  = 5;  // 2
int pinE  = 6;  // 1
int pinF  = 7;  // 10
int pinG  = 8;  // 5
int pinDP = 9;  // 3

// NOTE: the dot (DP) pin is ignored since it's unused in this program
int dispPins[] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG };

// common pins control digit selection; LOW is on
int pinC1 = 10; // 9
int pinC2 = 11; // 8
int pinC3 = 12; // 7

int controlPins[] = { pinC1, pinC2, pinC3 };

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("initializing...");

  for (int i; i != (sizeof(dispPins) / 2); i++) {
    pinMode(dispPins[i], OUTPUT);
  }

  for (int i; i != (sizeof(controlPins) / 2); i++) {
    pinMode(controlPins[i], OUTPUT);
  }
}


void posNum(int pos, int num) {
  setPos(pos);
  setNum(num);
}

void setPos(int pos) {
  switch(pos) {
    case 1:
      digitalWrite(pinC1, LOW);
      digitalWrite(pinC2, HIGH);
      digitalWrite(pinC3, HIGH);
      break;
    case 2:
      digitalWrite(pinC1, HIGH);
      digitalWrite(pinC2, LOW);
      digitalWrite(pinC3, HIGH);
      break;
    case 3:
      digitalWrite(pinC1, HIGH);
      digitalWrite(pinC2, HIGH);
      digitalWrite(pinC3, LOW);
      break;
  }
}

void setNum(int num) {
  switch(num) {
    case 0:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  HIGH);
      digitalWrite(pinE,  HIGH);
      digitalWrite(pinF,  HIGH);
      digitalWrite(pinG,  LOW);
      break;
    case 1:
      digitalWrite(pinA,  LOW);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  LOW);
      digitalWrite(pinE,  LOW);
      digitalWrite(pinF,  LOW);
      digitalWrite(pinG,  LOW);
      break;
    case 2:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  LOW);
      digitalWrite(pinD,  HIGH);
      digitalWrite(pinE,  HIGH);
      digitalWrite(pinF,  LOW);
      digitalWrite(pinG,  HIGH);
      break;
    case 3:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  HIGH);
      digitalWrite(pinE,  LOW);
      digitalWrite(pinF,  LOW);
      digitalWrite(pinG,  HIGH);
      break;
    case 4:
      digitalWrite(pinA,  LOW);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  LOW);
      digitalWrite(pinE,  LOW);
      digitalWrite(pinF,  HIGH);
      digitalWrite(pinG,  HIGH);
      break;
    case 5:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  LOW);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  HIGH);
      digitalWrite(pinE,  LOW);
      digitalWrite(pinF,  HIGH);
      digitalWrite(pinG,  HIGH);
      break;
    case 6:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  LOW);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  HIGH);
      digitalWrite(pinE,  HIGH);
      digitalWrite(pinF,  HIGH);
      digitalWrite(pinG,  HIGH);
      break;
    case 7:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  LOW);
      digitalWrite(pinE,  LOW);
      digitalWrite(pinF,  LOW);
      digitalWrite(pinG,  LOW);
      break;
    case 8:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  HIGH);
      digitalWrite(pinE,  HIGH);
      digitalWrite(pinF,  HIGH);
      digitalWrite(pinG,  HIGH);
      break;
    case 9:
      digitalWrite(pinA,  HIGH);
      digitalWrite(pinB,  HIGH);
      digitalWrite(pinC,  HIGH);
      digitalWrite(pinD,  HIGH);
      digitalWrite(pinE,  LOW);
      digitalWrite(pinF,  HIGH);
      digitalWrite(pinG,  HIGH);
      break;
  }
}

void num(int num) {
  // FIXME: blank digit if not required
  for (int i = 3; i > 0; i--) {
    Serial.println(i);
    posNum(i, (num % 10));
    num /= 10;
  }
}

void clearDisp() {
  for (int i; i != (sizeof(dispPins) / 2); i++) {
    digitalWrite(dispPins[i], LOW);
  }
}

void demoCount() {
  for (int i=0; i < 1000; i++) {
    for (int n=0; n < 2; n++) {
      num(i);
      delay(1);
    }
  }
}

void demoLEDTest() {
  // FIXME: change direction and lengthen final segment pause
  // FIXME: this is a pretty rubbish pattern, come up with something better..
  digitalWrite(pinG, HIGH);
  delay(100);

  digitalWrite(pinC, HIGH);
  delay(100);

  digitalWrite(pinD, HIGH);
  delay(100);

  digitalWrite(pinE, HIGH);
  delay(100);

  digitalWrite(pinF, HIGH);
  delay(100);

  digitalWrite(pinA, HIGH);
  delay(100);

  digitalWrite(pinB, HIGH);
  delay(100);

  digitalWrite(pinG, LOW);
  delay(100);

  digitalWrite(pinC, LOW);
  delay(100);

  digitalWrite(pinD, LOW);
  delay(100);

  digitalWrite(pinE, LOW);
  delay(100);

  digitalWrite(pinF, LOW);
  delay(100);

  digitalWrite(pinA, LOW);
  delay(100);

  digitalWrite(pinB, LOW);
  delay(100);
}

void loop() {
  demoLEDTest();
}


