#include <SoftwareSerial.h>

// defining motor driver's input pins
#define fmd1 4
#define fmd2 5
#define fmd3 6
#define fmd4 7

// defining communication port for the bluetooth module
SoftwareSerial bluetooth(2, 3);

void setup()
{
  pinMode(fmd1, OUTPUT);
  pinMode(fmd2, OUTPUT);
  pinMode(fmd3, OUTPUT);
  pinMode(fmd4, OUTPUT);

  // initializing serial communication for testing purposes
  Serial.begin(9600);
  // initiializing communation with the bluetooth module to receive inputs from the main robot
  bluetooth.begin(38400);
  while(!bluetooth) {;}

  bluetooth.println("Follower Robot Connected");
  Serial.print("Working");
  stop();
}

void loop()
{
  if(bluetooth.available())
  {
    // reading input from user via bluetooth and printing received input
    char input = bluetooth.read();
    Serial.println(input);

    // forward
    if(input == 'w')
    {
      forward();
    }

    // backward
    else if(input == 's')
    {
      backward();
    }
    
    // left
    else if(input == 'a')
    {
      left(); 
    }

    // right
    else if(input == 'd')
    {
      right();
    }

    // stop
    if(input == 'z')
    {
      stop();
    }
  }
}

// making the robot move forward
void forward()
{
  digitalWrite(fmd1, HIGH);
  digitalWrite(fmd2, LOW);
  digitalWrite(fmd3, HIGH);
  digitalWrite(fmd4, LOW);

  bluetooth.println("FORWARD \t Follower");
}
 
// making the robot move backward
void backward()
{
  digitalWrite(fmd1, LOW);
  digitalWrite(fmd2, HIGH);
  digitalWrite(fmd3, LOW);
  digitalWrite(fmd4, HIGH);

  bluetooth.println("BACKWARD \t Follower");
}
 
// making the robot move left
void left()
{
  digitalWrite(fmd1, LOW);
  digitalWrite(fmd2, HIGH);
  digitalWrite(fmd3, HIGH);
  digitalWrite(fmd4, LOW);

  bluetooth.println("RIGHT \t Follower");
}

// making the robot move right
void right()
{
  digitalWrite(fmd1, HIGH);
  digitalWrite(fmd2, LOW);
  digitalWrite(fmd3, LOW);
  digitalWrite(fmd4, HIGH);

  bluetooth.println("LEFT \t Follower");
}
 
// making the robot stop
void stop()
{
  digitalWrite(fmd1, LOW);
  digitalWrite(fmd2, LOW);
  digitalWrite(fmd3, LOW);
  digitalWrite(fmd4, LOW);

  bluetooth.println("STOP \t Follower");
}
 