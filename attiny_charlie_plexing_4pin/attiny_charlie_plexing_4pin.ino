/* code for ATtiny
 6 LED charlie plexing
 LEDs between pin1>pin2, pin1>pin3, pin2>pin1, pin2>pin3, pin3>pin1, pin3>pin2
 */




boolean tilt;
boolean sequence;
boolean last_tilt;
int val;
int lastR;


int pause=100;


void setup(){

  pinMode(4,INPUT);

  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);


}

void loop(){


  // store the digitalread value from the last loop
  last_tilt=tilt;
  // read the tilt sensor
  tilt=digitalRead(4);

//
//  val = analogRead(A2);
//  if (val>200){
//    tilt=true;
//
//  }
//  else 
//  { 
//    tilt=false;
//
//  }


  // if previously tilt sensor was not on
  if (last_tilt!=tilt){
    // and currently tilt sensor is on
    if (tilt==true) {
      sequence=true;     
    }
  } else sequence=false;

//if (tilt==true) {
//      sequence=true;     
//    }
//   else sequence=false;


  // if tilt1 sequence is on
  if (sequence){
    // go through the sequence
    for (int i=0; i<1; i++){
      int r=random(11);
      if (r==lastR){
        r=random(11);
      }
      LED_ON(r); 
      lastR=r;     
    }
//digitalWrite(0,HIGH);
//delay(50);
//digitalWrite(0,LOW);
  }


delay(2);
}

void LED_ON(int led){
  switch (led){
  case 0:
    pinMode(0,OUTPUT);
    pinMode(1,OUTPUT);
    digitalWrite(0,HIGH);
    digitalWrite(1,LOW);
    delay(pause);
    digitalWrite(0,LOW);
    pinMode(0,INPUT);
    pinMode(1,INPUT);
    break;

  case 1:
    pinMode(0,OUTPUT);
    pinMode(2,OUTPUT);
    digitalWrite(0,HIGH);
    digitalWrite(2,LOW);
    delay(pause);
    digitalWrite(0,LOW);
    pinMode(0,INPUT);
    pinMode(2,INPUT);
    break;

  case 2:
    pinMode(0,OUTPUT);
    pinMode(3,OUTPUT);
    digitalWrite(0,HIGH);
    digitalWrite(3,LOW);
    delay(pause);
    digitalWrite(0,LOW);
    pinMode(0,INPUT);
    pinMode(3,INPUT);
    break;

  case 3:
    pinMode(1,OUTPUT);
    pinMode(0,OUTPUT);
    digitalWrite(1,HIGH);
    digitalWrite(0,LOW);
    delay(pause);
    digitalWrite(1,LOW);
    pinMode(1,INPUT);
    pinMode(0,INPUT);
    break;

  case 4:
    pinMode(1,OUTPUT);
    pinMode(2,OUTPUT);
    digitalWrite(1,HIGH);
    digitalWrite(2,LOW);
    delay(pause);
    digitalWrite(1,LOW);
    pinMode(1,INPUT);
    pinMode(2,INPUT);
    break;

  case 5:
    pinMode(1,OUTPUT);
    pinMode(3,OUTPUT);
    digitalWrite(1,HIGH);
    digitalWrite(3,LOW);
    delay(pause);
    digitalWrite(1,LOW);
    pinMode(1,INPUT);
    pinMode(3,INPUT);
    break;

  case 6:
    pinMode(2,OUTPUT);
    pinMode(0,OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(0,LOW);
    delay(pause);
    digitalWrite(2,LOW);
    pinMode(2,INPUT);
    pinMode(0,INPUT);
    break;

  case 7:
    pinMode(2,OUTPUT);
    pinMode(1,OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(1,LOW);
    delay(pause);
    digitalWrite(2,LOW);
    pinMode(2,INPUT);
    pinMode(1,INPUT);
    break;

  case 8:
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    delay(pause);
    digitalWrite(2,LOW);
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    break;

  case 9:
    pinMode(3,OUTPUT);
    pinMode(0,OUTPUT);
    digitalWrite(3,HIGH);
    digitalWrite(0,LOW);
    delay(pause);
    digitalWrite(3,LOW);
    pinMode(3,INPUT);
    pinMode(0,INPUT);
    break;

  case 10:
    pinMode(3,OUTPUT);
    pinMode(1,OUTPUT);
    digitalWrite(3,HIGH);
    digitalWrite(1,LOW);
    delay(pause);
    digitalWrite(3,LOW);
    pinMode(3,INPUT);
    pinMode(1,INPUT);
    break;

  case 11:
    pinMode(3,OUTPUT);
    pinMode(2,OUTPUT);
    digitalWrite(3,HIGH);
    digitalWrite(2,LOW);
    delay(pause);
    digitalWrite(3,LOW);
    pinMode(3,INPUT);
    pinMode(2,INPUT);
    break;




  }


}





