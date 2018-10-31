//Created by Justin Nguyen
//For use by Texas Panic Room

#include <Bounce2.h>
//Inputs
int A = 2;
int B = 3;
int C = 4;
int D = 5;
int E = 6;
int key = A5;
//Outputs
int LED0 = 7; 
int LED1 = 8; 
int LED2 = 9; 
int LED3 = 10; 
int LED4 = 11;
int LED5 = 12;
int LED6 = 13;                                
int halos = A4;
int maglock = A3;

bool keyFlag = false;
bool initial = false;
bool Astate, Aprime;
bool Bstate, Bprime;
bool Cstate, Cprime;
bool Dstate, Dprime;
bool Estate, Eprime;
bool L0, L1, L2, L3, L4, L5, L6;
bool* LEDS[5];
bool flash = false;

Bounce butt0 = Bounce();
Bounce butt1 = Bounce();
Bounce butt2 = Bounce();
Bounce butt3 = Bounce();
Bounce butt4 = Bounce();

Bounce butts[5] = {butt0, butt1, butt2, butt3, butt4};

void setup() {
  Serial.begin(9600);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
  pinMode(key, INPUT_PULLUP);
  butt0.attach(A);
  butt1.attach(B);
  butt2.attach(C);
  butt3.attach(D);
  butt4.attach(E);
  for(int i = 0; i < 5; i++){
    butts[i].interval(50);
  }
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(halos, OUTPUT);
  pinMode(maglock, OUTPUT);
  L0 = false;
  L1 = false;
  L2 = false;
  L3 = false;
  L4 = false;
  L5 = false;
  L6 = false;
  digitalWrite(LED0, L0);
  digitalWrite(LED1, L1);
  digitalWrite(LED2, L2);
  digitalWrite(LED3, L3);
  digitalWrite(LED4, L4);
  digitalWrite(LED5, L5);
  digitalWrite(LED6, L6);
  digitalWrite(halos, LOW);
}

void loop() {
  while(digitalRead(key)){
    L0 = false;
    L1 = false;
    L2 = false;
    L3 = false;
    L4 = false;
    L5 = false;
    L6 = false;
    digitalWrite(LED0, L0);
    digitalWrite(LED1, L1);
    digitalWrite(LED2, L2);
    digitalWrite(LED3, L3);
    digitalWrite(LED4, L4);
    digitalWrite(LED5, L5);
    digitalWrite(LED6, L6);
    digitalWrite(halos, LOW);
    initial = false;
    flash = false;
  }
  if(!initial){
    //Starting State
    digitalWrite(LED6, HIGH);
    L6 = true;
    digitalWrite(LED5, HIGH);
    L5 = true;
    digitalWrite(halos, HIGH);
    initial = true;
  }

  butt0.update();
  if (butt0.fell()){
    L0 = !L0;
    L2 = !L2;
  }

  butt1.update();
  if (butt1.fell()){
    Serial.println("Button1!");
    L1 = !L1;
    L6 = !L6;
  }

  butt2.update();
  if (butt2.fell()){
    L1 = !L1;
    L3 = !L3;
  }

  butt3.update();
  if (butt3.fell()){
    L0 = !L0;
    L2 = !L2;
    L4 = !L4;
    L5 = !L5;
    L6 = !L6;
  }
  butt4.update();
  if (butt4.fell()){
    L3 = !L3;
    L5 = !L5;
  }

  digitalWrite(LED0, L0);
  digitalWrite(LED1, L1);
  digitalWrite(LED2, L2);
  digitalWrite(LED3, L3);
  digitalWrite(LED4, L4);
  digitalWrite(LED5, L5);
  digitalWrite(LED6, L6);

  if (L0 && L1 && L2 && L3 && L4 && L5 && L6){
    if(!flash){
      for(int i = 0; i < 2; i++){
        digitalWrite(LED0, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
        delay(500);
        digitalWrite(LED0, HIGH);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, HIGH);
        delay(500);
      }
      digitalWrite(maglock, HIGH);
      delay(50);
      digitalWrite(maglock, LOW);
      flash = true;
    }
  }
  else{
    digitalWrite(maglock, LOW);
  }
}
