# arduino-md04
Full article on https://swanrobotics.com/md04-motor-drivers/

Arduino Example for controlling a MD04 motor driver with I2C.

For the program, I started with the example: Arduino Examples (robot-electronics.co.uk) This example also used a display; I only needed the part to control the motors, so I changed the code example from James Henderson to a simpler version. The purpose is to make a loop of spinning a motor to half the speed and slowing down to a halt. At the same time, the code needs to read the information from the MD04 and send them to the serial connection.
