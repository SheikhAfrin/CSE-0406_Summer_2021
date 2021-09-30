#include <Keypad.h>
#define dw digitalWrite


const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns as this is a 4*4 Keypad

char keys[ROWS][COLS] = {

  {'7', '8', '9', '/'},

  {'4', '5', '6', '*'},

  {'1', '2', '3', '-'},

  {'c', '0', '=', '+'}


}; // defining the keys in the keypad

//here 13, 12, 8, 7 pins are disconnected
byte rowPins[ROWS] = {13, 12, 4, 8}; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = {2, 1, 0, 7}; // Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // Create the Keypad variable to identify and store the pressed key.

struct pin {
  int p1 = 0;
  int p2 = 0;
  pin(int _a = 0, int _b = 0) {
    p1 = _a;
    p2 = _b;
  }
}; /// Motor Pin Structure

pin DCmotor[4] = {{0, 0}, {11, 10}, {9, 6}, {5, 3}}; /// storing every motor pin number

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(DCmotor[i].p1, OUTPUT);
    pinMode(DCmotor[i].p2, OUTPUT);
  } // setting up every pin mode
}

void clockwise(pin motor){
  dw(motor.p1, HIGH);
  dw(motor.p2, LOW);
}/// clockwise motor rotation

void anti_clockwise(pin motor){
  dw(motor.p2, HIGH);
  dw(motor.p1, LOW);
}//anti clockwise motor rotation


void off(pin motor){
  dw(motor.p1, LOW);
  dw(motor.p2, LOW);
}//motor turn off


int motorNo = 0; // indicates which motor should rotate

void loop() {
  char key = kpd.getKey(); /// get key from keypad
  for(int i = 1; i < 4; i++){
    off(DCmotor[i]); /// initially turn off every motor
  }
  if (key != 0) {
    if (key >= '1' and key <= '3') { 
      if (!motorNo) motorNo = key - '0'; /// checking if 1st digit entered
      else if(key >= '1' and key <='2') {
        if (key == '1') clockwise(DCmotor[motorNo]);
        if (key == '2') anti_clockwise(DCmotor[motorNo]);
        delay(1000);
        motorNo = 0;
      }
      
    }
    
  }
  
}
