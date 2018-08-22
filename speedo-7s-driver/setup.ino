// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("initializing...");

  for (int i; i != (sizeof(controlPins) / 2); i++) {
    pinMode(controlPins[i], OUTPUT);
  }

  for (int i; i != (sizeof(decoderPins) / 2); i++) {
    pinMode(decoderPins[i], OUTPUT);
  }

  pinMode(pinHES, INPUT);
}
