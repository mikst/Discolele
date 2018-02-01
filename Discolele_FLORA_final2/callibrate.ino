void callibrateMIC(long callibrateDuration, int thresholdPercent) {
  long callibrateStart = millis();
  int micMax = 0;
  while ((millis() - callibrateStart ) < callibrateDuration) {
    int micValue = analogRead(micPin);
    //if(micValue < micMin) micMin = micValue;
    if (micValue > micMax) micMax = micValue;
  }
  micThreshold = micMax - (micMax / 100) * thresholdPercent;
  Serial.print("micMax: ");
  Serial.print('\t');
  Serial.println(micMax);
}
