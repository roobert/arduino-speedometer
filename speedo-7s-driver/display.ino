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
