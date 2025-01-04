# Esp 32 Motor Controller

Based from ROS2Ardiuno Bridge by Josh Ewans and modified using Curie Res codes

Update: added imu sensor  reading functions based on machinelearningsite.com and https://lastminuteengineers.com

Pin Assignment:

left motor forward/Backward - 32/33
right motor forward/Backward - 25/26
 
left encoder clk - 17
left encoder dt - 16

right encoder clk - 19
right encoder dt - 18

IR = ultrasonic
left IR_in - 13
left IR_out - 14
right IR_in - 04
right IR_out - 27

IMU scl - 21
IMU sda - 22