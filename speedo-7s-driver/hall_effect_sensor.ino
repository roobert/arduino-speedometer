
/*
void demoHES() {
  byte switchState = digitalRead(pinHES);
  
  if (millis() - switchPressTime >= debounceTime) {
    switchPressTime = millis();
    oldSwitchState = switchState;
    if (switchState == LOW) {
      //Serial.println("Switch opened.");
      countHESOpen++;
    } else {
      //Serial.println("Switch closed."); // magnet detected
      countHESClosed++;
    }
    Serial.print(countHESOpen);
    Serial.print(" / "); 
    Serial.println(countHESClosed);
  }
}
*/

void displayMph() {
  num(mph);
  //Serial.println(mph);
}
