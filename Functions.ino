


void Serial_Start() {
  Serial.begin(115200); 
  LORA.begin(9600, SERIAL_8N1, 16, 17);
  Left_Servo.attach(Left_Servo_Pin);
  Right_Servo.attach(Right_Servo_Pin);


}




 void Receive() {

    if (LORA.available()) {
      Command = LORA.readStringUntil('\n');
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


   void Translation() {
     if (Command[0] == 'V') {
    Speed = Command.substring(1).toInt();
    Serial.print("Speed is now ");
    Serial.println(Speed);  
    Part = 0;                             
    return;
  }

  Part   = Command[0];
  Specific_Part = Command[1];
  Goal_Position = Command.substring(2).toInt();   
  }

  void Selection() {
    switch (Part) {
      case 'S':
        Servo_Instructions();
        break;

    }

  }

  void Servo_Instructions() {
    switch(Specific_Part) {
      case 'L':
        Goal_Left_Servo = Goal_Position;
        break;
      case 'R':
        Goal_Right_Servo = Goal_Position;
        break;
      case 'M':
        Goal_Right_Servo = Goal_Position;
        Goal_Left_Servo = Goal_Position;
        break;



    }
  }








  bool Wait() {

    if (millis() - Start_Time < Speed) {
      
      return false;
    }
    else {
      Start_Time = millis();
      return true;
    }
  

    


  }



void Update() {
  Update_Arm();

}








void Update_Arm() {
  if (Wait()) {
    if (Current_Position_Left != Goal_Left_Servo) {
      if (Current_Position_Left > Goal_Left_Servo) {
       Current_Position_Left = max(Current_Position_Left - Step_Size, Goal_Left_Servo);
     }
     else {
       Current_Position_Left = min(Current_Position_Left + Step_Size, Goal_Left_Servo);
     }
     Left_Servo.write(Current_Position_Left);
     }

    if (Current_Position_Right != Goal_Right_Servo) {
      if (Current_Position_Right > Goal_Right_Servo) {
       Current_Position_Right = max(Current_Position_Right - Step_Size, Goal_Right_Servo);
     }
     else {
       Current_Position_Right = min(Current_Position_Right + Step_Size, Goal_Right_Servo);
     }
     Right_Servo.write(180 - Current_Position_Right);
     }


  }

  
  }
















