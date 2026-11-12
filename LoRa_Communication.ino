  #define LoRa Serial2
  #define Bpin 2
  #define Left_Servo 18
  #define Right_Servo 4
  #define Step_Size 5  
  #include <ESP32Servo.h>
  #include <vector>
  #include <string>
  void Servo_Instructions();
  void Receive();
  void Selection();
  int blink(int timeD, int amount);
  void Translation();




  Servo Left;
  Servo Right;

  char Progress_status;
  char Speed_S;
  char Speed_Ml; 


  char Selec; 
  char Instruc; 
  int Speed;
  int Data;
  int Current = 90;

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
  if (Speed == 100) {

    blink(20, 5);
  }         

  }


  void Receive() {
    
    if (LoRa.available()) {
      Command = LoRa.readStringUntil('\n');
      Command.trim();
      Serial.print("[LoRa] got: ");
      Serial.println(Command);
    }
    else if (Serial.available()) {
      Command = Serial.readStringUntil('\n');
      Command.trim();
      Serial.print("[USB] got: ");
      Serial.println(Command);
    }
    
  }



  void Servo_Instructions() {
    Serial.print("Move ");
    Serial.print(Instruc);
    Serial.print(" from ");
    Serial.print(Instruc == 'L' ? Cur_SPL : Cur_SPR);
    Serial.print(" to ");
    Serial.print(Data);
    Serial.print(" at speed ");
    Serial.print(Speed);
    Serial.print(" start=");             
          Left.write(Data);      
          Cur_SPL = Data;
        } else {
          while (Cur_SPL != Data) {
            if (Data > Cur_SPL) Cur_SPL = min(Cur_SPL + Step_Size, Data);
            else                Cur_SPL = max(Cur_SPL - Step_Size, Data);
            Left.write(Cur_SPL);
            delay(Speed);
          }
        }
        break;

      case 'R':
        if (Speed == 0) {
          Right.write(Data);
          Cur_SPR = Data;
        } else {
          while (Cur_SPR != Data) {
            if (Data > Cur_SPR) Cur_SPR = min(Cur_SPR + Step_Size, Data);
            else                Cur_SPR = max(Cur_SPR - Step_Size, Data);
            Right.write(Cur_SPR);
            delay(Speed);
          }
        }
        break; 
      case 'M':
      
    }

    Serial.print("end=");
    Serial.println(millis());

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
    Serial.print("Speed is now ");
    Serial.println(Speed);  
    blink(20, 5);
    Selec = 0;                             
    return;
  }

  Selec   = Command[0];
  Instruc = Command[1];
  Data    = Command.substring(2).toInt();   
  }
