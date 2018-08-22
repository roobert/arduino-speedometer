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


void displaySpeed(int revolutions) {
  // convert revolutions per second into mph..

  Serial.println(revolutions);
}
