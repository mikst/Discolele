/*
  KOBA Discolele Commission code for Flora
  Translates microphone input into thresholded trigger for ATtinys

  ////////////
  PINOUT FLORA
  ////////////
  +           --> +ATtiny, +MIC, +Neopixel
  -           --> -ATtiny, -MIC, -Neopixel, common GND of fabric buttons
  3 (OUTPUT)  --> trigger for ATtinys
  6 (INPUT)   --> inner button
  12 (INPUT)  --> outer button
  10 (OUTPUT)  --> Neopixel
  9 (INPUT)  --> MIC
*/
#include <Adafruit_NeoPixel.h>
#include <ButtonDebounce.h>


#ifdef __AVR__
#include <avr/power.h>
#endif
#define triggerPin 3
#define micPin 9
#define ledPin 10
#define inButtonPin 6
#define outButtonPin 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);
// set:
int micThresholdIncrease = 5;
//
int micThreshold = 180;
int sensorValue;
int outDCcount = 0;
boolean inButtonVal;
boolean outButtonVal;
boolean inButtonState;
boolean outButtonState;
boolean lastInButtonState = false;
boolean lastOutButtonState = false;
long lastInDebounceTime = 0;
long lastOutDebounceTime = 0;
long lastInDCtime = 0;
long lastOutDCtime = 0;
boolean inDCstate = false;
boolean outDCstate = false;
boolean inReleased = false;
boolean outReleased = false;
long DCdelay = 500;
long debounceDelay = 50;
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t off = strip.Color(0, 0, 0);
uint32_t white = strip.Color(255, 255, 255);
uint32_t orange = strip.Color(255, 200, 5);

ButtonDebounce buttonInner(6, 70);
ButtonDebounce buttonOuter(12, 70);

long innerclickTime = 0;

enum astate {
  NORMAL, ADJUST
};

astate currentState = NORMAL;
boolean bothPressed = false;
long initTime = 0;

void setup() {

  // test LED:
  strip.begin();
  strip.setBrightness(10); 
  strip.setPixelColor(0, white);
  strip.show();
  delay(1000);

  pinMode(triggerPin, OUTPUT);
  pinMode(micPin, INPUT);
  pinMode(inButtonPin, INPUT_PULLUP);
  pinMode(outButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {
  debugPrint();

  // set last states
  lastInButtonState = inButtonState;
  lastOutButtonState = outButtonState;

  if (inDCstate) {
    inDCstate = false;
  }

  ////////////////////////////////////////////////////////
  // read buttons, set variables
  ////////////////////////////////////////////////////////
  buttonInner.update();
  buttonOuter.update();

  // toggle state, so a button is logically true if pressed
  inButtonState = !buttonInner.state();
  outButtonState = !buttonOuter.state();

  //    Serial.print(inButtonState);
  //    Serial.print(" : ");
  //    Serial.println(outButtonState);

  ////////////////////////////////////////////////////////
  // detect double click
  ////////////////////////////////////////////////////////
  if (inButtonState != lastInButtonState) {

    if (inButtonState) {
      if ((millis() - innerclickTime) < DCdelay) {
        inDCstate = true;
      } else {
        inDCstate = false;
      }
      innerclickTime = millis();
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // MODES //

  // detect callibration mode //
  if (currentState != ADJUST && inDCstate == true) {
    inDCstate = false;
    strip.setPixelColor(0, blue);
    strip.show();

    Serial.println("CALIBRATE");

    // CALLIBRATION //
    callibrateMIC(10000, 80);  // dudration, percentage

    //----------------
    // early return
    return;
  }



  //check if both buttons are pressed -- > adjust mode //
  if (true == inButtonState && true == outButtonState) {

    // use initTime as a flag
    // only process bothButton-check if initTime is >= 0
    // !! important initTime needs to be of a signed type !!
    if (initTime >= 0) {

      if (!bothPressed) {
        initTime = millis();
        bothPressed = true;
      } else if (millis() - initTime > 2000) {

        if (currentState != ADJUST) {
          // set state
          currentState = ADJUST;
          Serial.println("ADJUST");

          strip.setPixelColor(0, white);
          strip.show();

          // avoid processing both buttons next cycle
          // need to get off one button before processing again
          initTime = -1;
        } else {
          // set state
          currentState = NORMAL;
          Serial.println("NORMAL");

          // avoid processing both buttons next cycle
          // need to get off one button before processing again
          initTime = -1;
        }
      }
    }

  } else {
    // we are off both buttons
    // reset variables
    bothPressed = false;
    initTime = 0;

    // process single button clicks in ADJUST state
    // only if one button is pressed (avoids 'fall-through' from mode-change)
    if (currentState == ADJUST) {

      // ADJUST STATE
      if (lastInButtonState != inButtonState && true == inButtonState) {
        Serial.println("RED");
        micThreshold += micThresholdIncrease;
        strip.setPixelColor(0, red);
        strip.show();
        delay(50);
      }
      else if (lastOutButtonState != outButtonState && true == outButtonState) {
        Serial.println("GREEN");
        micThreshold -= micThresholdIncrease;
        strip.setPixelColor(0, green);
        strip.show();
        delay(50);
      }
      else {
        strip.setPixelColor(0, off);
        strip.show();
      }
    }
  }


  ////////////////////////////////////////////////////////
  // ATTINY LED STUFF
  ////////////////////////////////////////////////////////
  sensorValue = analogRead(micPin);
  if (sensorValue > micThreshold)
  {
    strip.setBrightness(10);  
    strip.setPixelColor(0, orange);
    strip.show();
    digitalWrite(triggerPin, HIGH);
    //Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  }
  else {
    strip.setPixelColor(0, off);
    strip.show();
    digitalWrite(triggerPin, LOW);
  }



}
