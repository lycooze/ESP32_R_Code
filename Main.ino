#include <ESP32Servo.h>

void Serial_Start();
void Receive();
void Translation();


#define Left_Servo_Pin 18
#define Right_Servo_Pin 4
#define Step_Size 5

#define LORA Serial2

Servo Left_Servo;
Servo Right_Servo;



unsigned long Start_Time = 0;
int Speed;
int Goal_Time;

int Goal_Position;
int Goal_Left_Servo;
int Goal_Right_Servo;
int Current_Position_Left;
int Current_Position_Right;

String Command;

char Part;
char Specific_Part;





void setup() {
  Serial_Start();
  Goal_Left_Servo = 90;
  Goal_Right_Servo = 90;
  Current_Position_Left = 90;
  Current_Position_Right = 90;
  Left_Servo.write(90);
  Right_Servo.write(90);
}



void loop() {
  Update();
  Receive();

  if (Command.length() < 2) {    
    Command = "";
    return;
  }

  Translation();
  Selection();
  Command = "";

  


}
































