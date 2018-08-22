void loop() {
  demoHES();

  //demoCount(999);

  //displayMph();

  // a good way to test chip / cables are working is trace along wires and check they are all LOW
  /*
  setPos(1);
  digitalWrite(pinDecA, 0);
  digitalWrite(pinDecB, 0);
  digitalWrite(pinDecC, 0);
  digitalWrite(pinDecD, 0);
  delay(50);
  */

  // light all the LEDs (0001 - digit 8) then trace the cables checking they are all HIGH
  /*
  setPos(1);
  digitalWrite(pinDecA, 0);
  digitalWrite(pinDecB, 0);
  digitalWrite(pinDecC, 0);
  digitalWrite(pinDecD, 1);
  delay(50);
  */
}
