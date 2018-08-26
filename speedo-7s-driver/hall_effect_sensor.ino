/*
void demoHES() {
  byte switchState = digitalRead(pinHES);

  // work out how much time has passed since last loop
  elapsedTime = millis() - switchCloseTime;
  switchCloseTime = millis();

  // add time since last call to timer until we hit 1 second
  timer += elapsedTime;

  if (timer > 1000) {
    //displaySpeed(revolutions);
    timer = 0;
    return;
  }

  //Serial.print("timer: ");
  //Serial.println(timer);
  //Serial.print("elapsed: ");
  //Serial.println(elapsedTime);

  // only continue if we're going less than 100mph (~23rps or 1r every 44ms)
  if (elapsedTime < debounceHESMs) {
    return;
  }

  // HES is open
  if (switchState == LOW) {
    countHESOpen++;
  // HES is closed
  } else {
    countHESClosed++;
    revolutions++;
  }
   Serial.print(countHESOpen);
   Serial.print(" / ");
   Serial.println(countHESClosed);
}
*/


/*
void displaySpeed(int revolutions) {
  // convert revolutions per second into mph..

  Serial.println(revolutions);
}
*/


// volatile byte rotation; // variale for interrupt fun
// float timetaken, rpm, dtime;
// int v;
// unsigned long pevtime;
// 
// void setup() {
//   Serial.begin(9600);
// 
//   // secound pin of arduino used as interrupt
//   attachInterrupt(0, magnet_detect, RISING);
// 
//   rotation = 0;
//   rpm = 0;
//   pevtime = 0;
// }
// 
// // to drop down to zero when braked.
// void loop() {
//   if((millis() - dtime) > 1000)
//     v = (0.035) * rpm * 0.37699;  // ACTUAL CODE KM/hr
// }
// 
// //Called whenever a magnet is detected
// void magnet_detect() {
//   rotation++;
// 
//   dtime = millis();
// 
//   if (rotation >= 2) {
//     // time in millisec
//     timetaken = millis() - pevtime;
// 
//     rpm=(1000/timetaken)*60;
// 
//     pevtime = millis();
// 
//     rotation=0;
//     Serial.write(v);
//   }
// }
// 
// //}

/*
#include <CircularBuffer.h>

CircularBuffer<unsigned int,8> buffer;

unsigned int pinHES = 2;
unsigned int previousMs;
unsigned int currentMs;
unsigned int revolutionMs;
unsigned int sensorState;
unsigned int mph;
*/

/*
void setup() {
  pinMode(pinHES, INPUT);

  // populate buffer with 0s so it'll show 0mph on start-up
  for (unsigned int i = 0; i != 8; i++) {
    buffer.push(0);
  }

  Serial.begin(115200);
}
*/

/*
void demoHES() {
  // LOW  is open
  // HIGH is closed
  sensorState = digitalRead(pinHES);

  // magnet detected..
  if (sensorState == HIGH) {
    currentMs = millis();

    revolutionMs = currentMs - previousMs;

    previousMs = currentMs;

    buffer.push(revolutionMs);

    displayTimer += revolutionMs;
  }

  float bufferAverage = 0.0;
  for (unsigned int i = 0; i < buffer.size(); i++) {
    bufferAverage += buffer[i] / buffer.size();
  }

  mph = 1609344 / ( bufferAverage * 833 );

  //if (displayTimer > 1000) {
  //  displayTimer = 0;
  //  Serial.println(mph);
    num(mph);
  //}
  delay(10);

  delay(10);
  Serial.println();
  Serial.print("last revolution time: ");
  Serial.println(buffer.last());
  Serial.print("buffer average: ");
  Serial.println(bufferAverage);
  Serial.print("mph: ");
  Serial.println(mph);
}
*/

void demoHES() {
  // LOW  is open
  // HIGH is closed
  sensorState = digitalRead(pinHES);

  // magnet detected..
  if (sensorState == HIGH) {
    currentMs = millis();

    revolutionMs = currentMs - previousMs;

    previousMs = currentMs;

    buffer.push(revolutionMs);

    displayTimer += revolutionMs;
  }

  float bufferAverage = 0.0;
  for (unsigned int i = 0; i < buffer.size(); i++) {
    bufferAverage += buffer[i] / buffer.size();
  }

   if (displayTimer > 1000) {
    mph = 1609344 / ( bufferAverage * 833 );
    displayTimer = 0;
  }

  num(mph);
  //Serial.println(mph);
}
