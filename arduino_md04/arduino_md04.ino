/*
 * From www.swanrobotics.com
 * 
 * Code example for an MD04 motor driver from Robot Electronics for Arduino
 * https://www.robot-electronics.co.uk/md04.html
 * 
 * In a loop, the code spins up the motor to maximum speed and slows it down to a hold.
 * Then change the direction and goes to maximum speed, and hold again.
 * It uses the I2C protocol from the Wire library.
 * 
 * To connect the MD04 motor driver, for example, an Arduino Uno with the following connections:
 *  MD04      Arduino Uno
 *  P1    <=> D19 (SCL)
 *  P2    <=> D18 (SDA) 
 *  G     <=> GND
 * 
 * The original code by:
 * James Henderson 2012
 * https://www.robot-electronics.co.uk/htm/arduino_examples.htm#MD03%2050V%2020A%20Motor%20Driver
 */

#include <Wire.h>

#define ADDRESS             0x58                    // Address of MD03
#define SOFTREG             0x07                    // Byte to read software
#define CMDBYTE             0x00                    // Command byte
#define SPEEDBYTE           0x02                    // Byte to write to speed register
#define TEMPREG             0x04                    // Byte to read temperature
#define CURRENTREG          0x05                    // Byte to read motor current

byte direct = 1;                                    // Stores what direction the motor should run in

void setup(){
  Serial.begin(19200);                              // Start Serial connection
  delay(100);
  
  Wire.begin();                                     // Start I2C connection
  delay(100);
  
  Serial.print("Software version MD04: ");          // Print Software version from MD04
  Serial.println(getData(SOFTREG));
}

void loop(){
  for(int i = 0; i < 250; i=i+10){
    sendData(SPEEDBYTE, i);             // Sets speed to i
    sendData(CMDBYTE, direct);          // Sets motor to direct, a value of 1 runs the motor forward and 2 runs backward
    showData(direct,i);                 // Call function to print data to Serial
    delay(100);                         // Wait 0,1 second to send the next speed value
  }
  delay(100);
  for(int i = 250; i > 10; i=i-10){
    sendData(SPEEDBYTE, i);             // Sets speed to i
    sendData(CMDBYTE, direct);          // Sets motor to direct, a value of 1 runs the motor forward and 2 runs backward
    showData(direct,i);                 // Call function to print data to Serial
    delay(100);                         // Wait 0,1 second to send the next speed value
  }
  if(direct == 1)                       // If loop that swaps value of direct between 1 and 2 each time through loop
    direct = 2;                        
  else
    direct = 1;                     
}

void showData(byte valdirection, byte valSpeed) {
    Serial.print("Direction: ");
    Serial.print(valdirection);         // Prints current direction (1 or 2)
    Serial.print(" - Speed: ");
    Serial.print(valSpeed);             // Prints current Speed (0-250) tot Serial
   
    byte current = getData(CURRENTREG); // Get current value (186 = 20 Amp) to Serial
    delay(10);
    Serial.print(" - Current: ");       
    Serial.print(current);              
    
    byte temp = getData(TEMPREG);       // Get surface temperature of the PCB in degrees centigrade.
    delay(10);
    Serial.print(" - Temperature: ");
    Serial.print(temp);                
    
    Serial.println(".");                // Point at the end of the line and an Enter
}

byte getData(byte reg){                 // function for getting data from MD03
  Wire.beginTransmission(ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS, 1);         // Requests byte from MD03
  while(Wire.available() < 1);          // Waits for byte to become available
  byte data = Wire.read();

  return(data);
}

void sendData(byte reg, byte val){      // Function for sending data to MD03
  Wire.beginTransmission(ADDRESS);      // Send data to MD03
    Wire.write(reg);                    // Command like Direction, Speed
    Wire.write(val);                    // Value for the command
  Wire.endTransmission();
}
