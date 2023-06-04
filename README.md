# Hogwarts Legacy Broom

The basic idea behind this project is to control the in-game broomstick in Hogwarts Legacy via a $800 Harry Potter's Nimbus 2000 movie prop replica. This done by the combination of a Adafruit LSM6DS3TR-C (Accelerometer), HC-SR04 Ultrasonic Module (Distance Measuring) Sensor and a Arduino Pro Micro. I essentially turn the broom movie prop replica into a GIANT XBOX 360/One controller by utilising the Arduino Xinput library (created by David Madison). The Arduino connects to the PC as a XBOX 360/One Controller. The Arduino utilises the sensors as a way to input data, to determine which buttons are needed to be pressed to send the PC with Hogwarts Legacy running on it via USB.

## Check out the video for a demonstration

[![Thumbnail of Youtube Video based upon this fantastic and brilliant project]([https://raw.githubusercontent.com/Thats-so-Mo/Hogwarts-Legacy-Broom/main/thumbnailv2.png?token=GHSAT0AAAAAACBOOOGRZOPAAL6Y5SV5MBRGZD4AREQ))](https://youtu.be/3N-Sf7CjN4E)

## Ingredients

Items needed:
1. Arduino based Pro Micro (eBay/electronics site)
2. HC-SR04 Ultrasonic Module Distance Measuring Sensor (I got mine here: https://core-electronics.com.au/hc-sr04-ultrasonic-module-distance-measuring-sensor.html)
3. Adafruit LSM6DS3TR-C (I got mine here: https://core-electronics.com.au/adafruit-lsm6ds3tr-c-6-dof-accel-gyro-imu-stemma-qt-qwiic.html)
4. a push button (for reseting the Arduino - to reset the mount state just incase)

Three required libraries:

Dave Madison's Arduino Xinput - https://www.partsnotincluded.com/how-to-emulate-an-xbox-controller-with-arduino-xinput/

Tim Eckel's NewPing

Adafruit LSM6DS3: https://github.com/adafruit/Adafruit_LSM6DS

Special Thanks to the creators of those libraries, without them - I would not have been able to complete this project. :)

## Wiring Diagram

## Explaination



