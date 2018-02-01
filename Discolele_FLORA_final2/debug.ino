void debugPrint(){
  Serial.print("sensorVal. ");
  Serial.print(sensorValue);
  Serial.print('\t');
  Serial.print("inVal: ");
  Serial.print(inButtonState);
  Serial.print('\t');
  Serial.print("outVal: ");
  Serial.print(outButtonState);
  Serial.print('\t');
  Serial.print("micThreshold: ");
  Serial.println(micThreshold);
  delay(10);
  }
