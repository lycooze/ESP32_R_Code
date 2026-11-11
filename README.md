#define LoRa Serial2
#define Bpin 2
#define Left_Servo 18
#define Right_Servo 4
#include <ESP32Servo.h>
void Servo_Instructions();
void Receive();
void Selection();
int blink(int timeD, int amount);
void Translation();

Servo Left;
Servo Right;

char Selec;   //for what part i select
char Instruc; //for which specfic part of selection you chose
int Speed = 15; //ms delay per degree, higher = slower
int Data;

String Command;

int Cur_SPL = 90;
int Cur_SPR = 90;


void setup()
{
  pinMode(Bpin, OUTPUT);
  Serial.begin(115200);
  LoRa.begin(9600, SERIAL_8N1, 16, 17);
  Left.attach(Left_Servo);
  Right.attach(Right_Servo);
  Left.write(Cur_SPL);
  Right.write(Cur_SPR);
}


void loop() {
  Receive();
  if (Command.length() < 2) {
    Command = "";
    return;
  }
  Translation();
  Selection();
  Command = "";
}


void Receive() {
  //remember to change this to LoRa when done testing
  if (LoRa.available()) {
    Command = LoRa.readStringUntil('\n');
    Command.trim();
  }
}


void Servo_Instructions() {
  switch (Instruc) {
    case 'L':
      if (Data >= Cur_SPL) {
        for (; Cur_SPL < Data; Cur_SPL++) {
          Left.write(Cur_SPL);
          delay(Speed);
        }
      }
      else if (Data < Cur_SPL) {
        for (; Cur_SPL > Data; Cur_SPL--) {
          Left.write(Cur_SPL);
          delay(Speed);
        }
      }
      Left.write(Data);
      break;
    case 'R':
      if (Data >= Cur_SPR) {
        for (; Cur_SPR < Data; Cur_SPR++) {
          Right.write(Cur_SPR);
          delay(Speed);
        }
      }
      else if (Data < Cur_SPR) {
        for (; Cur_SPR > Data; Cur_SPR--) {
          Right.write(Cur_SPR);
          delay(Speed);
        }
      }
      Right.write(Data);
      break;
  }
}


void Selection() {
  switch (Selec) {
    case 'S':
      Servo_Instructions();
      break;
  }
}


int blink(int timeD, int amount) {
  for (int g = 0; g < amount; g++) {
    digitalWrite(Bpin, HIGH);
    delay(timeD);
    digitalWrite(Bpin, LOW);
    delay(timeD);
  }
  return timeD;
}


void Translation() {
  if (Command[0] == 'V') {
    Speed = Command.substring(1).toInt();
    if (Speed < 0) Speed = 0;
    Serial.print("Speed is now ");
    Serial.println(Speed);
    blink(20, 5);
    Selec = 0;
    return;
  }

  Selec   = Command[0];
  Instruc = Command[1];
  Data    = constrain(Command.substring(2).toInt(), 0, 180);
}
