#define ST_ENABLE 12
#define DIR 2
#define STEP 3

#define BUTTON 8
#define LED 13

//tmc2208 btt, fysetc stepper, close enough???
#define ONEREV 1620

#define BLINDREVS 3

int buttonState = 0;              //reads button state
bool blindState = true;           //tracks state of blinds

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(ST_ENABLE, OUTPUT);

  digitalWrite(ST_ENABLE, HIGH);    //stepper driver disabled by default
  digitalWrite(LED, LOW);           //LED off by default
}


void loop() {
  buttonState = digitalRead(BUTTON);  //reads button state

  //if button is pressed:
  if (buttonState == HIGH) {
    digitalWrite(LED, HIGH);        // turn LED on
    digitalWrite(ST_ENABLE, LOW);   // enable stepper driver

    //sets direction of stepper according to blindState tracking variable
    if(blindState){
      digitalWrite(DIR, HIGH);
    }
    else digitalWrite(DIR, LOW);

    turnBlinds(BLINDREVS, ONEREV);  //calls method to turn motor REVBLINDS times

    blindState = !blindState;       //toggles blindState

    digitalWrite(ST_ENABLE, HIGH);  //disables stepper motor
    digitalWrite(LED, LOW);         //turns off LED
  }
}


//accepts number of full revolutions and steps per revolution
//and spins motor accordingly by microstepping with 500microsec intervals
void turnBlinds(int numTurns, int turnsPerRev){
  for(int i=0; i < numTurns * turnsPerRev; i++){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP, LOW);
    delayMicroseconds(500);
  }
}
