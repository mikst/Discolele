void readButtons() {
  ////////////////////////////////////////////////////////
  // BUTTON STUFF
  ////////////////////////////////////////////////////////

  inButtonVal = digitalRead(inButtonPin);
  outButtonVal = digitalRead(outButtonPin);

  if (inButtonVal != lastInButtonState) {
    lastInDebounceTime = millis();
    lastInButtonState = inButtonVal;
  }
  if (outButtonVal != lastOutButtonState) {
    lastOutDebounceTime = millis();
    lastOutButtonState = outButtonVal;
  }

  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // BUTTONS RELEASED? //
  //  if ((millis() - lastInDebounceTime) > debounceDelay && inButtonVal == 1) {
  //    inReleased = true;
  //  }
  //  if ((millis() - lastOutDebounceTime) > debounceDelay && outButtonVal == 1) {
  //    outReleased = true;
  //  }

  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // BUTTONS PRESSED? //
  // IN //
  if ((millis() - lastInDebounceTime) > debounceDelay) {
    if (inButtonVal == 0 && inReleased == true) {
      inReleased = false;
      inButtonState = true;
      if (millis() - lastInDCtime < DCdelay) {
        inDCstate = true;
      }
      lastInDCtime = millis();
    } else if (inButtonVal == 1) {
      inReleased = true;
      inButtonState = false;
    }

  }
  // OUT //
  if ((millis() - lastOutDebounceTime) > debounceDelay) {
    if (outButtonVal == 0 && outReleased == true) {
      outReleased = false;
      outButtonState = true;
      if (millis() - lastOutDCtime < DCdelay) {
        outDCstate = true;
      }
      lastOutDCtime = millis();
    } else if (outButtonVal == 1) {
      outReleased = true;
      outButtonState = false;
    }

  }
}
