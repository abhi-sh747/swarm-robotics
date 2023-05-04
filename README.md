# swarm-robotics

**Project Overview:**

This repo includes two arduino code files for a swarm robotics project in which the user is sending commands to the main robot 
using bluetooth application and then the robot is transmitting the received commands to the follower robot using another bluetooth
module in the main robot.

The Follower Robot receives the commands from the main robot via a bluetooth module. Thus, both the robots recieve the same commands
for movement (forward - w, backward - s, right - d, left - a and stop - z).

There is also a potentiometer for adjusting speed of the main robot. Changing main robot speed doesn't change anything for the 
follower robot for now.



**Components I Used for testing:**

1. Main Robot: Chassis, 4 x tyres, 4 x 12v motors, motor driver (L293D), two Bluetooth modules (HC-05), Arduino UNO, 
		10K-ohm potentiometer, a switch, a 12 volt battery with a few jumper wires.

2. Follower Robot: Chassis, 2 x tyres, a castor wheel , 2 x 5v motors, motor driver (L293D), one Bluetooth module(HC-05), 
		Arduino UNO, a switch, a 12 volt battery with a few jumper wires.



**General Connections I used: **

1. Main Robot: 
In main robot, the Arduino board (UNO) acts as the main controller reading in data from the potentiometer (for speed control) 
and two hc-05 Bluetooth modules. Based on the input,  Arduino sends signals to the motor driver to make the connected motors stop 
or rotate clockwise or anticlockwise which results in the robot moving in four directions – forward, backward, left, right. 

First hc-05 is used to receive inputs from the user based on which main robot will perform certain actions and the second hc-05 
is being used to transmit data from first the main robot to the follower robot.

For power, the motor driver is connected to a 12v battery which further sends 5v signals to all the other components of the robot
including the Arduino, hc-05s, potentiometer, etc.

2. Follower Robot:
In follower robot, the Arduino board (UNO) acts as the main controller reading in data from the hc-05 Bluetooth module 
connected to the main robot. Based on the input,  Arduino sends signals to the motor driver to make the connected motors 
stop or rotate clockwise or anticlockwise which results in the robot moving in four directions – forward, backward, left, right. 

For power, the motor driver is connected to a 12v battery which further sends 5v signals to all the other components of the 
robot including the Arduino, hc-05, etc.




Demonstration Video Link: https://www.youtube.com/watch?v=74h_xOwxS9s



By: Abhinav Sharma
github.com/abhi-sh747
