#include <SoftwareSerial.h>

// defining motor driver's enable and input pins
#define md1 4
#define md2 5
#define md3 6
#define md4 7
#define enA 9
#define enB 10

// defining software serial ports on arduino for both the bluetooth modules
#define blRx 11
#define blTx 12
#define blRxMaster 2
#define blTxMaster 3

// defining input pin from the potentiometer.
#define potPin A0

// defining speed and boolean global variables 
int speed = 0;
bool isRightOrLeft = false;

// creating two serial communication objects and enabling their communication on the specified pins
SoftwareSerial bluetooth(blRx, blTx);
SoftwareSerial bluetoothMaster(blRxMaster, blTxMaster);

void setup() 
{
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  pinMode(md3, OUTPUT);
  pinMode(md4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(potPin, INPUT);

  // starting communication with the master bluetooth which will connect with the follower robot's bluetooth module.
  bluetoothMaster.begin(38400);
  while(!bluetoothMaster) {;}
  delay(100);

  // starting communication with the bluetooth module which will receive data from the user.
  bluetooth.begin(9600);
  while(!bluetooth) {;}
  delay(100);

  bluetooth.println("Main Robot Connected! ");
  stop();
}

void loop() 
{
  // listening on the 1st bluetooth port 
  bluetooth.listen();

  speedControl();
  if(bluetooth.available())
  {
    // reading input from user via bluetooth and printing current speed(0-min, 255-max) based on potentiometer
    char input = bluetooth.read(); 
    bluetooth.println(speed);

    // forward
    if (input == 'w') 
    {
      isRightOrLeft = false;
      forward();

      // listening on the master bluetooth port to send data to follower robot
      bluetoothMaster.listen();
      delay(15);
      bluetoothMaster.println("w");
    }
    //backward 
    else if (input == 's') 
    {
      isRightOrLeft = false;
      backward();
      
      // listening on the master bluetooth port to send data to follower robot
      bluetoothMaster.listen();
      delay(15);
      bluetoothMaster.println("s");
    }

    // right
    else if (input == 'd') 
    {
      isRightOrLeft = true;
      right();

      // listening on the master bluetooth port to send data to follower robot
      bluetoothMaster.listen();
      delay(15);
      bluetoothMaster.println("d");
    }

    //left
    else if (input == 'a') 
    {
      isRightOrLeft = true;
      left(); 

      // listening on the master bluetooth port to send data to follower robot
      bluetoothMaster.listen();
      delay(15);
      bluetoothMaster.println("a");
    }

    //stop
    else if (input == 'z')
    {
      stop();

      // listening on the master bluetooth port to send data to follower robot
      bluetoothMaster.listen();
      delay(15);
      bluetoothMaster.println("z");
    }
  }
}

// function to read from the potentiometer's data pin and accordingly adjust the speed of the motor 
void speedControl()
{
  speed = analogRead(potPin);
  speed = map(speed, 0, 1023, 0, 255);

  // increases the speed by 80 while turning to make rotating faster.
  if(isRightOrLeft)
  {
    speed += 80;
    if(speed > 255) speed = 255;
    if(speed == 0) speed = 0;
  }

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

// making the robot move forward
void forward()
{
  digitalWrite(md1, HIGH);
  digitalWrite(md2, LOW);
  digitalWrite(md3, HIGH);
  digitalWrite(md4, LOW);

  bluetooth.println("FORWARD \t MAIN \nSpeed: "); 
  bluetooth.println(speed); 
}
 
// making the robot move backwrd
void backward()
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);
  digitalWrite(md3, LOW);
  digitalWrite(md4, HIGH);

  bluetooth.println("BACKWARD \t MAIN \nSpeed: "); 
  bluetooth.println(speed);
}
 
// making the robot move right
void right()
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);
  digitalWrite(md3, HIGH);
  digitalWrite(md4, LOW);

  bluetooth.println("RIGHT \t MAIN \nSpeed: "); 
  bluetooth.println(speed);
}
 
// making the robot move left
void left()
{
  digitalWrite(md1, HIGH);
  digitalWrite(md2, LOW);
  digitalWrite(md3, LOW);
  digitalWrite(md4, HIGH);

  bluetooth.println("LEFT \t MAIN \nSpeed: "); 
  bluetooth.println(speed);
}
 
// making the robot stop
void stop()
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, LOW);
  digitalWrite(md3, LOW);
  digitalWrite(md4, LOW);

  bluetooth.println("STOP \t MAIN \nSpeed: "); 
  bluetooth.println(speed);
}
 