Lora_Communication code take the gpio pins 4 and 18 and uses 4 for left servo and 18 for right servo.
  Then connected to the lora module by tx2 and rx2
Lora module sends and receives commands through baud 9600
Esp32 receives through baud 115200

SL0
SR0
SM0
V0

S means servo is selected
L means left servo
R means right servo
M means both servos
0 is the position of the servo
V is for the delay in milliseconds
the 0 in the V command is the delay between each loop for the degree change (V5 is 5 milliseconds wait for every 1 degree of change. This updates at the start of each loop)
                                                                             
